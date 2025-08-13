#ifndef INPUT_H
#define INPUT_H

#include <hagl_hal.h>
#include <hagl.h>

// Joypad button constants to fit in uint8_t
#define JOYPAD_UP      0x01
#define JOYPAD_DOWN    0x02
#define JOYPAD_LEFT    0x04
#define JOYPAD_RIGHT   0x08
#define JOYPAD_A       0x10
#define JOYPAD_B       0x20
#define JOYPAD_X       0x40
#define JOYPAD_Y       0x80

typedef struct {
    uint8_t down;
    uint8_t pressed;
    uint8_t released; 
} joypad_state_t;

// Global joypad state variable
extern joypad_state_t joypad_state;

void initInput(void);
void handleInput(hagl_backend_t *display);

#endif // INPUT_H
