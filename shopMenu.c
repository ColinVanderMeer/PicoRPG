#include "shopMenu.h"
#include "save_system.h"
#include "graphics_data.h"
#include "audio.h"
#include "pico/stdlib.h"
#include "fonts.h"
#include "global.h"
#include <wchar.h>

int rodPrice = 500;
int baitPrice = 300;
int luckPrice = 400;

void shopMenu(hagl_backend_t *display) {
    wchar_t moneyText[12];
    swprintf(moneyText, sizeof(moneyText), L"Money: $%d", money);

    wchar_t rodCostText[12];
    wchar_t rodHaveText[12];
    
    wchar_t baitCostText[12];
    wchar_t baitHaveText[12];
    
    wchar_t luckCostText[12];
    wchar_t luckHaveText[12];
    
    int selection = 0;
    int butPressed = 1;
    hagl_fill_rounded_rectangle_xyxy(display, 2, 2, 118, 125, 5, 0x0000);
    hagl_draw_rounded_rectangle_xyxy(display, 2, 2, 118, 125, 5, 0xffff);
    hagl_put_text(display, L"Shop", 5, 5, 0xffff, font6x9);
    hagl_put_text(display, L"Exit", 17, 112, 0xffff, font6x9);

    
    hagl_put_text(display, L"Buy Rod Upgrade", 17, 22, 0xffff, font6x9);
    hagl_put_text(display, L"Buy Bait Upgrade", 17, 52, 0xffff, font6x9);
    hagl_put_text(display, L"Buy Luck Upgrade", 17, 82, 0xffff, font6x9);
    
    while (1) { // This is a weird backwards way to handle this, but I think it actually works well? So it'll stay until it causes a catastrophic failure.
        rodPrice = 500 + catchSpeedIncrease * 500;
        baitPrice = 500 + weightIncrease * 500;
        luckPrice = 500 + rarityIncrease * 500;

        hagl_fill_rectangle_xyxy(display, 90, 6, 116, 15, 0x0000);
        swprintf(moneyText, sizeof(moneyText), L"Money: $%d", money);
        hagl_put_text(display, moneyText, 42, 5, 0xffff, font6x9);

        swprintf(rodCostText, sizeof(rodCostText), L"Cost: $%d", rodPrice);
        swprintf(rodHaveText, sizeof(rodHaveText), L"Have: %d", catchSpeedIncrease);
        if (catchSpeedIncrease >= 5) {
            swprintf(rodCostText, sizeof(rodCostText), L"SOLD OUT");
            swprintf(rodHaveText, sizeof(rodHaveText), L"Have: MAX");
        }

        swprintf(baitCostText, sizeof(baitCostText), L"Cost: $%d", baitPrice);
        swprintf(baitHaveText, sizeof(baitHaveText), L"Have: %d", weightIncrease);
        if (weightIncrease >= 5) {
            swprintf(baitCostText, sizeof(baitCostText), L"SOLD OUT");
            swprintf(baitHaveText, sizeof(baitHaveText), L"Have: MAX");
        }

        swprintf(luckCostText, sizeof(luckCostText), L"Cost: $%d", luckPrice);
        swprintf(luckHaveText, sizeof(luckHaveText), L"Have: %d", rarityIncrease);
        if (rarityIncrease >= 5) {
            swprintf(luckCostText, sizeof(luckCostText), L"SOLD OUT");
            swprintf(luckHaveText, sizeof(luckHaveText), L"Have: MAX");
        }

        hagl_fill_rectangle_xyxy(display, 9, 20, 16, 120, 0x0000);
        hagl_blit_xy(display, 9, 22 + selection * 30, &selector);

        hagl_put_text(display, rodCostText, 41, 32, 0xffff, font6x9);
        hagl_put_text(display, rodHaveText, 41, 42, 0xffff, font6x9);
        hagl_put_text(display, baitCostText, 41, 62, 0xffff, font6x9);
        hagl_put_text(display, baitHaveText, 41, 72, 0xffff, font6x9);
        hagl_put_text(display, luckCostText, 41, 92, 0xffff, font6x9);
        hagl_put_text(display, luckHaveText, 41, 102, 0xffff, font6x9);

        if (!gpio_get(5) && !butPressed) {
            selection--;
            if (selection < 0) {
                selection = 3;
            }
        }
        if (!gpio_get(7) && !butPressed) {
            selection++;
            if (selection > 3) {
                selection = 0;
            }
        }

        if (!gpio_get(15) && !butPressed) {
            switch (selection) {
                case 0:
                    while (!gpio_get(15)) {}
                    if (money >= rodPrice && rodPrice != 0) {
                        money -= rodPrice;
                        catchSpeedIncrease++;
                    }
                    break;
                case 1:
                    while (!gpio_get(15)) {}
                    if (money >= baitPrice && baitPrice != 0) {
                        money -= baitPrice;
                        weightIncrease++;
                    }
                    break;
                case 2:
                    while (!gpio_get(15)) {}
                    if (money >= luckPrice && luckPrice != 0) {
                        money -= luckPrice;
                        rarityIncrease++;
                    }
                    break;
                case 3:
                    while (!gpio_get(15)) {}
                    game_state = GAME_STATE_NORMAL;
                    return;
            }
        }
        if (!gpio_get(14) && !butPressed) {
            game_state = GAME_STATE_NORMAL;
            return;
        }

        if (!gpio_get(5) || !gpio_get(7) || !gpio_get(14) || !gpio_get(15)) {
            butPressed = 1;
        } else {
            butPressed = 0;
        }

        update_mod_player();

        hagl_flush(display);

    }
}
