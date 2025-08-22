#include "interactableMap.h"

struct interactableObject sign1 = {
    .x = 60,
    .y = 32,
    .sprite = &sign,
    .numMessages = 1,
    .messages = {
        L"Welcome to Fishing! Use L to interact and start fishing K to close text boxes and I to open the menu",
    }
};

struct interactableObject sign4 = {
    .x = 65,
    .y = 100,
    .sprite = &sign,
    .numMessages = 1,
    .messages = {
        L"Interact with the rug (L) to leave",
    }
};

struct interactableObject sign5 = {
    .x = 128,
    .y = 60,
    .sprite = &sign,
    .numMessages = 1,
    .messages = {
        L"Interact with the shop (L) to enter",
    }
};

struct interactableObject shopBuilding = {
    .x = 64,
    .y = 0,
    .sprite = &shop,
    .numMessages = 1,
    .messages = {
        L"[1]",
    }
};

struct interactableObject frame1 = {
    .x = 42,
    .y = 0,
    .sprite = &fishFrame,
    .numMessages = 1,
    .messages = {
        L"[11]",
    }
};

struct interactableObject frame2 = {
    .x = 74,
    .y = 0,
    .sprite = &fishFrame,
    .numMessages = 1,
    .messages = {
        L"[12]",
    }
};

struct interactableObject frame3 = {
    .x = 106,
    .y = 0,
    .sprite = &fishFrame,
    .numMessages = 1,
    .messages = {
        L"[13]",
    }
};

struct interactableObject pcObj = {
    .x = 143,
    .y = 0,
    .sprite = &pc,
    .numMessages = 1,
    .messages = {
        L"[14]",
    }
};

struct interactableObject rugObj = {
    .x = 28,
    .y = 110,
    .sprite = &rug,
    .numMessages = 1,
    .messages = {
        L"[2]",
    }
};

struct interactableObject shopCounterObj = {
    .x = 128,
    .y = 48,
    .sprite = &shopCounter,
    .numMessages = 1,
    .messages = {
        L"[15]",
    }
};

struct interactableObject fishTankObj = {
    .x = 0,
    .y = 67,
    .sprite = &fishtank,
    .numMessages = 1,
    .messages = {
        L"[16]",
    }
};

struct interactableObject toiletObj = {
    .x = 112,
    .y = 55,
    .sprite = &toilet,
    .numMessages = 1,
    .messages = {
        L"[5]",
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
    &sign1
};

const int numstartObjects = sizeof(startObjects) / sizeof(startObjects[0]);

struct interactableObject* centralMapObjects[] = {
};

const int numCentralMapObjects = sizeof(centralMapObjects) / sizeof(centralMapObjects[0]);

struct interactableObject* shopIslandMapObjects[] = {
    &shopBuilding,
    &sign5
};

const int numShopIslandMapObjects = sizeof(shopIslandMapObjects) / sizeof(shopIslandMapObjects[0]);

struct interactableObject* dockMapObjects[] = {
};

const int numDockMapObjects = sizeof(dockMapObjects) / sizeof(dockMapObjects[0]);

struct interactableObject* shopMapObjects[] = {
    &sign4,
    &frame1,
    &frame2,
    &frame3,
    &pcObj,
    &rugObj,
    &shopCounterObj,
    &fishTankObj
};

const int numShopMapObjects = sizeof(shopMapObjects) / sizeof(shopMapObjects[0]);

struct interactableObject* bathroomMapObjects[] = {
    &toiletObj
};

const int numBathroomMapObjects = sizeof(bathroomMapObjects) / sizeof(bathroomMapObjects[0]);

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
    .upMap = &shopMap,
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

struct map shopMap = {
    .tiles = {
        {&woodWall, &woodTile, &woodWall, &woodWall, &woodWall, &woodWall, &woodWall, &woodWall, &woodWall, &woodWall},
        {&woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile},
        {&woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile},
        {&woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile},
        {&woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile},
        {&woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile},
        {&woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile},
        {&woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile}
    },
    .objects = shopMapObjects,
    .numObjects = numShopMapObjects,
    .leftMap = NULL,
    .rightMap = NULL,
    .upMap = &bathroomMap,
    .downMap = NULL,
};

struct map bathroomMap = {
    .tiles = {
        {&blackTile, &blackTile, &blackTile, &blackTile, &greyTile, &greyTile, &blackTile, &blackTile, &blackTile, &blackTile},
        {&blackTile, &blackTile, &blackTile, &blackTile, &greyTile, &greyTile, &blackTile, &blackTile, &blackTile, &blackTile},
        {&blackTile, &blackTile, &blackTile, &blackTile, &greyTile, &greyTile, &blackTile, &blackTile, &blackTile, &blackTile},
        {&blackTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &blackTile, &blackTile},
        {&blackTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &woodTile, &blackTile, &blackTile},
        {&blackTile, &woodTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile},
        {&blackTile, &woodTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile},
        {&blackTile, &woodTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile, &blackTile}
    },
    .objects = bathroomMapObjects,
    .numObjects = numBathroomMapObjects,
    .leftMap = NULL,
    .rightMap = NULL,
    .upMap = &sprigRoom,
    .downMap = &shopMap,
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
    .downMap = &bathroomMap,
};