#include "textbox.h"
#include "player.h"
#include "interactableMap.h"
#include "game_state.h"
#include "fonts.h"
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"

wchar_t textLine1[26] = L"";
wchar_t textLine2[26] = L"";
wchar_t textLine3[26] = L"";
wchar_t textLine4[26] = L"";

static bool textBoxActive = false;
bool doorOpeningActive = false;
static uint64_t doorOpeningStartTime = 0;
static const uint64_t DOOR_OPENING_DURATION_US = 5000000; // 5 seconds in microseconds

// Execute special functions based on number codes
void executeFunction(int functionCode) {
    switch (functionCode) {
        case 0:
            wcscpy(player.inventory[player.inventory_count].name, L"Carrot");
            player.inventory_count++;
            break;
        case 1:
            wcscpy(player.inventory[player.inventory_count].name, L"Wheat");
            player.inventory_count++;
            break;
        case 2:
            wcscpy(player.inventory[player.inventory_count].name, L"Rock");
            player.inventory_count++;
            break;
        case 3:
            if (player.inventory_count == 3) {
                // Start the door opening sequence
                wcscpy(textLine1, L"The door opens...");
                doorOpeningActive = true;
                doorOpeningStartTime = time_us_64();
            } else {
                // Textbox says "look for the 3 magical items"
                wcscpy(textLine1, L"Look for the 3 magical items!");
            }
            break;
        default:
            // Unknown function code, do nothing
            break;
    }
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
            // Parse the message and handle any special function codes
            parseMessage(currentMap->objects[i]->messages[currentMap->objects[i]->messageNumber]);

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

void updateTextBoxTimer(void) {
    if (doorOpeningActive) {
        uint64_t currentTime = time_us_64();
        if (currentTime - doorOpeningStartTime >= DOOR_OPENING_DURATION_US) {
            // 5 seconds have passed, teleport player to sprigRoom
            doorOpeningActive = false;
            textBoxActive = false;
            setCurrentMap(&sprigRoom);
            // Set player position in the center of the new room
            player.x = 74;  // Center of 160px wide screen
            player.y = 104;  // Center of 128px high screen
        }
    }
}
