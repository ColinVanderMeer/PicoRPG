#ifndef SAVE_SYSTEM_H
#define SAVE_SYSTEM_H

#define FLASH_TARGET_OFFSET (2044 * 1024)

// Simple save data structure containing only essential player data
struct player_save_data {
    float x, y;
    int direction;
};

void saveGame(void);
void loadGame(void);

#endif // SAVE_SYSTEM_H
