import os
from PIL import Image

def display_ppm_image(file_path):
    image = Image.open(file_path)
    image.show()

# Get the filepath
filepath = input("Filepath: ")

# Remove quotes from the filepath
filepath = filepath.strip('"').strip("'")

# Handle Unix-style paths (convert /f/ to F:\)
if filepath.startswith('/'):
    # Convert /f/path to F:\path
    drive_letter = filepath[1].upper()
    rest_of_path = filepath[3:].replace('/', '\\')
    filepath = f"{drive_letter}:\\{rest_of_path}"  # 修正：加上 \\

# Check if the filepath has the .ppm extension
if not filepath.endswith(".ppm"):
    filepath += ".ppm"

# Normalize the filepath
normalized_filepath = os.path.normpath(filepath)

# Check if file exists (use normalized_filepath)
if not os.path.exists(normalized_filepath):
    print(f"File '{normalized_filepath}' does not exist.")
    exit()

# Display the image
display_ppm_image(normalized_filepath)
