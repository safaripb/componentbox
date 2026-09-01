"""Mock ESP32-CAM image sender for local backend testing."""

import argparse
import mimetypes
from pathlib import Path
from urllib import request


SAMPLE_IMAGE_FOLDER = Path("assets/sample_images")
DEFAULT_API_URL = "http://localhost:8000/api/component-scans"


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


def upload_image(path: Path, api_url: str):
    boundary = "----componentbox-component-boundary"
    content_type = mimetypes.guess_type(path.name)[0] or "image/jpeg"
    image_bytes = path.read_bytes()
    body = b"".join(
        [
            f"--{boundary}\r\n".encode(),
            f'Content-Disposition: form-data; name="image"; filename="{path.name}"\r\n'.encode(),
            f"Content-Type: {content_type}\r\n\r\n".encode(),
            image_bytes,
            f"\r\n--{boundary}--\r\n".encode(),
        ]
    )

    req = request.Request(
        api_url,
        data=body,
        headers={"Content-Type": f"multipart/form-data; boundary={boundary}"},
        method="POST",
    )
    with request.urlopen(req, timeout=20) as response:
        print(response.read().decode("utf-8"))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Send a sample component image to the ComponentBox backend.")
    parser.add_argument("image", nargs="?", type=Path, help="Path to an image file to upload.")
    parser.add_argument("--api-url", default=DEFAULT_API_URL, help="Component scan upload endpoint.")
    args = parser.parse_args()

    if args.image:
        upload_image(args.image, args.api_url)
    else:
        list_sample_images()
