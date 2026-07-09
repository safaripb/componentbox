# ESP32-CAM Capture Firmware

This folder will contain the ESP32-CAM firmware for ComponentBox.

## Purpose

The firmware will allow the ESP32-CAM to capture images of electronic components and send them to the backend API.

## Planned Features

- Wi-Fi connection
- Camera initialization
- Image capture
- HTTP image upload
- Serial debugging
- Basic error handling

## Current Status

Firmware development has not started yet. The current focus is setting up the software foundation and project documentation.

## Future Firmware Flow

```text
Start ESP32-CAM
      ↓
Connect to Wi-Fi
      ↓
Initialize camera
      ↓
Wait for capture command
      ↓
Take picture
      ↓
Send image to backend
      ↓
Print upload status to Serial Monitor