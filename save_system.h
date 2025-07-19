#ifndef SAVE_SYSTEM_H
#define SAVE_SYSTEM_H

#define FLASH_TARGET_OFFSET (2044 * 1024)

#include "player.h"

// Simple save data structure containing only essential player data
struct player_save_data {
    float x, y;
    int direction;
    struct item inventory[3];
    int inventory_count; // Number of items in inventory
};

void saveGame(void);
void loadGame(void);

#endif // SAVE_SYSTEM_H
