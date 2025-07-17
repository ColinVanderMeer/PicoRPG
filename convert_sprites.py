import os
from PIL import Image
import argparse

def to_rgb565(r, g, b):
    """Converts a 24-bit RGB color to a 16-bit RGB565 color."""
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)

def image_to_rgb565_bytes(image_path):
    """Converts a PNG image to a byte array in RGB565 format."""
    try:
        with Image.open(image_path) as img:
            img = img.convert("RGB")
            pixels = img.load()
            width, height = img.size
            byte_array = bytearray()

            for y in range(height):
                for x in range(width):
                    r, g, b = pixels[x, y]
                    rgb565 = to_rgb565(r, g, b)
                    # The format is 8-bit, so we split the 16-bit value
                    byte_array.append(rgb565 >> 8)  # High byte
                    byte_array.append(rgb565 & 0xFF)  # Low byte
            return byte_array, width, height
    except IOError as e:
        print(f"Error processing {image_path}: {e}")
        return None, 0, 0

def create_c_header(image_folder, output_file):
    """
    Creates a C header file with RGB565 byte arrays and hagl_bitmap_t structs
    for all PNG images in a folder.
    """
    with open(output_file, "w") as f:

        for filename in sorted(os.listdir(image_folder)):
            if filename.lower().endswith(".png"):
                image_path = os.path.join(image_folder, filename)
                byte_array, width, height = image_to_rgb565_bytes(image_path)

                if byte_array:
                    var_name = os.path.splitext(filename)[0]
                    buffer_name = f"{var_name}buf"

                    f.write(f"// Image: {filename} ({width}x{height})\n")
                    f.write(f"unsigned char {buffer_name}[] = {{\n    ")

                    for i, byte in enumerate(byte_array):
                        f.write(f"0x{byte:02x}, ")
                        if (i + 1) % 16 == 0 and (i + 1) < len(byte_array):
                            f.write("\n    ")
                    f.write("\n};\n\n")

                    f.write(f"hagl_bitmap_t {var_name} = {{\n")
                    f.write(f"    .width = {width},\n")
                    f.write(f"    .height = {height},\n")
                    f.write(f"    .depth = 16, // RGB565 is 16-bit\n")
                    f.write(f"    .buffer = {buffer_name},\n")
                    f.write("};\n\n")

    print(f"Successfully created {output_file}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert a folder of PNG images to a C header file with RGB565 sprites.")
    parser.add_argument("image_folder", help="The folder containing the PNG images.")
    parser.add_argument("output_file", help="The name of the output C header file (e.g., graphics.h).")
    args = parser.parse_args()

    create_c_header(args.image_folder, args.output_file)