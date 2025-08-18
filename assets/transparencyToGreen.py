import os
from PIL import Image

def replace_transparency_with_green(folder_path):
    for filename in os.listdir(folder_path):
        if filename.lower().endswith(".png"):
            file_path = os.path.join(folder_path, filename)

            # Open image with alpha channel
            img = Image.open(file_path).convert("RGBA")
            pixels = img.load()

            # Replace fully transparent pixels with green
            width, height = img.size
            for y in range(height):
                for x in range(width):
                    r, g, b, a = pixels[x, y]
                    if a == 0:  # transparent pixel
                        pixels[x, y] = (0, 255, 0, 255)  # pure green, opaque

            # Save modified image (overwrite original or to a new file)
            output_path = os.path.join(folder_path, f"{filename}")
            img.save(output_path, "PNG")
            print(f"Processed: {filename} -> {output_path}")

if __name__ == "__main__":
    folder = "."  # 🔹 Change this to your folder path
    replace_transparency_with_green(folder)
