#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "interactableMap.h"

void initGameState(void);
struct map* getCurrentMap(void);
void setCurrentMap(struct map* map);
void handleMapTransitions(void);

extern struct map* currentMap;

#endif // GAME_STATE_H
