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

def create_c_files(image_folder, output_base):
    """
    Creates both a C source file and header file with RGB565 byte arrays and hagl_bitmap_t structs
    for all PNG images in a folder.
    """
    c_file = f"{output_base}.c"
    h_file = f"{output_base}.h"
    
    # Create header file
    with open(h_file, "w") as h:
        header_guard = f"{output_base.upper().replace('.', '_')}_H"
        h.write(f"#ifndef {header_guard}\n")
        h.write(f"#define {header_guard}\n\n")
        h.write("#include <hagl_hal.h>\n")
        h.write("#include <hagl.h>\n\n")
        h.write("// External declarations for all sprites\n")
        
        # Collect all sprite names first
        sprite_names = []
        for filename in sorted(os.listdir(image_folder)):
            if filename.lower().endswith(".png"):
                var_name = os.path.splitext(filename)[0]
                sprite_names.append(var_name)
        
        # Write extern declarations
        for var_name in sprite_names:
            h.write(f"extern hagl_bitmap_t {var_name};\n")
        
        h.write(f"\n#endif // {header_guard}\n")

    # Create source file
    with open(c_file, "w") as f:
        f.write("#include <hagl_hal.h>\n")
        f.write("#include <hagl.h>\n\n")

        for filename in sorted(os.listdir(image_folder)):
            if filename.lower().endswith(".png"):
                image_path = os.path.join(image_folder, filename)
                byte_array, width, height = image_to_rgb565_bytes(image_path)

                if byte_array:
                    var_name = os.path.splitext(filename)[0]
                    buffer_name = f"{var_name}buf"

                    f.write(f"// Image: {filename} ({width}x{height})\n")
                    f.write(f"static unsigned char {buffer_name}[] = {{\n    ")

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

    print(f"Successfully created {c_file} and {h_file}")

def create_c_header(image_folder, output_file):
    """
    Legacy function - creates either .c/.h combo or single .h file based on extension
    """
    if output_file.endswith('.c'):
        # Create both .c and .h files
        output_base = output_file[:-2]  # Remove .c extension
        create_c_files(image_folder, output_base)
    else:
        # Original single file behavior for backward compatibility
        with open(output_file, "w") as f:
            f.write("#ifndef GRAPHICS_H\n")
            f.write("#define GRAPHICS_H\n\n")
            f.write("#include <hagl_hal.h>\n")
            f.write("#include <hagl.h>\n\n")

            for filename in sorted(os.listdir(image_folder)):
                if filename.lower().endswith(".png"):
                    image_path = os.path.join(image_folder, filename)
                    byte_array, width, height = image_to_rgb565_bytes(image_path)

                    if byte_array:
                        var_name = os.path.splitext(filename)[0]
                        buffer_name = f"{var_name}buf"

                        f.write(f"// Image: {filename} ({width}x{height})\n")
                        f.write(f"static unsigned char {buffer_name}[] = {{\n    ")

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
            
            f.write("#endif // GRAPHICS_H\n")

        print(f"Successfully created {output_file}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert a folder of PNG images to C source/header files with RGB565 sprites.")
    parser.add_argument("image_folder", help="The folder containing the PNG images.")
    parser.add_argument("output_file", help="The name of the output file (e.g., graphics_data for .c/.h pair or graphics.h for single file).")
    args = parser.parse_args()

    # If output_file doesn't have an extension, assume we want .c/.h pair
    if '.' not in args.output_file:
        create_c_files(args.image_folder, args.output_file)
    else:
        create_c_header(args.image_folder, args.output_file)