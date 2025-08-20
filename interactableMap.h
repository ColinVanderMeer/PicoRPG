#ifndef INTERACTABLE_MAP_H
#define INTERACTABLE_MAP_H

#include <hagl_hal.h>
#include <hagl.h>
#include <wchar.h>
#include "graphics_data.h"

struct interactableObject {
    int x, y;
    hagl_bitmap_t* sprite;
    int messageNumber;
    int numMessages;
    wchar_t* messages[];
};

struct map {
    hagl_bitmap_t* tiles[8][10];
    struct interactableObject** objects;
    int numObjects;
    struct map* leftMap;
    struct map* rightMap;
    struct map* upMap;
    struct map* downMap;
};

extern struct interactableObject* startObjects[];
extern struct interactableObject* centralMapObjects[];
extern struct interactableObject* dockMapObjects[];
extern struct interactableObject* shopIslandMapObjects[];
extern struct interactableObject* sprigRoomObjects[];

extern const int numstartObjects;
extern const int numCentralMapObjects;
extern const int numDockMapObjects;
extern const int numShopIslandMapObjects;
extern const int sprigRoomNumObjects;

extern struct map startMap;
extern struct map centralMap;
extern struct map dockMap;
extern struct map shopIslandMap;
extern struct map sprigRoom;

#endif // INTERACTABLE_MAP_H
