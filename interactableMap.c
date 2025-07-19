#include "interactableMap.h"

// Forward declaration
extern struct map cabinMap;

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
    .numMessages = 4,
    .messages = {
        L"Some NPC's have multiple lines of text. Press L   again to see more.",
        L"See I have so much more  to say than the 100 characters in the text box!",
        L"Uh... actually I've run  out of things to say now.",
        L"[3]",
    }
};

struct interactableObject carrotObj = {
    .x = 28,
    .y = 59,
    .sprite = &carrot,
    .numMessages = 2,
    .messages = {
        L"You found a carrot! [0]",
        L"(Picking up two carrots would be redundant.)", 
    }
};

struct interactableObject rockObj = {
    .x = 91,
    .y = 65,
    .sprite = &rock,
    .numMessages = 2,
    .messages = {
        L"You found a rock! [2]",
        L"(Picking up two rocks would be ROCKduntant.)", 
    }
};

struct interactableObject wheatObj = {
    .x = 39,
    .y = 45,
    .sprite = &wheat,
    .numMessages = 2,
    .messages = {
        L"You found some wheat! [1]",
        L"(Picking up two wheats would crash the game.)", 
    }
};

struct interactableObject cabinObj = {
    .x = 60,
    .y = -23,
    .sprite = &cabin,
    .numMessages = 1,
    .messages = {
        L"[3]",
    }
};

struct interactableObject* startObjects[] = {
    &sign1,
    &sign2,
};

const int numstartObjects = sizeof(startObjects) / sizeof(startObjects[0]);

struct interactableObject* map2Objects[] = {
    &sign3,
};

const int nummap2Objects = sizeof(map2Objects) / sizeof(map2Objects[0]);

struct interactableObject* map3Objects[] = {
};

const int nummap3Objects = sizeof(map3Objects) / sizeof(map3Objects[0]);

struct interactableObject* map4Objects[] = {
};

const int numMap4Objects = sizeof(map4Objects) / sizeof(map4Objects[0]);

struct interactableObject* itemMap1Objects[] = {
    &carrotObj,
};

const int numItemMap1Objects = sizeof(itemMap1Objects) / sizeof(itemMap1Objects[0]);

struct interactableObject* itemMap2Objects[] = {
    &rockObj,
};

const int numItemMap2Objects = sizeof(itemMap2Objects) / sizeof(itemMap2Objects[0]);

struct interactableObject* itemMap3Objects[] = {
    &wheatObj,
};

const int numItemMap3Objects = sizeof(itemMap3Objects) / sizeof(itemMap3Objects[0]);

struct interactableObject* cabinMapObjects[] = {
    &cabinObj,
};

const int numCabinMapObjects = sizeof(cabinMapObjects) / sizeof(cabinMapObjects[0]);

struct map startMap = {
    .tiles = {
        {&water, &water, &waterA1, &water, &water, &water, &water, &water, &waterA1, &water},
        {&water, &water, &water, &waterGrassBR, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT},
        {&water, &waterA2, &waterGrassBR, &grassWaterTL, &grass, &grass, &grassA2, &grass, &grass, &grass},
        {&water, &water, &grassWaterL, &grassA1, &grass, &grass, &grass, &grass, &grass, &grass},
        {&waterA1, &water, &grassWaterL, &grass, &grass, &grass, &grassA2, &grass, &grass, &grass},
        {&water, &water, &waterGrassTR, &grassWaterBL, &grass, &grassA1, &grass, &grass, &grass, &grass},
        {&water, &waterA2, &water, &waterGrassTR, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB},
        {&water, &water, &water, &water, &water, &water, &waterA2, &water, &water, &water}
    },
    .objects = startObjects,
    .numObjects = numstartObjects,
    .leftMap = NULL,
    .rightMap = &map2,
    .upMap = NULL,
    .downMap = NULL,
};

