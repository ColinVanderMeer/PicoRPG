#include "rendering.h"
#include "interactableMap.h"
#include "game_state.h"

void renderSprite(hagl_backend_t *display, int px, int py, hagl_bitmap_t *bitmap) {
    hagl_color_t transparentColor = hagl_color(display, 0, 255, 0);
    for (uint8_t x = 0; x < bitmap->width; x++) {
        for (uint8_t y = 0; y < bitmap->height; y++) {
            hagl_color_t *color = (hagl_color_t *) (bitmap->buffer + (x + y * bitmap->width) * 2);
            if (*color != transparentColor) {
                hagl_put_pixel(display, px + x, py + y, *color);
            }
        }
    }
}

void renderScaledSprite(hagl_backend_t *display, int px, int py, hagl_bitmap_t *bitmap, int scale) {
    hagl_color_t transparentColor = hagl_color(display, 0, 255, 0);
    for (uint8_t x = 0; x < bitmap->width; x++) {
        for (uint8_t y = 0; y < bitmap->height; y++) {
            hagl_color_t *color = (hagl_color_t *) (bitmap->buffer + (x + y * bitmap->width) * 2);
            if (*color != transparentColor) {
                for (int sx = 0; sx < scale; sx++) {
                    for (int sy = 0; sy < scale; sy++) {
                        hagl_put_pixel(display, px + x * scale + sx, py + y * scale + sy, *color);
                    }
                }
            }
        }
    }
}

void renderMap(hagl_backend_t *display) {
    struct map* currentMap = getCurrentMap();
    for (uint8_t x = 0; x < 10; x++) {
        for (uint8_t y = 0; y < 8; y++) {
            hagl_blit(display, x*16, y*16, currentMap->tiles[y][x]);
        }
    }
}

void renderInteractableObjects(hagl_backend_t *display) {
    struct map* currentMap = getCurrentMap();
    for (int i = 0; i < currentMap->numObjects; i++) {
        renderSprite(display, currentMap->objects[i]->x, currentMap->objects[i]->y, currentMap->objects[i]->sprite);
    }
}
