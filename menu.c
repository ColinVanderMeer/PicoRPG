#include "menu.h"
#include "save_system.h"
#include "graphics_data.h"
#include "audio.h"
#include "pico/stdlib.h"
#include "fonts.h"
#include "global.h"

void menu(hagl_backend_t *display) {
    int selection = 0;
    int butPressed = 0;
    hagl_fill_rounded_rectangle_xyxy(display, 2, 2, 80, 125, 5, 0x0000);
    hagl_draw_rounded_rectangle_xyxy(display, 2, 2, 80, 125, 5, 0xffff);
    hagl_put_text(display, L"Menu", 5, 5, 0xffff, font6x9);
    hagl_put_text(display, L"Save", 15, 15, 0xffff, font6x9);
    hagl_put_text(display, L"Load", 15, 25, 0xffff, font6x9);
    hagl_put_text(display, L"Exit", 15, 35, 0xffff, font6x9);

    while (1) { // This is a weird backwards way to handle this, but I think it actually works well? So it'll stay until it causes a catastrophic failure.
        hagl_fill_rectangle_xyxy(display, 7, 15, 10, 120, 0x0000);
        hagl_blit_xy(display, 7, 17 + selection * 10, &selector);

        update_mod_player();

        hagl_flush(display);

        if (!gpio_get(5) && !butPressed) {
            selection--;
            if (selection < 0) {
                selection = 2;
            }
        }
        if (!gpio_get(7) && !butPressed) {
            selection++;
            if (selection > 2) {
                selection = 0;
            }
        }

        if (!gpio_get(5) || !gpio_get(7)) {
            butPressed = 1;
        } else {
            butPressed = 0;
        }

        if (!gpio_get(15)) {
            switch (selection) {
                case 0:
                    saveGame();
                    while (!gpio_get(15)) {}
                    return;
                case 1:
                    loadGame();
                    while (!gpio_get(15)) {}
                    return;
                case 2:
                    while (!gpio_get(15)) {}
                    game_state = GAME_STATE_NORMAL;
                    return;
            }
        }
        if (!gpio_get(14)) {
            return;
        }
    }
}
