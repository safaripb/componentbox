"""
Mock ESP32-CAM image sender.

This file is a placeholder for testing backend image upload later.
The real ESP32-CAM currently captures images through a local web page.
"""

from pathlib import Path


SAMPLE_IMAGE_FOLDER = Path("assets/sample_images")


def list_sample_images():
    if not SAMPLE_IMAGE_FOLDER.exists():
        print("No sample image folder found.")
        return

    images = list(SAMPLE_IMAGE_FOLDER.glob("*.jpg"))

    if not images:
        print("No sample images found yet.")
        return

    print("Available sample images:")
    for image in images:
        print(f"- {image}")


if __name__ == "__main__":
    list_sample_images()