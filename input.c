#include "input.h"
#include "player.h"
#include "textbox.h"
#include "menu.h"
#include "flash_utils.h"
#include "pico/stdlib.h"
#include <stdio.h>

extern bool gp15justPressed;

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
    if (!isTextBoxActive()) {
        int moving = 0;
        
        if (!gpio_get(5)) { // W
            player.y -= 0.9;
            setPlayerDirection(0); // Up direction
            moving = 1;
        }
        if (!gpio_get(6)) { // A
            player.x -= 0.9;
            setPlayerDirection(1); // Left direction  
            moving = 1;
        }
        if (!gpio_get(7)) { // S
            player.y += 0.9;
            setPlayerDirection(2); // Down direction
            moving = 1;
        }
        if (!gpio_get(8)) { // D
            player.x += 0.9;
            setPlayerDirection(3); // Right direction
            moving = 1;
        }
        
        setPlayerWalking(moving);
    }
    if (!gpio_get(12)) { // I
        menu(display);
    }
    if (!gpio_get(13)) { // J
        printf("Player X: %f, Player Y: %f\n", player.x, player.y);
        printf("Save size: %d, %d\n", sizeof(player), sizeof(void*));
        printf("Save address: %x\n", getAddressPersistent());
    }
    if (!gpio_get(14)) { // K
        setTextBoxActive(false);
    }
    if (!gpio_get(15) && gp15justPressed) { // L
        interactObject(display);
        gp15justPressed = false;
    }
    if (gpio_get(15)) {
        gp15justPressed = true;
    }
}
