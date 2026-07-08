# ComponentBox

ComponentBox is a full-stack electronics inventory platform for tracking components, storage boxes, and project usage. The system uses an ESP32-CAM to capture component images, a backend API to store inventory data, and a dashboard to organize parts and generate reports.

## Project Overview

Many electronics students and makers own dozens of components across multiple boxes, but it is easy to lose track of quantities, resistor values, project usage, and storage locations.

ComponentBox helps users:

- Capture component images using an ESP32-CAM
- Store components by type, value, quantity, and location
- Calculate resistor values from color bands
- Assign parts to projects
- Track which parts are available, low-stock, or in use
- Generate inventory and project reports

## Planned Features

- ESP32-CAM image capture
- Component inventory dashboard
- Box/location tracking
- Project-based part assignment
- Resistor color-code calculator
- Report generation
- Backend unit tests
- Documentation
- GitHub Actions test workflow

## Tech Stack

### Embedded

- ESP32-CAM
- Arduino / PlatformIO
- C++

### Backend

- Python
- FastAPI
- SQLite
- Pytest

### Frontend

- React
- JavaScript

## Repository Structure

```text
componentbox/
├── docs/              Project documentation
├── firmware/          ESP32-CAM firmware
├── backend/           Backend API and tests
├── dashboard/         React dashboard
├── mock_device/       Software simulator for ESP32-CAM events
├── sample_data/       Example inventory data and reports
├── assets/            Images, diagrams, and demo media
└── .github/           GitHub Actions workflows