#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#include <hagl_hal.h>
#include <hagl.h>

#include "fonts.h"

#include <wchar.h>

#include <mod_play.h>
#include <sound_i2s.h>

#include "hymn_to_aurora.h"
#include "graphics_data.h"
#include "player.h"
#include "rendering.h"
#include "input.h"
#include "textbox.h"
#include "menu.h"
#include "save_system.h"
#include "game_state.h"
#include "audio.h"
#include "global.h"
#include "fishing.h"
#include "pcInterface.h"
#include "shopMenu.h"

static const uint64_t US_PER_FRAME_60_FPS = 1000000 / 60;
GameState game_state = GAME_STATE_TITLE;
bool fish_hooked = false;
fish_list globalCaughtFish = FISH_COUNT;

static const struct sound_i2s_config sound_config = {
  .pin_scl         = 10,
  .pin_sda         = 9,
  .pin_ws          = 11,
  .sample_rate     = 22050,
  .bits_per_sample = 16,
  .pio_num         = 0,
};

int titleScreen(hagl_backend_t *display) {
    hagl_clear(display);
    hagl_blit(display, 0, 0, &titleScreenImg);

    hagl_flush(display);
    while (1) {
        if (!gpio_get(14)) return 0;
        if (!gpio_get(15)) return 1;
    }

}

uint8_t joypad(void) {
    uint8_t state = 0;
    
    // Read GPIO pins for joypad state (switch style / japanese style)
    if (!gpio_get(5)) state |= JOYPAD_UP;      // W
    if (!gpio_get(6)) state |= JOYPAD_LEFT;    // A  
    if (!gpio_get(7)) state |= JOYPAD_DOWN;    // S
    if (!gpio_get(8)) state |= JOYPAD_RIGHT;   // D
    if (!gpio_get(12)) state |= JOYPAD_X;      // I
    if (!gpio_get(13)) state |= JOYPAD_Y;      // J
    if (!gpio_get(14)) state |= JOYPAD_B;      // K
    if (!gpio_get(15)) state |= JOYPAD_A;      // L
    
    return state;
}

void updateJoypad(void) {
    uint8_t last = joypad_state.down;
    joypad_state.down = joypad();
    joypad_state.pressed = ~last & joypad_state.down;
    joypad_state.released = last & ~joypad_state.down;
}

void gameLoop(hagl_backend_t *display) {
    switch (game_state) {
        case GAME_STATE_TITLE:
            game_state = GAME_STATE_MENU;
            break;
        case GAME_STATE_NORMAL:
            handleInput(display);
            handleMapTransitions();
            break;
        case GAME_STATE_MENU:
            menu(display);
            break;
        case GAME_STATE_PC:
            pcInterface(display);
            break;
        case GAME_STATE_SHOP:
            shopMenu(display);
            break;
        case GAME_STATE_TEXTBOX:
            handleInput(display);
            updateTextBoxTimer();
            break;
        case GAME_STATE_FISHING:
            handleInput(display);
            fishingProcess();
            // Unimplemented
            break;
        default:
            break;
    }
}

void render(hagl_backend_t *display) {
    renderMap(display);
    renderInteractableObjects(display);
    renderPlayer(display);

    if (currentMap == &shopMap) {
        renderSprite(display, 46, 4, fish_data[fishDisplayFish[0]].texture);
        renderSprite(display, 78, 4, fish_data[fishDisplayFish[1]].texture);
        renderSprite(display, 110, 4, fish_data[fishDisplayFish[2]].texture);
    }

    switch (game_state) {
        case GAME_STATE_TEXTBOX:
            renderTextBox(display);
            if (globalCaughtFish != FISH_COUNT) {
                renderScaledSprite(display, 60, 26, fish_data[globalCaughtFish].texture, 5);
            }
            player.steps = 0;
            break;
        case GAME_STATE_FISHING:
            if (fish_hooked) {
                if (player.y < 9) {
                    renderSprite(display, player.x, player.y + 20, &alert);
                } else {
                    renderSprite(display, player.x, player.y - 16, &alert);
                }
            }
            break;
    }
    
    hagl_flush(display);
}

void main()
{
    stdio_init_all();

    hagl_backend_t *display = hagl_init();

    initInput();
    initPlayer();
    initGameState();

    sound_i2s_init(&sound_config);


    int soundActive = titleScreen(display);

    if (soundActive) {
        mod_play_start(&mod_hymn_to_aurora, 22050, 1);
        sound_i2s_playback_start();
    }

    game_state = GAME_STATE_NORMAL;

    while (1) {
        uint64_t start = time_us_64();
        updateJoypad();

        gameLoop(display);
        render(display);
        update_mod_player();

        busy_wait_until(start + US_PER_FRAME_60_FPS);
    }


    hagl_close(display);
}