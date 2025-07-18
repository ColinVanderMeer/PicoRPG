#include "player.h"
#include "graphics_data.h"
#include "rendering.h"

struct player player = {30, 30, 2, 0};

void renderPlayer(hagl_backend_t *display) {
    if (player.direction == 0) {
        if (player.steps > 60) {
            renderSprite(display, (int)player.x, (int)player.y, &friskWalkW3);
            if (player.steps > 80) {
                player.steps = 0;
            }
        } else if (player.steps > 20 && player.steps < 40) {
            renderSprite(display, (int)player.x, (int)player.y, &friskWalkW2);
            if (player.steps > 40) {
                player.steps = 0;
            }
        } else {
            renderSprite(display, (int)player.x, (int)player.y, &friskWalkW1);
        }
    } else if (player.direction == 1) {
        if (player.steps > 20) {
            renderSprite(display, (int)player.x, (int)player.y, &friskWalkA2);
            if (player.steps > 40) {
                player.steps = 0;
            }
        } else {
            renderSprite(display, (int)player.x, (int)player.y, &friskWalkA1);
        }
    } else if (player.direction == 2) {
        if (player.steps > 60) {
            renderSprite(display, (int)player.x, (int)player.y, &friskWalkS3);
            if (player.steps > 80) {
                player.steps = 0;
            }
        } else if (player.steps > 20 && player.steps < 40) {
            renderSprite(display, (int)player.x, (int)player.y, &friskWalkS2);
            if (player.steps > 40) {
                player.steps = 0;
            }
        } else {
            renderSprite(display, (int)player.x, (int)player.y, &friskWalkS1);
        }
    } else if (player.direction == 3) {
        if (player.steps > 20) {
            renderSprite(display, (int)player.x, (int)player.y, &friskWalkD2);
            if (player.steps > 40) {
                player.steps = 0;
            }
        } else {
            renderSprite(display, (int)player.x, (int)player.y, &friskWalkD1);
        }
    }
}
