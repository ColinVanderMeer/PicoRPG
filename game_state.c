#include "game_state.h"
#include "player.h"
#include "interactableMap.h"

static struct map (*currentMap) = &startMap;

void initGameState(void) {
    currentMap = &startMap;
}

struct map* getCurrentMap(void) {
    return currentMap;
}

void setCurrentMap(struct map* map) {
    currentMap = map;
}

void handleMapTransitions(void) {
    const int SCREEN_WIDTH = 160;
    const int SCREEN_HEIGHT = 128;

    const int PLAYER_WIDTH = 16;
    const int PLAYER_HEIGHT = 20;
    
    // Check if player walks off right edge
    if (player.x > SCREEN_WIDTH && currentMap->rightMap != NULL) {
        currentMap = currentMap->rightMap;
        player.x = 0;
    }
    // Check if player walks off left edge
    else if (player.x < -PLAYER_WIDTH && currentMap->leftMap != NULL) {
        currentMap = currentMap->leftMap;
        player.x = SCREEN_WIDTH - PLAYER_WIDTH; 
    }
    // Check if player walks off bottom edge
    else if (player.y > SCREEN_HEIGHT && currentMap->downMap != NULL) {
        currentMap = currentMap->downMap;
        player.y = 0; 
    }
    // Check if player walks off top edge
    else if (player.y < -PLAYER_HEIGHT && currentMap->upMap != NULL) {
        currentMap = currentMap->upMap;
        player.y = SCREEN_HEIGHT - PLAYER_HEIGHT; 
    }
}
