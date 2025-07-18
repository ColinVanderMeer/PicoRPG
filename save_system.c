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
    uint8_t* playerSaveDataBytes = (uint8_t*) &player;
    uint8_t mapSaveDataBytes;
    if (getCurrentMap() == &houseMap) {
        mapSaveDataBytes = 0;
    } else if (getCurrentMap() == &outsideMap) {
        mapSaveDataBytes = 1;
    } else if (getCurrentMap() == &roadMap) {
        mapSaveDataBytes = 2;
    }
    uint8_t* saveDataBytes = (uint8_t*) malloc(sizeof(player) + sizeof(mapSaveDataBytes));

    memcpy(saveDataBytes, playerSaveDataBytes, sizeof(player));
    memcpy(saveDataBytes + sizeof(player), &mapSaveDataBytes, sizeof(mapSaveDataBytes));

    int saveDataSize = sizeof(saveDataBytes);
    printf("Save size: %d\n", saveDataSize);

    int writeSize = (saveDataSize / FLASH_PAGE_SIZE) + 1;
    int sectorCount = ((writeSize * FLASH_PAGE_SIZE) / FLASH_SECTOR_SIZE) + 1; 
    printf("Save address: %d\n", FLASH_TARGET_OFFSET);
    printf("Save size: %d", FLASH_TARGET_OFFSET);

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
    memcpy(&player, flash_target_contents, sizeof(player));
    
    uint8_t mapSaveDataBytes;
    memcpy(&mapSaveDataBytes, flash_target_contents + sizeof(player), sizeof(mapSaveDataBytes));
    
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
