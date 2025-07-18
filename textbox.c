#include "textbox.h"
#include "player.h"
#include "interactableMap.h"
#include "game_state.h"
#include "fonts.h"
#include <wchar.h>
#include <string.h>

wchar_t textLine1[26] = L"";
wchar_t textLine2[26] = L"";
wchar_t textLine3[26] = L"";
wchar_t textLine4[26] = L"";

static bool textBoxActive = false;

bool isTextBoxActive(void) {
    return textBoxActive;
}

void setTextBoxActive(bool active) {
    textBoxActive = active;
}

void interactObject(hagl_backend_t *display) {
    struct map* currentMap = getCurrentMap();
    int playerBoxX1 = player.x;
    int playerBoxX2 = player.x;
    int playerBoxY1 = player.y;
    int playerBoxY2 = player.y;
    switch (player.direction) {
        case 0:
            playerBoxY1 -= 30;
            playerBoxX1 -= 5;
            playerBoxX2 += 25;
            break;
        case 1:
            playerBoxX1 -= 30;
            playerBoxY1 += 5;
            playerBoxY2 += 35;
            break;
        case 2:
            playerBoxY1 += 30;
            playerBoxY2 += 60;
            playerBoxX2 += 25;
            playerBoxX1 -= 5;
            break;
        case 3:
            playerBoxX1 += 20;
            playerBoxX2 += 50;
            playerBoxY1 += 5;
            playerBoxY2 += 35;
            break;
    }
    for (int i = 0; i < currentMap->numObjects; i++) {
        if (
            playerBoxX1 < currentMap->objects[i]->x + currentMap->objects[i]->sprite->width &&
            playerBoxX2 > currentMap->objects[i]->x &&
            playerBoxY1 < currentMap->objects[i]->y + currentMap->objects[i]->sprite->height &&
            playerBoxY2 > currentMap->objects[i]->y
        ) {
            textBoxActive = true;
            // TODO: This code sucks, it is atrociously bad. If you are reading this code right now and know how to make it better, please submit a PR.
            int messageLength = wcslen(currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber]);
            if (messageLength < 26) {
                wcscpy(textLine1, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber]);
                wcscpy(textLine2, L"                         ");
                wcscpy(textLine3, L"                         ");
                wcscpy(textLine4, L"                         ");
            } else if (messageLength < 52) {
                wcscpy(textLine1, wcsncpy(textLine1, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber], 25));
                if (currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber][25] == ' ') {
                    wcscpy(textLine2, wcsncpy(textLine2, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 26, 25));
                } else {
                    wcscpy(textLine2, wcsncpy(textLine2, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 25, 25));
                }
                wcscpy(textLine3, L"                         ");
                wcscpy(textLine4, L"                         ");
            } else if (messageLength < 78) {
                wcscpy(textLine1, wcsncpy(textLine1, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber], 25));
                if (currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber][25] == ' ') {
                    wcscpy(textLine2, wcsncpy(textLine2, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 26, 25));
                    if (currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber][51] == ' ') {
                        wcscpy(textLine3, wcsncpy(textLine3, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 52, 25));
                    } else {
                        wcscpy(textLine3, wcsncpy(textLine3, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 51, 25));
                    }
                } else {
                    wcscpy(textLine2, wcsncpy(textLine2, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 25, 25));
                    if (currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber][50] == ' ') {
                        wcscpy(textLine3, wcsncpy(textLine3, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 51, 25));
                    } else {
                        wcscpy(textLine3, wcsncpy(textLine3, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 50, 25));
                    }
                }
                wcscpy(textLine4, L"                         ");
            } else {
                wcscpy(textLine1, wcsncpy(textLine1, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber], 25));
                if (currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber][25] == ' ') {
                    wcscpy(textLine2, wcsncpy(textLine2, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 26, 25));
                    if (currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber][51] == ' ') {
                        wcscpy(textLine3, wcsncpy(textLine3, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 52, 25));
                        if (currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber][77] == ' ') {
                            wcscpy(textLine4, wcsncpy(textLine4, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 78, 25));
                        } else {
                            wcscpy(textLine4, wcsncpy(textLine4, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 77, 25));
                        }
                    } else {
                        wcscpy(textLine3, wcsncpy(textLine3, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 51, 25));
                        if (currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber][76] == ' ') {
                            wcscpy(textLine4, wcsncpy(textLine4, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 77, 25));
                        } else {
                            wcscpy(textLine4, wcsncpy(textLine4, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 76, 25));
                        }
                    }
                } else {
                    wcscpy(textLine2, wcsncpy(textLine2, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 25, 25));
                    if (currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber][50] == ' ') {
                        wcscpy(textLine3, wcsncpy(textLine3, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 51, 25));
                        if (currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber][76] == ' ') {
                            wcscpy(textLine4, wcsncpy(textLine4, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 77, 25));
                        } else {
                            wcscpy(textLine4, wcsncpy(textLine4, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 76, 25));
                        }
                    } else {
                        wcscpy(textLine3, wcsncpy(textLine3, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 50, 25));
                        if (currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber][75] == ' ') {
                            wcscpy(textLine4, wcsncpy(textLine4, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 76, 25));
                        } else {
                            wcscpy(textLine4, wcsncpy(textLine4, currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber] + 75, 25));
                        }
                    }
                }
            }

            if (currentMap->objects[i]->messageNumber < currentMap->objects[i]->numMessages - 1) {
                currentMap->objects[i]->messageNumber++;
            } else {
                continue;
            }
        }
    }
}

void renderTextBox(hagl_backend_t *display) {
    if (textBoxActive) {
        hagl_color_t color = 0xffff;
        hagl_fill_rounded_rectangle_xyxy(display, 2, 82, 157, 125, 5, 0x0000);
        hagl_draw_rounded_rectangle_xyxy(display, 2, 82, 157, 125, 5, color);
        hagl_put_text(display, textLine1, 5, 85, color, font6x9);
        hagl_put_text(display, textLine2, 5, 95, color, font6x9);
        hagl_put_text(display, textLine3, 5, 105, color, font6x9);
        hagl_put_text(display, textLine4, 5, 115, color, font6x9);
    }
}