struct map map2 = {
    .tiles = {
        {&water, &water, &grassWaterL, &grass, &grassWaterR, &water, &water, &water, &water, &water},
        {&grassWaterT, &grassWaterT, &grassWaterTL, &grass, &grassWaterTR, &waterGrassBL, &water, &waterA2, &water, &water},
        {&grass, &grassA2, &grass, &grass, &grassA1, &grassWaterR, &water, &water, &water, &water},
        {&grass, &grass, &grass, &grass, &grass, &grassWaterTR, &grassWaterT, &grassWaterT, &waterGrassBL, &waterA1},
        {&grass, &grassA1, &grass, &grass, &grass, &grassA2, &grass, &grass, &grassWaterR, &water},
        {&grass, &grass, &grass, &grass, &grass, &grass, &grass, &grass, &grassWaterR, &water},
        {&grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterBL, &grass, &grassA2, &grassWaterR, &water},
        {&water, &waterA1, &water, &water, &water, &grassWaterL, &grass, &grass, &grassWaterR, &waterA2}
    },
    .objects = map2Objects,
    .numObjects = nummap2Objects,
    .leftMap = &startMap,
    .rightMap = NULL,
    .upMap = &cabinMap,
    .downMap = &map3,
};

struct map map3 = {
    .tiles = {
        {&water, &waterA1, &water, &water, &water, &grassWaterL, &grass, &grass, &grassWaterR, &water},
        {&water, &water, &water, &waterA1, &water, &grassWaterL, &grass, &grass, &grassWaterTR, &grassWaterT},
        {&water, &waterA2, &waterGrassBR, &grassWaterT, &grassWaterT, &grassWaterTL, &grass, &grassA2, &grass, &grass},
        {&water, &waterGrassBR, &grassWaterTL, &grass, &grass, &grassA1, &grass, &grass, &grass, &grass},
        {&waterGrassBR, &grassWaterTL, &grassA1, &grassWaterBR, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB},
        {&grassWaterL, &grass, &grass, &grassWaterR, &water, &waterA2, &water, &water, &water, &water},
        {&grassWaterL, &grass, &grass, &grassWaterR, &water, &water, &water, &water, &water, &water},
        {&grassWaterL, &grassA2, &grass, &grassWaterR, &waterA1, &water, &water, &water, &waterA1, &water}
    },
    .objects = map3Objects,
    .numObjects = nummap3Objects,
    .leftMap = NULL,
    .rightMap = &map4,
    .upMap = &map2,
    .downMap = &itemMap1,
};

struct map map4 = {
    .tiles = {
        {&water, &water, &waterA1, &water, &water, &water, &water, &water, &waterA1, &water},
        {&grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT},
        {&grass, &grass, &grass, &grass, &grass, &grassA1, &grass, &grass, &grass, &grass},
        {&grass, &grassA1, &grass, &grass, &grass, &grass, &grass, &grass, &grassA2, &grass},
        {&grassWaterBL, &grass, &grass, &grass, &grassWaterBR, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB},
        {&grassWaterL, &grass, &grass, &grass, &grassWaterR, &water, &water, &waterA2, &water, &water},
        {&grassWaterL, &grass, &grassA2, &grass, &grassWaterR, &water, &water, &water, &water, &water},
        {&grassWaterL, &grass, &grass, &grass, &grassWaterR, &waterA2, &water, &water, &waterA1, &water}
    },
    .objects = map4Objects,
    .numObjects = numMap4Objects,
    .leftMap = &map3,
    .rightMap = &itemMap3,
    .upMap = NULL,
    .downMap = &itemMap2,
};

