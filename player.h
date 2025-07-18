#ifndef PLAYER_H
#define PLAYER_H

#include <hagl_hal.h>
#include <hagl.h>

struct player {
    float x, y;
    int direction;
    int steps;
};

extern struct player player;

void renderPlayer(hagl_backend_t *display);

#endif // PLAYER_H
