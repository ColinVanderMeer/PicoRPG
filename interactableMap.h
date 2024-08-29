#include <hagl.h>

char houseMap[8][10] = {
    "WWWWWWWWWW",
    "WFFFFFFFFW",
    "WFFFFFFFFW",
    "WFFFFFFFFF",
    "WFFFFFFFFF",
    "WFFFFFFFFW",
    "WFFFFFFFFW",
    "WWWWWWWWWW",
};

struct interactableObject {
    int x, y;
    hagl_bitmap_t* sprite;
    wchar_t message[];
};

struct interactableObject sign1 = {
    .x = 100,
    .y = 16,
    .sprite = &sign,
    .message = L"Hello, world!"
};

struct interactableObject sign2 = {
    .x = 50,
    .y = 16,
    .sprite = &sign,
    .message = L"I'm a evil sign... I'm going to over flow the text buffer and crash the game! Wait it's fixed?"
};

struct interactableObject* interactableObjects[] = {
    &sign1,
    &sign2,
};

const int numInteractableObjects = sizeof(interactableObjects) / sizeof(interactableObjects[0]);
