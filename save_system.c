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
        .direction = player.direction,
        .inventory[0] = player.inventory[0],
        .inventory[1] = player.inventory[1],
        .inventory[2] = player.inventory[2],
        .inventory_count = player.inventory_count
    };
    
    uint8_t mapSaveDataBytes;
    if (getCurrentMap() == &startMap) {
        mapSaveDataBytes = 0;
    } else if (getCurrentMap() == &centralMap) {
        mapSaveDataBytes = 1;
    } else if (getCurrentMap() == &dockMap) {
        mapSaveDataBytes = 2;
    } else if (getCurrentMap() == &shopIslandMap) {
        mapSaveDataBytes = 3;
    } else {
        mapSaveDataBytes = 0; // Default to startMap if unknown
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
    player.inventory_count = playerSave.inventory_count;
    for (int i = 0; i < player.inventory_count; i++) {
        wcscpy(player.inventory[i].name, playerSave.inventory[i].name);
    }
    
    // Reset animation state (don't save/load animation state)
    player.animation_timer = 0;
    player.is_walking = 0;
    player.steps = 0;
    
    uint8_t mapSaveDataBytes;
    memcpy(&mapSaveDataBytes, flash_target_contents + sizeof(struct player_save_data), sizeof(mapSaveDataBytes));
    
    switch (mapSaveDataBytes) {
        case 0:
            setCurrentMap(&startMap);
            break;
        case 1:
            setCurrentMap(&centralMap);
            break;
        case 2:
            setCurrentMap(&dockMap);
            break;
        case 3:
            setCurrentMap(&shopIslandMap);
            break;
    }
    printf("Loaded\n");
}
