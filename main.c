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

static const uint64_t US_PER_FRAME_60_FPS = 1000000 / 60;

bool gp15justPressed = false;

static const struct sound_i2s_config sound_config = {
  .pin_scl         = 10,
  .pin_sda         = 9,
  .pin_ws          = 11,
  .sample_rate     = 22050,
  .bits_per_sample = 16,
  .pio_num         = 0,
};

void gameLoop(hagl_backend_t *display) {
    while (1) {
        uint64_t start = time_us_64();
        hagl_clear(display);
        renderMap(display);

        uint16_t w = 20;
        uint16_t h = 30;
        hagl_color_t color = 0xffff;

        renderInteractableObjects(display);
        if (!doorOpeningActive) {
            handleInput(display);
        }
        
        renderPlayer(display);

        handleMapTransitions();


        if (isTextBoxActive()) {
            player.steps = 0;
            renderTextBox(display);
        }
        
        updateTextBoxTimer();
        
        update_mod_player();
        hagl_flush(display);
        busy_wait_until(start + US_PER_FRAME_60_FPS);
    }
}

int titleScreen(hagl_backend_t *display) {
    hagl_clear(display);
    hagl_blit(display, 0, 0, &titleScreenImg);

    hagl_flush(display);
    while (1) {
        if (!gpio_get(14)) return 0;
        if (!gpio_get(15)) return 1;
    }

}

int main()
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

    gameLoop(display);

    hagl_close(display);

}