struct map itemMap1 = {
    .tiles = {
        {&grassWaterL, &grass, &grass, &grassWaterR, &water, &water, &water, &water, &water, &water},
        {&grassWaterL, &grass, &grass, &grassWaterR, &water, &water, &waterA1, &water, &water, &water},
        {&grassWaterL, &grassA2, &grass, &grassWaterR, &water, &water, &water, &water, &water, &waterA2},
        {&grassWaterL, &grass, &grass, &grassWaterR, &water, &water, &waterA2, &water, &water, &water},
        {&grassWaterL, &grass, &grass, &grassWaterR, &water, &water, &water, &water, &water, &water},
        {&waterGrassTR, &grassWaterB, &grassWaterB, &waterGrassTL, &waterA1, &water, &water, &water, &waterA2, &water},
        {&water, &water, &water, &water, &water, &water, &water, &water, &water, &water},
        {&water, &waterA1, &water, &water, &water, &water, &water, &water, &waterA1, &water}
    },
    .objects = itemMap1Objects,
    .numObjects = numItemMap1Objects,
    .leftMap = NULL,
    .rightMap = NULL,
    .upMap = &map3,
    .downMap = NULL,
};

struct map itemMap2 = {
    .tiles = {
        {&grassWaterL, &grass, &grass, &grass, &grassWaterR, &waterA2, &water, &water, &water, &water},
        {&grassWaterL, &grassA2, &grass, &grass, &grassWaterR, &water, &water, &waterA1, &water, &water},
        {&grassWaterL, &grass, &grass, &grass, &grassWaterR, &water, &water, &water, &water, &water},
        {&grassWaterL, &grass, &grass, &grassA1, &grassWaterTR, &grassWaterT, &grassWaterT, &waterGrassBL, &water, &water},
        {&grassWaterL, &grass, &grass, &grass, &grass, &grass, &grass, &grassWaterR, &water, &waterA2},
        {&waterGrassTR, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &waterGrassTL, &water, &water},
        {&water, &water, &water, &water, &water, &water, &water, &water, &water, &water},
        {&water, &water, &water, &waterA1, &water, &water, &water, &water, &water, &waterA2}
    },
    .objects = itemMap2Objects,
    .numObjects = numItemMap2Objects,
    .leftMap = NULL,
    .rightMap = NULL,
    .upMap = &map4,
    .downMap = NULL,
};

struct map itemMap3 = {
    .tiles = {
        {&water, &waterA2, &water, &water, &water, &water, &waterA1, &water, &water, &water},
        {&grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &waterGrassBL, &water, &water, &water, &water, &waterA2},
        {&grass, &grassA2, &grass, &grass, &grassWaterR, &water, &water, &water, &water, &water},
        {&grass, &grass, &grass, &grass, &grassWaterR, &water, &water, &waterA1, &water, &water},
        {&grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &waterGrassTL, &water, &water, &water, &water, &water},
        {&water, &water, &water, &water, &water, &waterA2, &water, &water, &water, &water},
        {&water, &water, &water, &water, &water, &water, &water, &water, &water, &waterA1},
        {&water, &water, &waterA1, &water, &water, &waterA2, &water, &water, &water, &water}
    },
    .objects = itemMap3Objects,
    .numObjects = numItemMap3Objects,
    .leftMap = &map4,
    .rightMap = NULL,
    .upMap = NULL,
    .downMap = NULL,
};

struct map cabinMap = {
    .tiles = {
        {&waterA1, &water, &water, &water, &water, &water, &water, &water, &waterA1, &water},
        {&water, &waterGrassBR, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &waterGrassBL, &water},
        {&water, &grassWaterL, &grassA1, &grass, &grass, &grass, &grass, &grass, &grassWaterR, &water},
        {&water, &grassWaterL, &grass, &grass, &grass, &grass, &grass, &grassA1, &grassWaterR, &water},
        {&waterA2, &grassWaterL, &grass, &grass, &grass, &grass, &grass, &grass, &grassWaterR, &waterA2},
        {&water, &grassWaterL, &grass, &grassA2, &grass, &grass, &grass, &grass, &grassWaterR, &water},
        {&water, &grassWaterL, &grass, &grassWaterBR, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &waterGrassTL, &water},
        {&water, &grassWaterL, &grass, &grassWaterR, &water, &water, &waterA1, &water, &water, &water}
    },
    .objects = cabinMapObjects,
    .numObjects = numCabinMapObjects,
    .leftMap = NULL,
    .rightMap = NULL,
    .upMap = NULL,
    .downMap = &map2,
};