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
};

// External declarations
extern struct interactableObject sign1;
extern struct interactableObject sign2;
extern struct interactableObject sign3;
extern struct interactableObject morayObj;
extern struct interactableObject lucasObj;

extern struct interactableObject* houseObjects[];
extern struct interactableObject* outsideObjects[];
extern struct interactableObject* roadObjects[];

extern const int numHouseObjects;
extern const int numOutsideObjects;
extern const int numRoadObjects;

extern struct map houseMap;
extern struct map outsideMap;
extern struct map roadMap;

#endif // INTERACTABLE_MAP_H
