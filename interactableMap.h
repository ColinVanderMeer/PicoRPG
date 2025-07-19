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

// External declarations
extern struct interactableObject sign1;
extern struct interactableObject sign2;
extern struct interactableObject sign3;

extern struct interactableObject* startObjects[];
extern struct interactableObject* map2Objects[];
extern struct interactableObject* map3Objects[];
extern struct interactableObject* map4Objects[];
extern struct interactableObject* itemMap1Objects[];
extern struct interactableObject* itemMap2Objects[];
extern struct interactableObject* itemMap3Objects[];

extern const int numstartObjects;
extern const int nummap2Objects;
extern const int nummap3Objects;
extern const int numMap4Objects;
extern const int numItemMap1Objects;
extern const int numItemMap2Objects;
extern const int numItemMap3Objects;

extern struct map startMap;
extern struct map map2;
extern struct map map3;
extern struct map map4;
extern struct map itemMap1;
extern struct map itemMap2;
extern struct map itemMap3;

#endif // INTERACTABLE_MAP_H
