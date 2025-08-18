#include "game_state.h"
#include "player.h"
#include "interactableMap.h"
#include "global.h"


static struct map (*currentMap) = &startMap;

// Fish data implementation
const fish_data_t fish_data[FISH_COUNT] = {
    [FISH_CLOWN] = {
        .name = "Clown Fish",
        .weight = {0.2f, 2.0f},
        .texture = &fish_clown,
        .description = "A small, brightly colored reef fish often found living among sea anemones"
    },
    [FISH_COD] = {
        .name = "Cod",
        .weight = {0.5f, 3.0f},
        .texture = &fish_cod,
        .description = "A cold-water fish that thrives in deep seas and northern waters\nCod is prized for its mild flavor and is a key species in many global fisheries"
    },
    [FISH_SALMON] = {
        .name = "Salmon",
        .weight = {1.0f, 5.0f},
        .texture = &fish_salmon,
        .description = "Known for its legendary upriver journeys, Salmon shows great determination in both migration and flavor"
    },
    [FISH_PUFFERFISH] = {
        .name = "Pufferfish",
        .weight = {0.3f, 1.5f},
        .texture = &fish_pufferfish,
        .description = "This fish inflates to defend itself, surprising predators\nHandle with care"
    },
    [FISH_TUNA] = {
        .name = "Tuna",
        .weight = {2.0f, 10.0f},
        .texture = &fish_tuna,
        .description = "A powerful and fast-swimming fish known to traverse great distances"
    },
    [FISH_SEA_BASS] = {
        .name = "Sea Bass",
        .weight = {1.5f, 6.0f},
        .texture = &fish_sea_bass,
        .description = "The most common catch of the day. Sea Bass is well-known for biting often... maybe too often"
    },
    [FISH_CATFISH] = {
        .name = "Catfish",
        .weight = {1.0f, 8.0f},
        .texture = &fish_catfish,
        .description = "Named for its whisker-like barbels, this bottom-dweller can grow surprisingly large"
    },
    [FISH_PIG_FISH] = {
        .name = "Pig Fish",
        .weight = {3.0f, 12.0f},
        .texture = &fish_pig_fish,
        .description = "This fish doesn't know how to get food for itself, but it has a whole school behind it giving it the best food they can"
    },
    [FISH_SINGING_FISH] = {
        .name = "Singing Fish",
        .weight = {1.0f, 4.0f},
        .texture = &fish_singing_fish,
        .description = "This fish is known all across the ocean for its incredible singing voice and hit line of rhythm games based off of its songs"
    },
    [FISH_MACHINE_FISH] = {
        .name = "Machine Fish",
        .weight = {5.0f, 15.0f},
        .texture = &fish_machine_fish,
        .description = "This fish is extremely fast with some researchers claiming it's able to do something called a \"Slam Storage\" to boost to amazing speeds"
    },
    [FISH_DRIMP] = {
        .name = "Drimp",
        .weight = {0.5f, 2.5f},
        .texture = &fish_drimp,
        .description = "Drimp has been stated to be quite cruel to other fish in it's area, but is sought after for it's decorative properties.\n\"Wow, Drimp is doing very good this week\" - Stock Analysts"
    },
    [FISH_SHARK] = {
        .name = "Shark",
        .weight = {10.0f, 50.0f},
        .texture = &fish_shark,
        .description = "The apex predator of the sea\nBut this one kinda looks cute and cuddly"
    },
    [FISH_ORPHEUS] = {
        .name = "Orpheus",
        .weight = {2.0f, 6.0f},
        .texture = &fish_orpheus,
        .description = "This curious dino is never found far from a computer, or the bottom right of your console..."
    },
    [FISH_AT_FISH] = {
        .name = "@Fish",
        .weight = {0.1f, 1.0f},
        .texture = &fish_at_fish,
        .description = "The real ones are in fish-channel"
    },
    [FISH_MAGICAL_FROG] = {
        .name = "Magical Frog",
        .weight = {0.2f, 0.8f},
        .texture = &fish_magical_frog,
        .description = "This magical frog is stated to love games and loves to see more of them get made"
    }
};

void initGameState(void) {
    currentMap = &startMap;
}

struct map* getCurrentMap(void) {
    return currentMap;
}

void setCurrentMap(struct map* map) {
    currentMap = map;
}

void handleMapTransitions(void) {
    const int SCREEN_WIDTH = 160;
    const int SCREEN_HEIGHT = 128;

    const int PLAYER_WIDTH = 16;
    const int PLAYER_HEIGHT = 20;
    
    // Check if player walks off right edge
    if (player.x > SCREEN_WIDTH && currentMap->rightMap != NULL) {
        currentMap = currentMap->rightMap;
        player.x = 0;
    }
    // Check if player walks off left edge
    else if (player.x < -PLAYER_WIDTH && currentMap->leftMap != NULL) {
        currentMap = currentMap->leftMap;
        player.x = SCREEN_WIDTH - PLAYER_WIDTH; 
    }
    // Check if player walks off bottom edge
    else if (player.y + 5 > SCREEN_HEIGHT && currentMap->downMap != NULL) {
        currentMap = currentMap->downMap;
        player.y = 0; 
    }
    // Check if player walks off top edge
    else if (player.y < -PLAYER_HEIGHT && currentMap->upMap != NULL) {
        currentMap = currentMap->upMap;
        player.y = SCREEN_HEIGHT - PLAYER_HEIGHT; 
    }
}
