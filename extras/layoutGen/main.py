import pygame
import os
import sys
from pathlib import Path

# Initialize pygame
pygame.init()

# Constants
TILE_SIZE = 16
MAP_WIDTH = 10
MAP_HEIGHT = 8
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
PALETTE_WIDTH = 200
GRID_OFFSET_X = PALETTE_WIDTH + 20
GRID_OFFSET_Y = 50

# Colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GRAY = (128, 128, 128)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

class TilemapEditor:
    def __init__(self):
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption("Tilemap Layout Editor")
        self.clock = pygame.time.Clock()
        
        # Load tiles
        self.tiles = {}
        self.tile_names = []
        self.load_tiles()
        
        # Initialize map grid
        self.map_grid = [[None for _ in range(MAP_WIDTH)] for _ in range(MAP_HEIGHT)]
        
        # UI state
        self.selected_tile = None
        self.palette_scroll = 0
        self.font = pygame.font.Font(None, 24)
        self.is_dragging = False
        self.drag_button = None
        
    def load_tiles(self):
        """Load all tiles from the assets directory"""
        assets_path = Path("assets")
        
        # Define tile files (excluding character sprites)
        tile_files = [
            "grass.png", "grassWaterB.png", "grassWaterBL.png", "grassWaterBR.png",
            "grassWaterL.png", "grassWaterR.png", "grassWaterT.png", "grassWaterTL.png",
            "grassWaterTR.png", "water.png", "waterA1.png", "waterA2.png",
            "waterGrassBL.png", "waterGrassBR.png", "waterGrassTL.png", "waterGrassTR.png",
            "grassA1.png", "grassA2.png", "greyTile.png", "blackTile.png",
            "waterDockL.png", "waterDockR.png", "dockL.png", "dockR.png", "grassDockL.png", "grassDockR.png"
        ]
        
        for filename in tile_files:
            filepath = assets_path / filename
            if filepath.exists():
                try:
                    image = pygame.image.load(str(filepath))
                    # Scale to 16x16 if needed
                    if image.get_size() != (TILE_SIZE, TILE_SIZE):
                        image = pygame.transform.scale(image, (TILE_SIZE, TILE_SIZE))
                    
                    tile_name = filename.replace('.png', '')
                    self.tiles[tile_name] = image
                    self.tile_names.append(tile_name)
                except pygame.error as e:
                    print(f"Could not load {filename}: {e}")
        
        print(f"Loaded {len(self.tiles)} tiles")
    
    def draw_palette(self):
        """Draw the tile palette on the left side"""
        # Draw palette background
        pygame.draw.rect(self.screen, GRAY, (0, 0, PALETTE_WIDTH, SCREEN_HEIGHT))
        
        # Draw tiles in palette
        tiles_per_row = PALETTE_WIDTH // (TILE_SIZE + 4)
        for i, tile_name in enumerate(self.tile_names):
            row = i // tiles_per_row
            col = i % tiles_per_row
            
            x = col * (TILE_SIZE + 4) + 4
            y = row * (TILE_SIZE + 4) + 4 - self.palette_scroll
            
            if y > -TILE_SIZE and y < SCREEN_HEIGHT:
                # Draw tile
                self.screen.blit(self.tiles[tile_name], (x, y))
                
                # Highlight selected tile
                if self.selected_tile == tile_name:
                    pygame.draw.rect(self.screen, RED, (x-1, y-1, TILE_SIZE+2, TILE_SIZE+2), 2)
                
                # Draw border
                pygame.draw.rect(self.screen, BLACK, (x, y, TILE_SIZE, TILE_SIZE), 1)
    
    def draw_grid(self):
        """Draw the tilemap grid"""
        # Draw grid background
        grid_rect = pygame.Rect(GRID_OFFSET_X, GRID_OFFSET_Y, 
                               MAP_WIDTH * TILE_SIZE * 2, MAP_HEIGHT * TILE_SIZE * 2)
        pygame.draw.rect(self.screen, WHITE, grid_rect)
        
        # Draw tiles in grid
        for row in range(MAP_HEIGHT):
            for col in range(MAP_WIDTH):
                x = GRID_OFFSET_X + col * TILE_SIZE * 2
                y = GRID_OFFSET_Y + row * TILE_SIZE * 2
                
                # Draw tile if one is placed
                if self.map_grid[row][col]:
                    tile_image = pygame.transform.scale(
                        self.tiles[self.map_grid[row][col]], (TILE_SIZE * 2, TILE_SIZE * 2)
                    )
                    self.screen.blit(tile_image, (x, y))
                
                # Draw grid lines
                pygame.draw.rect(self.screen, BLACK, (x, y, TILE_SIZE * 2, TILE_SIZE * 2), 1)
    
    def draw_ui(self):
        """Draw UI elements"""
        # Title
        title = self.font.render("Tilemap Editor", True, BLACK)
        self.screen.blit(title, (GRID_OFFSET_X, 10))
        
        # Instructions
        instructions = [
            "Left click: Select tile from palette",
            "Right click/drag: Place tile on grid",
            "Middle click/drag: Remove tile from grid",
            "C: Clear map",
            "S: Save as C array",
            "Mouse wheel: Scroll palette"
        ]
        
        for i, instruction in enumerate(instructions):
            text = pygame.font.Font(None, 18).render(instruction, True, BLACK)
            self.screen.blit(text, (GRID_OFFSET_X, GRID_OFFSET_Y + MAP_HEIGHT * TILE_SIZE * 2 + 20 + i * 20))
    
    def handle_palette_click(self, pos):
        """Handle clicks on the tile palette"""
        x, y = pos
        if x < PALETTE_WIDTH:
            tiles_per_row = PALETTE_WIDTH // (TILE_SIZE + 4)
            col = x // (TILE_SIZE + 4)
            row = (y + self.palette_scroll) // (TILE_SIZE + 4)
            
            tile_index = row * tiles_per_row + col
            if 0 <= tile_index < len(self.tile_names):
                self.selected_tile = self.tile_names[tile_index]
                print(f"Selected tile: {self.selected_tile}")
    
    def handle_grid_click(self, pos, button):
        """Handle clicks on the tilemap grid"""
        x, y = pos
        
        # Check if click is within grid
        if (GRID_OFFSET_X <= x < GRID_OFFSET_X + MAP_WIDTH * TILE_SIZE * 2 and
            GRID_OFFSET_Y <= y < GRID_OFFSET_Y + MAP_HEIGHT * TILE_SIZE * 2):
            
            # Calculate grid position
            grid_x = (x - GRID_OFFSET_X) // (TILE_SIZE * 2)
            grid_y = (y - GRID_OFFSET_Y) // (TILE_SIZE * 2)
            
            self.place_or_remove_tile(grid_x, grid_y, button)
    
    def handle_grid_drag(self, pos):
        """Handle dragging on the tilemap grid"""
        if not self.is_dragging:
            return
            
        x, y = pos
        
        # Check if drag is within grid
        if (GRID_OFFSET_X <= x < GRID_OFFSET_X + MAP_WIDTH * TILE_SIZE * 2 and
            GRID_OFFSET_Y <= y < GRID_OFFSET_Y + MAP_HEIGHT * TILE_SIZE * 2):
            
            # Calculate grid position
            grid_x = (x - GRID_OFFSET_X) // (TILE_SIZE * 2)
            grid_y = (y - GRID_OFFSET_Y) // (TILE_SIZE * 2)
            
            self.place_or_remove_tile(grid_x, grid_y, self.drag_button)
    
    def place_or_remove_tile(self, grid_x, grid_y, button):
        """Place or remove a tile at the specified grid position"""
        if button == 3 and self.selected_tile:  # Right click - place tile
            self.map_grid[grid_y][grid_x] = self.selected_tile
            print(f"Placed {self.selected_tile} at ({grid_x}, {grid_y})")
        elif button == 2:  # Middle click - remove tile
            self.map_grid[grid_y][grid_x] = None
            print(f"Removed tile at ({grid_x}, {grid_y})")
    
    def clear_map(self):
        """Clear the entire map"""
        self.map_grid = [[None for _ in range(MAP_WIDTH)] for _ in range(MAP_HEIGHT)]
        print("Map cleared")
    
    def export_to_c_array(self):
        """Export the current map to C array format"""
        output = "{\n"
        for row in range(MAP_HEIGHT):
            output += "    {"
            for col in range(MAP_WIDTH):
                tile = self.map_grid[row][col]
                if tile:
                    output += f"&{tile}"
                else:
                    output += "&grass"  # Default to grass for empty tiles
                
                if col < MAP_WIDTH - 1:
                    output += ", "
            output += "}"
            if row < MAP_HEIGHT - 1:
                output += ","
            output += "\n"
        output += "},"
        
        print("C Array format:")
        print(output)
    
    def run(self):
        """Main game loop"""
        running = True
        
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 1:  # Left click
                        self.handle_palette_click(event.pos)
                    elif event.button in [2, 3]:  # Middle or right click
                        self.handle_grid_click(event.pos, event.button)
                        # Start dragging
                        self.is_dragging = True
                        self.drag_button = event.button
                
                elif event.type == pygame.MOUSEBUTTONUP:
                    if event.button in [2, 3]:  # Middle or right click released
                        self.is_dragging = False
                        self.drag_button = None
                
                elif event.type == pygame.MOUSEMOTION:
                    if self.is_dragging:
                        self.handle_grid_drag(event.pos)
                
                elif event.type == pygame.MOUSEWHEEL:
                    # Scroll palette
                    self.palette_scroll -= event.y * 20
                    self.palette_scroll = max(0, self.palette_scroll)
                
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_c:
                        self.clear_map()
                    elif event.key == pygame.K_s:
                        self.export_to_c_array()
            
            # Clear screen
            self.screen.fill(WHITE)
            
            # Draw everything
            self.draw_palette()
            self.draw_grid()
            self.draw_ui()
            
            # Update display
            pygame.display.flip()
            self.clock.tick(60)
        
        pygame.quit()
        sys.exit()

if __name__ == "__main__":
    editor = TilemapEditor()
    editor.run() 