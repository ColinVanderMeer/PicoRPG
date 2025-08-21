#include "textbox.h"
#include "player.h"
#include "interactableMap.h"
#include "game_state.h"
#include "fonts.h"
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "global.h"
#include "game_state.h"

wchar_t textLine1[26] = L"";
wchar_t textLine2[26] = L"";
wchar_t textLine3[26] = L"";
wchar_t textLine4[26] = L"";

bool doorOpeningActive = false;
static uint64_t doorOpeningStartTime = 0;
static const uint64_t DOOR_OPENING_DURATION_US = 5000000; // 5 seconds in microseconds

// Execute special functions based on number codes
void executeFunction(int functionCode) {
    switch (functionCode) {
        case 1: // Enter shop
            currentMap = currentMap->upMap;
            player.x = 39;
            player.y = 100; 
            game_state = GAME_STATE_NORMAL;
            break;
        case 2: // Exit shop
            currentMap = &shopIslandMap;
            player.x = 104;
            player.y = 43;
            game_state = GAME_STATE_NORMAL;
            break;

        case 11:
            printf("Displaying fish 1\n");
            fishDisplay(0);
            break;
        case 12:
            fishDisplay(1);
            break;
        case 13:
            fishDisplay(2);
            break;
        default:
            // Unknown function code, do nothing
            break;
    }
}

void fishDisplay(int frameNum) {
    printf("We enter the function");
    
    globalCaughtFish = fishDisplayFish[frameNum];
    printf("Globalfish: %d\n", globalCaughtFish);
    
    swprintf(textLine1, 26, L"%hs", fish_data[globalCaughtFish].name);
    printf("Line1");
    swprintf(textLine2, 26, L"Times Caught: %d", fishTimesCaught[globalCaughtFish]);
    printf("Line2");
    swprintf(textLine3, 26, L"Max Weight: %.2fkg", fishMaxWeight[globalCaughtFish]);
    printf("Line3");
}

// Parse message and handle special functions while formatting text
void parseMessage(const wchar_t* message) {
    // Clear all text lines
    wcscpy(textLine1, L"");
    wcscpy(textLine2, L"");
    wcscpy(textLine3, L"");
    wcscpy(textLine4, L"");
    
    wchar_t* lines[4] = {textLine1, textLine2, textLine3, textLine4};
    int currentLine = 0;
    int currentPos = 0;
    const int maxLineLength = 25;
    
    for (int i = 0; message[i] != L'\0' && currentLine < 4; i++) {
        if (message[i] == L'[') {
            // Look for closing bracket
            int j = i + 1;
            while (message[j] != L'\0' && message[j] != L']') {
                j++;
            }
            
            if (message[j] == L']') {
                // Extract the number between brackets
                wchar_t functionCodeStr[10] = L"";
                int codeLength = j - i - 1;
                if (codeLength < 10) {
                    wcsncpy(functionCodeStr, &message[i + 1], codeLength);
                    functionCodeStr[codeLength] = L'\0';
                    
                    // Convert to integer and execute function
                    int functionCode = wcstol(functionCodeStr, NULL, 10);
                    executeFunction(functionCode);
                }
                
                // Skip past the closing bracket
                i = j;
                continue;
            }
        }
        
        // Regular character - add to current line
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
            if (currentLine < 4) {
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
    
    // Pad remaining space in lines with spaces for consistent display
    for (int line = 0; line < 4; line++) {
        int len = wcslen(lines[line]);
        for (int pos = len; pos < maxLineLength; pos++) {
            lines[line][pos] = L' ';
        }
        lines[line][maxLineLength] = L'\0';
    }
}

void interactObject(void) {
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
            game_state = GAME_STATE_TEXTBOX;
            // Parse the message and handle any special function codes
            parseMessage(currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber]);

            if (currentMap->objects[i]->messageNumber < currentMap->objects[i]->numMessages - 1) {
                currentMap->objects[i]->messageNumber++;
            }
            // If interacted with an object, stop here
            return;
        }
    }

    // If no object was interacted with, check the tile immediately in front for water
    {
        const int TILE_SIZE = 16;
        int checkX = (int)player.x;
        int checkY = (int)player.y;

        switch (player.direction) {
            case 0: // Up
                checkX += 8;
                checkY -= 1;
                break;
            case 1: // Left
                checkX -= 1;
                checkY += 10;
                break;
            case 2: // Down
                checkX += 8;
                checkY += 20;
                break;
            case 3: // Right
                checkX += 16;
                checkY += 10;
                break;
        }

        int tileX = checkX / TILE_SIZE;
        int tileY = checkY / TILE_SIZE;

        if (tileX >= 0 && tileX < 10 && tileY >= 0 && tileY < 8) {
            hagl_bitmap_t *tile = currentMap->tiles[tileY][tileX];
            if (isWaterTile(tile)) {
                game_state = GAME_STATE_FISHING;
            }
        }
    }
}

void renderTextBox(hagl_backend_t *display) {
    hagl_color_t color = 0xffff;
    hagl_fill_rounded_rectangle_xyxy(display, 2, 82, 157, 125, 5, 0x0000);
    hagl_draw_rounded_rectangle_xyxy(display, 2, 82, 157, 125, 5, color);
    hagl_put_text(display, textLine1, 5, 85, color, font6x9);
    hagl_put_text(display, textLine2, 5, 95, color, font6x9);
    hagl_put_text(display, textLine3, 5, 105, color, font6x9);
    hagl_put_text(display, textLine4, 5, 115, color, font6x9);
}

void updateTextBoxTimer(void) {
    if (doorOpeningActive) {
        uint64_t currentTime = time_us_64();
        if (currentTime - doorOpeningStartTime >= DOOR_OPENING_DURATION_US) {
            // 5 seconds have passed, teleport player to sprigRoom
            doorOpeningActive = false;
            game_state = GAME_STATE_NORMAL;
            setCurrentMap(&sprigRoom);
            // Set player position in the center of the new room
            player.x = 74;  // Center of 160px wide screen
            player.y = 104;  // Center of 128px high screen
        }
    }
}
