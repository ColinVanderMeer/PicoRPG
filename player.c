#include "player.h"
#include "graphics_data.h"
#include "rendering.h"
#include "game_state.h"

struct player player;

void initPlayer() {
    player.x = 40;
    player.y = 40;
    player.direction = 2;
    player.steps = 0;
    player.animation_timer = 0;
    player.is_walking = 0;
    
    
    // Direction 0: Up (w)
    player.animations[0].idle_frames[0] = &playerIdleW1;
    player.animations[0].idle_frames[1] = &playerIdleW2;
    player.animations[0].idle_frames[2] = &playerIdleW3;
    player.animations[0].idle_frames[3] = &playerIdleW2;
    player.animations[0].walk_frames[0] = &playerWalkW1;
    player.animations[0].walk_frames[1] = &playerWalkW2;
    player.animations[0].walk_frames[2] = &playerWalkW3;
    player.animations[0].walk_frames[3] = &playerWalkW4;
    player.animations[0].walk_frames[4] = &playerWalkW5;
    player.animations[0].walk_frames[5] = &playerWalkW6;
    player.animations[0].idle_frame_count = 4;
    player.animations[0].walk_frame_count = 6;
    player.animations[0].frame_duration = 15;
    
    // Direction 1: Left (a)
    player.animations[1].idle_frames[0] = &playerIdleA1;
    player.animations[1].idle_frames[1] = &playerIdleA2;
    player.animations[1].idle_frames[2] = &playerIdleA3;
    player.animations[1].idle_frames[3] = &playerIdleA2;
    player.animations[1].walk_frames[0] = &playerWalkA1;
    player.animations[1].walk_frames[1] = &playerWalkA2;
    player.animations[1].walk_frames[2] = &playerWalkA3;
    player.animations[1].walk_frames[3] = &playerWalkA4;
    player.animations[1].walk_frames[4] = &playerWalkA5;
    player.animations[1].walk_frames[5] = &playerWalkA6;
    player.animations[1].idle_frame_count = 4;
    player.animations[1].walk_frame_count = 6;
    player.animations[1].frame_duration = 15;
    
    // Direction 2: Down (s)
    player.animations[2].idle_frames[0] = &playerIdleS1;
    player.animations[2].idle_frames[1] = &playerIdleS2;
    player.animations[2].idle_frames[2] = &playerIdleS3;
    player.animations[2].idle_frames[3] = &playerIdleS2;
    player.animations[2].walk_frames[0] = &playerWalkS1;
    player.animations[2].walk_frames[1] = &playerWalkS2;
    player.animations[2].walk_frames[2] = &playerWalkS3;
    player.animations[2].walk_frames[3] = &playerWalkS4;
    player.animations[2].walk_frames[4] = &playerWalkS5;
    player.animations[2].walk_frames[5] = &playerWalkS6;
    player.animations[2].idle_frame_count = 4;
    player.animations[2].walk_frame_count = 6;
    player.animations[2].frame_duration = 15;
    
    // Direction 3: Right (d)
    player.animations[3].idle_frames[0] = &playerIdleD1;
    player.animations[3].idle_frames[1] = &playerIdleD2;
    player.animations[3].idle_frames[2] = &playerIdleD3;
    player.animations[3].idle_frames[3] = &playerIdleD2;
    player.animations[3].walk_frames[0] = &playerWalkD1;
    player.animations[3].walk_frames[1] = &playerWalkD2;
    player.animations[3].walk_frames[2] = &playerWalkD3;
    player.animations[3].walk_frames[3] = &playerWalkD4;
    player.animations[3].walk_frames[4] = &playerWalkD5;
    player.animations[3].walk_frames[5] = &playerWalkD6;
    player.animations[3].idle_frame_count = 4;
    player.animations[3].walk_frame_count = 6;
    player.animations[3].frame_duration = 15;
}

void renderPlayer(hagl_backend_t *display) {
    struct animation_config *anim = &player.animations[player.direction];
    hagl_bitmap_t *current_sprite;
    
    if (player.is_walking) {
        // Calculate current walking frame based on animation timer
        int frame_index = (player.animation_timer / anim->frame_duration) % anim->walk_frame_count;
        current_sprite = anim->walk_frames[frame_index];
        
        // Advance animation timer
        player.animation_timer++;
    } else {
        // Use idle frame (currently just one frame per direction)
        int frame_index = (player.animation_timer / (anim->frame_duration * 2)) % anim->idle_frame_count;
        current_sprite = anim->idle_frames[frame_index];
        
        // Advance animation timer slower for idle
        player.animation_timer++;
    }
    
    renderSprite(display, (int)player.x, (int)player.y, current_sprite);
}

void setPlayerWalking(int walking) {
    if (player.is_walking != walking) {
        player.is_walking = walking;
    }
}

void setPlayerDirection(int direction) {
    if (player.direction != direction) {
        player.direction = direction;
    }
}

bool isWaterTile(hagl_bitmap_t *tile) {
    return (tile == &water || 
            tile == &waterA1 || 
            tile == &waterA2);
}

bool isCollisionTile(hagl_bitmap_t *tile) {
    return (tile == &water || 
            tile == &waterA1 || 
            tile == &waterA2 ||
            tile == &woodWall ||
            tile == &blackTile);
}

bool canMoveTo(float newX, float newY) {
    struct map *currentMap = getCurrentMap();
    
    const int TILE_SIZE = 16;
    const int PLAYER_WIDTH = 16;
    const int PLAYER_HEIGHT = 20;
    
    // Check the corners of the player sprite
    int tileX1 = (int)(newX / TILE_SIZE);
    int tileY1 = (int)(newY / TILE_SIZE);
    int tileX2 = (int)((newX + PLAYER_WIDTH - 1) / TILE_SIZE);
    int tileY2 = (int)((newY + PLAYER_HEIGHT - 1) / TILE_SIZE);

    if (currentMap == &shopMap) { // If player is in shop manually add walls
        if (tileX1 <= -1 || tileY1 < -1 || tileX2 >= 10 || tileY2 >= 8) {
            return false;
        }
    }
    
    // Allow 1 tile off the edge of screen for map transitions
    if (tileX1 < -1 || tileY1 < -1 || tileX2 > 10 || tileY2 > 8) {
        return false;
    }
    
    // If player is only 1 tile off, always return true
    if (tileX1 < 0 || tileY1 < 0 || tileX2 >= 10 || tileY2 >= 8) {
        return true;
    }
    
    for (int y = tileY1; y <= tileY2; y++) {
        for (int x = tileX1; x <= tileX2; x++) {
            hagl_bitmap_t *tile = currentMap->tiles[y][x];
            if (isCollisionTile(tile)) {
                return false;
            }
        }
    }
    
    return true;
}

bool tryMovePlayer(float deltaX, float deltaY) {
    float newX = player.x + deltaX;
    float newY = player.y + deltaY;
    
    if (canMoveTo(newX, newY)) {
        player.x = newX;
        player.y = newY;
        return true;
    }
    return false;
}

