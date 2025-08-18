#ifndef RENDERING_H
#define RENDERING_H

#include <hagl_hal.h>
#include <hagl.h>

void renderSprite(hagl_backend_t *display, int px, int py, hagl_bitmap_t *bitmap);
void renderScaledSprite(hagl_backend_t *display, int px, int py, hagl_bitmap_t *bitmap, int scale);
void renderMap(hagl_backend_t *display);
void renderInteractableObjects(hagl_backend_t *display);

#endif // RENDERING_H
