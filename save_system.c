#include "save_system.h"
#include "player.h"
#include "game_state.h"
#include "interactableMap.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void saveGame(void) {
    printf("Starting save\n");
    
    // Create a minimal save data structure
    struct player_save_data playerSave = {
        .x = player.x,
        .y = player.y,
        .direction = player.direction
    };
    
    uint8_t mapSaveDataBytes;
    if (getCurrentMap() == &houseMap) {
        mapSaveDataBytes = 0;
    } else if (getCurrentMap() == &outsideMap) {
        mapSaveDataBytes = 1;
    } else if (getCurrentMap() == &roadMap) {
        mapSaveDataBytes = 2;
    }
    
    int totalSaveSize = sizeof(struct player_save_data) + sizeof(mapSaveDataBytes);
    uint8_t* saveDataBytes = (uint8_t*) malloc(totalSaveSize);

    memcpy(saveDataBytes, &playerSave, sizeof(struct player_save_data));
    memcpy(saveDataBytes + sizeof(struct player_save_data), &mapSaveDataBytes, sizeof(mapSaveDataBytes));

    printf("Save size: %d\n", totalSaveSize);

    int writeSize = (totalSaveSize / FLASH_PAGE_SIZE) + 1;
    int sectorCount = ((writeSize * FLASH_PAGE_SIZE) / FLASH_SECTOR_SIZE) + 1; 
    printf("Save address: %d\n", FLASH_TARGET_OFFSET);

    uint32_t interrupts = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, sectorCount * FLASH_SECTOR_SIZE);
    flash_range_program(FLASH_TARGET_OFFSET, saveDataBytes, FLASH_PAGE_SIZE * writeSize);
    restore_interrupts(interrupts);
    printf("Saved\n");

    free(saveDataBytes);
    printf("Saved2\n");
}

void loadGame(void) {
    const uint8_t* flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);
    
    // Load the minimal player save data
    struct player_save_data playerSave;
    memcpy(&playerSave, flash_target_contents, sizeof(struct player_save_data));
    
    // Restore only the essential player data
    player.x = playerSave.x;
    player.y = playerSave.y;
    player.direction = playerSave.direction;
    
    // Reset animation state (don't save/load animation state)
    player.animation_timer = 0;
    player.is_walking = 0;
    player.steps = 0;
    
    uint8_t mapSaveDataBytes;
    memcpy(&mapSaveDataBytes, flash_target_contents + sizeof(struct player_save_data), sizeof(mapSaveDataBytes));
    
    switch (mapSaveDataBytes) {
        case 0:
            setCurrentMap(&houseMap);
            break;
        case 1:
            setCurrentMap(&outsideMap);
            break;
        case 2:
            setCurrentMap(&roadMap);
            break;
    }
    printf("Loaded\n");
}
