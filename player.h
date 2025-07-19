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

struct item {
    wchar_t name[10];
};

struct player {
    float x, y;
    int direction;
    int steps;
    int animation_timer;
    int is_walking;
    struct animation_config animations[NUM_DIRECTIONS];
    struct item inventory[3]; // Example inventory, can be expanded
    int inventory_count; // Number of items in inventory
};

extern struct player player;

void initPlayer();
void renderPlayer(hagl_backend_t *display);
void setPlayerWalking(int walking);
void setPlayerDirection(int direction);

#endif // PLAYER_H
