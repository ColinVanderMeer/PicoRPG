#include "pcInterface.h"
#include "graphics_data.h"
#include "audio.h"
#include "pico/stdlib.h"
#include "fonts.h"
#include "global.h"
#include "rendering.h"
#include "game_state.h"
#include <wchar.h>
#include <stdio.h>

void infoScreen(hagl_backend_t *display, int fishIndex) {
    int butPressed = 1;

    wchar_t weightLine[10] = L"";

    wchar_t infoLine1[16] = L"";
    wchar_t infoLine2[16] = L"";
    wchar_t infoLine3[16] = L"";
    wchar_t infoLine4[16] = L"";
    wchar_t infoLine5[16] = L"";
    wchar_t infoLine6[16] = L"";
    wchar_t infoLine7[16] = L"";
    wchar_t infoLine8[16] = L"";
    wchar_t infoLine9[16] = L"";
    wchar_t infoLine10[16] = L"";
    wchar_t infoLine11[16] = L"";
    wchar_t infoLine12[16] = L"";
    
    
    hagl_fill_rounded_rectangle_xyxy(display, 0, 0, 159, 127, 5, 0x0000); // Go back to black because apparently hagl can only render text with a black background
    hagl_draw_rounded_rectangle_xyxy(display, 0, 0, 159, 127, 5, 0xe0da);
    
    renderScaledSprite(display, 15, 10, fish_data[fishIndex].texture, 4);

    hagl_put_text(display, L"Weight:", 5, 49, 0xffff, font6x9);
    swprintf(weightLine, 10, L"%.2f Kg", fishMaxWeight[fishIndex]);
    hagl_put_text(display, weightLine, 5, 59, 0xffff, font6x9);
    wchar_t message[200];
    swprintf(message, 200, L"%hs", fish_data[fishIndex].description);

    wchar_t* lines[12] = {infoLine1, infoLine2, infoLine3, infoLine4, infoLine5, infoLine6, infoLine7, infoLine8, infoLine9, infoLine10, infoLine11, infoLine12};
    int currentLine = 0;
    int currentPos = 0;
    const int maxLineLength = 15;
    for (int i = 0; message[i] != L'\0' && currentLine < 12; i++) {
        if (currentPos < maxLineLength) {
            // Skip leading spaces on any line
            if (currentPos == 0 && message[i] == L' ') {
                continue;
            }
            lines[currentLine][currentPos] = message[i];
            lines[currentLine][currentPos + 1] = L'\0';
            currentPos++;
        } else {
            // Move to next line
            currentLine++;
            if (currentLine < 12) {
                currentPos = 0;
                // Skip leading spaces on new line
                if (message[i] == L' ') {
                    continue;
                }
                lines[currentLine][currentPos] = message[i];
                lines[currentLine][currentPos + 1] = L'\0';
                currentPos++;
            }
        }
    }
    hagl_put_text(display, infoLine1, 62, 3, 0xffff, font6x9);
    hagl_put_text(display, infoLine2, 62, 13, 0xffff, font6x9);
    hagl_put_text(display, infoLine3, 62, 23, 0xffff, font6x9);
    hagl_put_text(display, infoLine4, 62, 33, 0xffff, font6x9);
    hagl_put_text(display, infoLine5, 62, 43, 0xffff, font6x9);
    hagl_put_text(display, infoLine6, 62, 53, 0xffff, font6x9);
    hagl_put_text(display, infoLine7, 62, 63, 0xffff, font6x9);
    hagl_put_text(display, infoLine8, 62, 73, 0xffff, font6x9);
    hagl_put_text(display, infoLine9, 62, 83, 0xffff, font6x9);
    hagl_put_text(display, infoLine10, 62, 93, 0xffff, font6x9);
    hagl_put_text(display, infoLine11, 62, 103, 0xffff, font6x9);
    hagl_put_text(display, infoLine12, 62, 113, 0xffff, font6x9);

    hagl_put_text(display, L"Display:", 5, 76, 0xffff, font6x9);
    hagl_put_text(display, L"Frame 1", 15, 86, 0xffff, font6x9);
    hagl_put_text(display, L"Frame 2", 15, 96, 0xffff, font6x9);
    hagl_put_text(display, L"Frame 3", 15, 106, 0xffff, font6x9);
    hagl_put_text(display, L"Exit", 15, 116, 0xffff, font6x9);

    int selection = 0;

    while (1) {
        hagl_fill_rectangle_xyxy(display, 7, 86, 14, 125, 0x0000);
        hagl_blit_xy(display, 7, 86 + selection*10, &selector);

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
            if (selection == 3) {
                return;
            }

            fishDisplayFish[selection] = fishIndex;
        }
        if (!gpio_get(14)) {
            return;
        }

        if (!gpio_get(5) || !gpio_get(7) || !gpio_get(15) || !gpio_get(14)) { // double press / instant press prevention
            butPressed = 1;
        } else {
            butPressed = 0;
        }

        update_mod_player();
        hagl_flush(display);
    }
}

void pcInterface(hagl_backend_t *display) {
    int selectorPosX = 0;
    int selectorPosY = 0;
    int selectionV = 0;
    int selectionH = 0;
    int butPressed = 1; // Start assuming a button has been pressed so that it doesn't immediately select a fish

    while (1) {
        hagl_fill_rounded_rectangle_xyxy(display, 0, 0, 159, 127, 5, 0x0028);
        hagl_draw_rounded_rectangle_xyxy(display, 0, 0, 159, 127, 5, 0xe0da);
        // printf("COLOR = %06X\n", hagl_color(display, 40, 0, 0));
        // printf("COLOR2 = %06X\n", hagl_color(display, 221, 92, 7));

        for (int i = 0; i < FISH_COUNT; i++) {
            if (fishTimesCaught[i]) {
                int yOffset = i / 4;
                int xOffset = i % 4;
                renderScaledSprite(display, (xOffset * 36) + 13, (yOffset * 30) + 5, fish_data[i].texture, 3);
            }
        }
        renderScaledSprite(display, 121, 95, &leave, 3);
        
        if (!gpio_get(5) && !butPressed) {
            selectionV--;
            if (selectionV < 0) {
                selectionV = 3;
            }
        }
        if (!gpio_get(7) && !butPressed) {
            selectionV++;
            if (selectionV > 3) {
                selectionV = 0;
            }
        }

        if (!gpio_get(6) && !butPressed) {
            selectionH--;
            if (selectionH < 0) {
                selectionH = 3;
            }
        }
        if (!gpio_get(8) && !butPressed) {
            selectionH++;
            if (selectionH > 3) {
                selectionH = 0;
            }
        }

        selectorPosX = 10 + selectionH * 36;
        selectorPosY = 2 + selectionV * 30;

        hagl_draw_rounded_rectangle_xywh(display, selectorPosX, selectorPosY, 30, 30, 5, 0xe0da);

        if (!gpio_get(15) && !butPressed) {
            int selection = selectionV * 4 + selectionH;
            if (selection == 15) {
                game_state = GAME_STATE_NORMAL;
                return;
            }

            if (fishTimesCaught[selection]) {
                infoScreen(display, selection);
                butPressed = 1;
            }
        }
        if (!gpio_get(14) && !butPressed) {
            game_state = GAME_STATE_NORMAL;
            return;
        }

        if (!gpio_get(5) || !gpio_get(7) || !gpio_get(6) || !gpio_get(8) || !gpio_get(15) || !gpio_get(14)) { // double press / instant press prevention
            butPressed = 1;
        } else {
            butPressed = 0;
        }

        update_mod_player();
        
        hagl_flush(display);
    }
}
