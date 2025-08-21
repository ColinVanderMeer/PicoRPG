#ifndef SAVE_SYSTEM_H
#define SAVE_SYSTEM_H

#define FLASH_TARGET_OFFSET (2044 * 1024)

#include "player.h"
#include "global.h"

// Simple save data structure containing only essential player data
struct player_save_data {
    float x, y;
    int direction;
    int fishMaxWeight[FISH_COUNT];
    int money;
    int fishTimesCaught[FISH_COUNT];
    int allFishTimesCaught;
    int fishDisplayFish[3];
    int catchSpeedIncrease;
    int weightIncrease;
    int rarityIncrease;
};

void saveGame(void);
void loadGame(void);

#endif // SAVE_SYSTEM_H
