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

struct interactableObject* startObjects[] = {
    &sign1,
    &sign2,
};

const int numstartObjects = sizeof(startObjects) / sizeof(startObjects[0]);

struct interactableObject* map2Objects[] = {
    &sign3,
    &morayObj,
};

const int nummap2Objects = sizeof(map2Objects) / sizeof(map2Objects[0]);

struct interactableObject* map3Objects[] = {
    &lucasObj,
};

const int nummap3Objects = sizeof(map3Objects) / sizeof(map3Objects[0]);

struct interactableObject* map4Objects[] = {
};

const int numMap4Objects = sizeof(map4Objects) / sizeof(map4Objects[0]);

struct interactableObject* itemMap1Objects[] = {
};

const int numItemMap1Objects = sizeof(itemMap1Objects) / sizeof(itemMap1Objects[0]);

struct interactableObject* itemMap2Objects[] = {
};

const int numItemMap2Objects = sizeof(itemMap2Objects) / sizeof(itemMap2Objects[0]);

struct interactableObject* itemMap3Objects[] = {
};

const int numItemMap3Objects = sizeof(itemMap3Objects) / sizeof(itemMap3Objects[0]);


struct map startMap = {
    .tiles = {
        {&water, &water, &waterA1, &waterGrassBR, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT, &grassWaterT},
        {&water, &water, &waterGrassBR, &grassWaterTL, &grassA1, &grass, &grass, &grass, &grass, &grassA2},
        {&water, &waterA2, &grassWaterL, &grass, &grass, &grass, &grassA2, &grass, &grass, &grass},
        {&water, &water, &grassWaterL, &grassA1, &grass, &grass, &grass, &grass, &grass, &grass},
        {&waterA1, &water, &grassWaterL, &grass, &grass, &grass, &grassA2, &grass, &grass, &grass},
        {&water, &water, &grassWaterL, &grass, &grass, &grassA1, &grass, &grass, &grass, &grass},
        {&water, &waterA2, &waterGrassTR, &grassWaterBL, &grass, &grass, &grass, &grass, &grass, &grassA1},
        {&water, &water, &water, &waterGrassTR, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB, &grassWaterB}
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
    .upMap = NULL,
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