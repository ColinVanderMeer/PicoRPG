#include "game_state.h"
#include "player.h"
#include "interactableMap.h"

static struct map (*currentMap) = &houseMap;

void initGameState(void) {
    currentMap = &houseMap;
}

struct map* getCurrentMap(void) {
    return currentMap;
}

void setCurrentMap(struct map* map) {
    currentMap = map;
}

void handleMapTransitions(void) {
    if (player.x > 150 && player.y > 35 && player.y < 60 && currentMap == &houseMap) {
        currentMap = &outsideMap;
        player.x = 10;
    }
    if (player.x < 10 && player.y > 35 && player.y < 60 && currentMap == &outsideMap) {
        currentMap = &houseMap;
        player.x = 140;
    }
    if (player.x > 55 && player.x < 85 && player.y > 110 && currentMap == &outsideMap) {
        currentMap = &roadMap;
        player.y = 0;
    }
    if (player.x > 55 && player.x < 85 && player.y < -10 && currentMap == &roadMap) {
        currentMap = &outsideMap;
        player.y = 100;
    }
}
