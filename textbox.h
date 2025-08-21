#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <hagl_hal.h>
#include <hagl.h>
#include <wchar.h>
#include <stdbool.h>

extern wchar_t textLine1[26];
extern wchar_t textLine2[26];
extern wchar_t textLine3[26];
extern wchar_t textLine4[26];

extern bool doorOpeningActive;

void interactObject(void);
void renderTextBox(hagl_backend_t *display);
void executeFunction(int functionCode);
void parseMessage(const wchar_t* message);
void updateTextBoxTimer(void);
void fishDisplay(int frameNum);

#endif // TEXTBOX_H
