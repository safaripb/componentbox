# ESP32-CAM Capture Firmware

This folder contains the ESP32-CAM firmware for the ComponentBox project.

## Purpose

The ESP32-CAM is responsible for capturing images of electronic components so they can later be stored in the ComponentBox inventory dashboard.

For the first hardware milestone, the ESP32-CAM runs a local web server. A user can open the camera's IP address in a browser and capture a component image.

## Current Features

- Connects ESP32-CAM to Wi-Fi
- Initializes the camera
- Starts a local web server
- Provides a `/capture` endpoint
- Displays a simple browser page for image capture
- Allows sample component images to be saved manually

## Hardware Used

- ESP32-CAM module
- USB-to-serial programmer or ESP32-CAM-MB programmer
- 5V power source
- Electronic components for sample images

## How It Works

1. The ESP32-CAM connects to Wi-Fi.
2. The Serial Monitor prints the local IP address.
3. The user opens the IP address in a browser.
4. The browser shows a simple capture page.
5. Pressing the capture button displays a new component image.
6. The image can be saved and added to `assets/sample_images/`.

## Arduino IDE Setup

Recommended board settings:

- Board: AI Thinker ESP32-CAM
- Upload speed: 115200
- Flash frequency: 40 MHz
- Partition scheme: Huge APP
- Core debug level: None

## Wi-Fi Setup

Edit these lines before uploading:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";