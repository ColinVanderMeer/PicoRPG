#include "interactableMap.h"

struct interactableObject sign1 = {
    .x = 60,
    .y = 32,
    .sprite = &sign,
    .numMessages = 1,
    .messages = {
        L"Welcome to PicoRPG! Use L to interact with objects, K to close text boxes,   and I to open the menu.",
    }
};

struct interactableObject sign2 = {
    .x = 110,
    .y = 32,
    .sprite = &sign,
    .numMessages = 1,
    .messages = {
        L"Your goal is to find the 3 magical items to open  the cabin. Good luck!",
    }
};

struct interactableObject sign3 = {
    .x = 107,
    .y = 56,
    .sprite = &sign,
    .numMessages = 3,
    .messages = {
        L"Some NPC's have multiple lines of text. Press L   again to see more.",
        L"See I have so much more  to say than the 100 characters in the text box!",
        L"Uh... actually I've run  out of things to say now.",
    }
};

struct interactableObject sprigObj = {
    .x = 54,
    .y = 19,
    .sprite = &sprigDino,
    .numMessages = 1,
    .messages = {
        L"sprig",
    }
};

struct interactableObject* startObjects[] = {
    // &sign1,
    // &sign2,
};

const int numstartObjects = sizeof(startObjects) / sizeof(startObjects[0]);

struct interactableObject* centralMapObjects[] = {
    // &sign3,
};

const int numCentralMapObjects = sizeof(centralMapObjects) / sizeof(centralMapObjects[0]);

struct interactableObject* shopIslandMapObjects[] = {
};

const int numShopIslandMapObjects = sizeof(shopIslandMapObjects) / sizeof(shopIslandMapObjects[0]);

struct interactableObject* dockMapObjects[] = {
};

const int numDockMapObjects = sizeof(dockMapObjects) / sizeof(dockMapObjects[0]);

struct interactableObject* sprigRoomObjects[] = {
    &sprigObj,
};

const int sprigRoomNumObjects = sizeof(sprigRoomObjects) / sizeof(sprigRoomObjects[0]);

struct map startMap = {
    .tiles = {
        {&water, &water, &waterA1, &water, &water, &water, &water, &water, &water, &water},
        {&water, &water, &water, &waterGrassBR, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT},
        {&waterA2, &water, &waterGrassBR, &grassWaterTL, &grass, &grass, &grass, &grass, &grass, &grass},
        {&water, &water, &grassWaterL, &grass, &grass, &grass, &grassA2, &grass, &grass, &grass},
        {&water, &water, &grassWaterL, &grassA1, &grass, &grass, &grass, &grass, &grass, &grass},
        {&water, &water, &waterGrassTR, &grassWaterBL, &grass, &grass, &grass, &grass, &grassA1, &grass},
        {&water, &waterA1, &water, &waterGrassTR, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB},
        {&water, &water, &water, &water, &water, &water, &water, &waterA2, &water, &water}
    },
    .objects = startObjects,
    .numObjects = numstartObjects,
    .leftMap = NULL,
    .rightMap = &centralMap,
    .upMap = NULL,
    .downMap = NULL,
};

struct map centralMap = {
    .tiles = {
        {&water, &water, &water, &water, &water, &dockL, &dockR, &water, &water, &water},
        {&grassWaterT, &grassWaterT, &waterGrassBL, &water, &water, &dockL, &dockR, &water, &water, &water},
        {&grassA1, &grass, &grassWaterTR, &grassWaterT, &grassWaterT, &grassDockL, &grassDockR, &grassWaterT, &grassWaterT, &grassWaterT},
        {&grass, &grass, &grass, &grass, &grass, &grass, &grassA2, &grass, &grass, &grassA1},
        {&grass, &grass, &grassA1, &grass, &grassWaterBR, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB},
        {&grassA2, &grass, &grass, &grassWaterBR, &waterGrassTL, &water, &water, &water, &water, &water},
        {&grassWaterB, &grassWaterB, &grassWaterB, &waterGrassTL, &water, &water, &water, &water, &water, &water},
        {&water, &water, &water, &water, &water, &water, &water, &water, &water, &water}
    },
    .objects = centralMapObjects,
    .numObjects = numCentralMapObjects,
    .leftMap = &startMap,
    .rightMap = &shopIslandMap,
    .upMap = &dockMap,
    .downMap = NULL,
};

struct map shopIslandMap = {
    .tiles = {
        {&water, &water, &water, &water, &water, &water, &waterA1, &water, &water, &water},
        {&water, &water, &waterA2, &water, &water, &water, &water, &water, &water, &waterA1},
        {&grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &waterGrassBL},
        {&grass, &grassA2, &grass, &grass, &grass, &grass, &grass, &grass, &grass, &grassWaterR},
        {&grassWaterBL, &grass, &grass, &grassA1, &grass, &grass, &grass, &grassA2, &grass, &grassWaterR},
        {&waterGrassTR, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &waterGrassTL},
        {&waterA2, &water, &water, &water, &water, &water, &waterA2, &water, &water, &water},
        {&water, &water, &water, &waterA1, &water, &water, &water, &water, &waterA1, &water}
    },
    .objects = shopIslandMapObjects,
    .numObjects = numShopIslandMapObjects,
    .leftMap = &centralMap,
    .rightMap = NULL,
    .upMap = NULL,
    .downMap = NULL,
};

struct map dockMap = {
    .tiles = {
        {&waterA2, &water, &water, &water, &water, &water, &water, &water, &water, &waterA2},
        {&water, &water, &water, &waterA1, &water, &water, &water, &water, &water, &water},
        {&water, &waterA1, &water, &water, &water, &waterDockL, &waterDockR, &water, &water, &water},
        {&water, &water, &water, &water, &water, &dockL, &dockR, &water, &waterA2, &water},
        {&water, &water, &water, &water, &water, &dockL, &dockR, &water, &water, &water},
        {&water, &water, &water, &water, &water, &dockL, &dockR, &water, &waterA1, &water},
        {&water, &waterA1, &water, &water, &water, &dockL, &dockR, &water, &water, &water},
        {&water, &water, &water, &waterA2, &water, &dockL, &dockR, &water, &water, &waterA2}
    },
    .objects = dockMapObjects,
    .numObjects = numDockMapObjects,
    .leftMap = NULL,
    .rightMap = NULL,
    .upMap = NULL,
    .downMap = &centralMap,
};

struct map sprigRoom = {
    .tiles = {
        {&blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile},
        {&blackTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &blackTile},
        {&blackTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &blackTile},
        {&blackTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &blackTile},
        {&blackTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &blackTile},
        {&blackTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &greyTile, &blackTile},
        {&blackTile, &blackTile, &blackTile, &blackTile, &greyTile, &greyTile, &blackTile, &blackTile, &blackTile, &blackTile},
        {&blackTile, &blackTile, &blackTile, &blackTile, &greyTile, &greyTile, &blackTile, &blackTile, &blackTile, &blackTile}
    },
    .objects = sprigRoomObjects,
    .numObjects = sprigRoomNumObjects,
};