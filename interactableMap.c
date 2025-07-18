#include "interactableMap.h"

struct interactableObject sign1 = {
    .x = 110,
    .y = 16,
    .sprite = &sign,
    .numMessages = 4,
    .messages = {
        L"Hello world!",
        L"Goodbye world!",
        L"The world exists!",
        L"stop talking to me",
    }
};

struct interactableObject sign2 = {
    .x = 60,
    .y = 16,
    .sprite = &sign,
    .numMessages = 2,
    .messages = {
        L"I'm a evil sign... I'm going to over flow the text buffer and crash the game!",
        L"Wait what do you mean it's been patched?",
    }
};

struct interactableObject sign3 = {
    .x = 50,
    .y = 16,
    .sprite = &sign,
    .numMessages = 2,
    .messages = {
        L"I'm an outdoor sign! Those inside signs are so boring!",
        L"(This is definitely the more boring sign)",
    }
};

struct interactableObject morayObj = {
    .x = 110,
    .y = 60,
    .sprite = &moray,
    .numMessages = 7,
    .messages = {
        L"What do you MEAN I'm in the wrong game!?!?",
        L"That's absurd!",
        L"Absolutely ridiculous!",
        L"Unbelievable!",
        L"Outrageous!",
        L"Preposterous!",
        L"I'm only here because someone can't draw sprites                            {They're right...}",
    }
};

struct interactableObject lucasObj = {
    .x = 71,
    .y = 23,
    .sprite = &lucas,
    .numMessages = 6,
    .messages = {
        L"{I still haven't played Mother 3}",
        L"{I'll get around to it eventually okay}",
        L"{I've just been busy implementing a save system}",
        L"{It actually works pretty well}",
        L"{I'm pretty proud of it}",
        L"{It's in your menu (press I to open it)}",
    }
};

struct interactableObject* houseObjects[] = {
    &sign1,
    &sign2,
};

const int numHouseObjects = sizeof(houseObjects) / sizeof(houseObjects[0]);

struct interactableObject* outsideObjects[] = {
    &sign3,
    &morayObj,
};

const int numOutsideObjects = sizeof(outsideObjects) / sizeof(outsideObjects[0]);

struct interactableObject* roadObjects[] = {
    &lucasObj,
};

const int numRoadObjects = sizeof(roadObjects) / sizeof(roadObjects[0]);

struct map houseMap = {
    .tiles = {
        {&water, &waterA1, &water, &waterGrassBR, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT},
        {&water, &water, &waterGrassBR, &grassWaterTL, &grass, &grass, &grass, &grass, &grass, &grass},
        {&waterA1, &water, &grassWaterL, &grass, &grass, &grass, &grass, &grass, &grass, &grass},
        {&water, &water, &grassWaterL, &grass, &grass, &grass, &grass, &grass, &grass, &grass},
        {&waterA2, &water, &grassWaterL, &grass, &grass, &grass, &grass, &grass, &grass, &grass},
        {&water, &water, &grassWaterL, &grass, &grass, &grass, &grass, &grass, &grass, &grass},
        {&water, &water, &waterGrassTR, &grassWaterBL, &grass, &grass, &grass, &grass, &grass, &grass},
        {&waterA1, &water, &water, &waterGrassTR, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB},
    },
    .objects = houseObjects,
    .numObjects = numHouseObjects,
};

struct map outsideMap = {
    .tiles = {
        {&grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &waterGrassBL, &water, &water, &water, &water, &waterA1},
        {&grass, &grass, &grass, &grass, &grassWaterR, &water, &waterA1, &water, &water, &water},
        {&grass, &grass, &grass, &grass, &grassWaterR, &water, &water, &water, &waterA2, &water},
        {&grass, &grass, &grass, &grass, &grassWaterTR, &grassWaterT, &grassWaterT, &grassWaterT, &waterGrassBL, &water},
        {&grass, &grass, &grass, &grass, &grass, &grass, &grass, &grass, &grassWaterR, &water},
        {&grass, &grass, &grass, &grass, &grass, &grass, &grass, &grass, &grassWaterR, &waterA1},
        {&grass, &grass, &grass, &grass, &grass, &grass, &grass, &grass, &grassWaterR, &water},
        {&grassWaterB, &grassWaterB, &grassWaterB, &grassWaterBL, &grass, &grass, &grass, &grass, &grassWaterR, &water},
    },
    .objects = outsideObjects,
    .numObjects = numOutsideObjects,
};

struct map roadMap = {
    .tiles = {
        {&waterA2, &water, &water, &grassWaterL, &grass, &grass, &grass, &grass, &grassWaterR, &water},
        {&water, &water, &water, &grassWaterL, &grass, &grass, &grass, &grass, &grassWaterR, &waterA1},
        {&water, &waterA1, &water, &grassWaterL, &grass, &grass, &grass, &grass, &grassWaterR, &water},
        {&water, &water, &water, &grassWaterL, &grass, &grass, &grass, &grass, &grassWaterR, &water},
        {&water, &water, &water, &waterGrassTR, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &waterGrassTL, &water},
        {&water, &waterA2, &water, &water, &water, &water, &waterA2, &water, &water, &waterA2},
        {&water, &water, &water, &water, &water, &water, &water, &water, &water, &water},
        {&water, &water, &water, &water, &waterA1, &water, &water, &water, &water, &water},
    },
    .objects = roadObjects,
    .numObjects = numRoadObjects,
};
