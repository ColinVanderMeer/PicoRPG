#include "input.h"
#include "player.h"
#include "textbox.h"
#include "menu.h"
#include "flash_utils.h"
#include "pico/stdlib.h"
#include "global.h"
#include "fishing.h"
#include "game_state.h"
#include <stdio.h>

joypad_state_t joypad_state;

void initInput(void) {
    gpio_init(5);
    gpio_set_dir(5, GPIO_IN);
    gpio_pull_up(5);

    gpio_init(6);
    gpio_set_dir(6, GPIO_IN);
    gpio_pull_up(6);

    gpio_init(7);
    gpio_set_dir(7, GPIO_IN);
    gpio_pull_up(7);

    gpio_init(8);
    gpio_set_dir(8, GPIO_IN);
    gpio_pull_up(8);

    gpio_init(12);
    gpio_set_dir(12, GPIO_IN);
    gpio_pull_up(12);

    gpio_init(13);
    gpio_set_dir(13, GPIO_IN);
    gpio_pull_up(13);

    gpio_init(14);
    gpio_set_dir(14, GPIO_IN);
    gpio_pull_up(14);

    gpio_init(15);
    gpio_set_dir(15, GPIO_IN);
    gpio_pull_up(15);
}

void handleInput(hagl_backend_t *display) {
    if (game_state == GAME_STATE_NORMAL) {
        int moving = 0;

        if (joypad_state.down & JOYPAD_UP) { // W
            if (tryMovePlayer(0, -0.9)) {
                setPlayerDirection(0); // Up direction
                moving = 1;
            }
        }
        if (joypad_state.down & JOYPAD_LEFT) { // A
            if (tryMovePlayer(-0.9, 0)) {
                setPlayerDirection(1); // Left direction  
                moving = 1;
            }
        }
        if (joypad_state.down & JOYPAD_DOWN) { // S
            if (tryMovePlayer(0, 0.9)) {
                setPlayerDirection(2); // Down direction
                moving = 1;
            }
        }
        if (joypad_state.down & JOYPAD_RIGHT) { // D
            if (tryMovePlayer(0.9, 0)) {
                setPlayerDirection(3); // Right direction
                moving = 1;
            }
        }
        
        setPlayerWalking(moving);
    }

    if (joypad_state.pressed & JOYPAD_X) { // I
        if (currentMap != &sprigRoom) {
            game_state = GAME_STATE_MENU;
        }
    }
    if (joypad_state.pressed & JOYPAD_Y) { // J
        
    }
    if (joypad_state.pressed & JOYPAD_B) { // K
        game_state = GAME_STATE_NORMAL;
        globalCaughtFish = FISH_COUNT;
        fish_hooked = false;
    }
    if (joypad_state.pressed & JOYPAD_A) { // L
        
        switch (game_state) {
            case GAME_STATE_NORMAL:
                interactObject();
                break;
            case GAME_STATE_FISHING:
                if (fish_hooked) {
                    catchFish();
                } else {
                    game_state = GAME_STATE_NORMAL;
                }
                break;
            default:
                break;
        }
    }
}
