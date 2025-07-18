#ifndef PLAYER_H
#define PLAYER_H

#include <hagl_hal.h>
#include <hagl.h>

// Animation configuration
#define MAX_ANIMATION_FRAMES 6
#define NUM_DIRECTIONS 4

struct animation_config {
    hagl_bitmap_t *idle_frames[MAX_ANIMATION_FRAMES];
    hagl_bitmap_t *walk_frames[MAX_ANIMATION_FRAMES];
    int idle_frame_count;
    int walk_frame_count;
    int frame_duration;
};

struct player {
    float x, y;
    int direction;
    int steps;
    int animation_timer;
    int is_walking;
    struct animation_config animations[NUM_DIRECTIONS];
};

extern struct player player;

void initPlayer();
void renderPlayer(hagl_backend_t *display);
void setPlayerWalking(int walking);
void setPlayerDirection(int direction);

#endif // PLAYER_H
