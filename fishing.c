#include "fishing.h"
#include "global.h"
#include "textbox.h"
#include <stdbool.h>
#include <math.h>
#include <wchar.h>
#include <stdio.h>


fish_list selectFish(void) {
    fish_list common_fish[] = {
        FISH_CLOWN, FISH_COD, FISH_SALMON, FISH_PUFFERFISH, FISH_TUNA,
        FISH_SEA_BASS, FISH_CATFISH
    };

    fish_list rare_fish[] = {
        FISH_PIG_FISH, FISH_SINGING_FISH, FISH_MACHINE_FISH, FISH_DRIMP,
        FISH_SHARK
    };

    fish_list hack_rare[] = {
        FISH_ORPHEUS, FISH_AT_FISH, FISH_MAGICAL_FROG
    };

    int roll = rand() % 100;

    if (roll >= (95 - rarityIncrease*2)) { // 5% Hack Rare
        int random_index = rand() % (sizeof(hack_rare) / sizeof(hack_rare[0]));
        return hack_rare[random_index];
    } else if (roll >= (75 - rarityIncrease*5)) { // 20% Rare
        int random_index = rand() % (sizeof(rare_fish) / sizeof(rare_fish[0]));
        return rare_fish[random_index];
    } else { // 75% Common
        int random_index = rand() % (sizeof(common_fish) / sizeof(common_fish[0]));
        return common_fish[random_index];
    }
}

float generateFishWeight(weight_range_t weight_range, int roll) {
    float weight = weight_range.min_weight + pow(roll / 100.0, 2.5) * (weight_range.max_weight - weight_range.min_weight);
    return weight;
}

int generateFishPrice(fish_list fish_type, int roll) {
    float price = 2 + pow(roll / 100.0, 2.5) * 48;

    if (fish_type > 6) {
        if (fish_type > 11) {
            price *= 3.0; // Increase price for hack rare fish
        } else {
            price *= 2.0; // Increase price for rare fish
        }
    }

    return (int)price;
}

void catchFish(void) {
    fish_list fish_caught = selectFish();
    fish_data_t fish_info = fish_data[fish_caught];

    int roll = rand() % 100;
    roll += weightIncrease * 10;

    float weight = generateFishWeight(fish_info.weight, roll);
    int price = generateFishPrice(fish_caught, roll);
    wchar_t message[100];
    swprintf(message, sizeof(message), L"You caught a %s weighing %.2f kg! It sold for $%d", fish_info.name, weight, price);

    money += price;
    fishTimesCaught[fish_caught]++;
    allFishTimesCaught++;

    if (fishMaxWeight[fish_caught] < weight) {
        fishMaxWeight[fish_caught] = weight;
    }

    game_state = GAME_STATE_TEXTBOX;
    globalCaughtFish = fish_caught;
    parseMessage(message);
}

void fishingProcess(void) {
    if (rand() % (120 - catchSpeedIncrease*5) == 0) {
        fish_hooked = true;
        printf("FISH TIME IDIOT");
        // make timer happen
    }

}