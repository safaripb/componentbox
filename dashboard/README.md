# ComponentBox dashboard

A responsive AngularJS 1.8 dashboard for reviewing images captured by the ESP32-CAM.

## Run locally

```powershell
npm install
npm start
```

Open `http://localhost:5173`.

## Current features

- Organized grid and list views for camera captures
- Search, status filters, and resistance sorting
- Identified and needs-review states
- Scan detail viewer with detected color bands
- Responsive layout for desktop and mobile
- Online camera status and scan feedback

The sample scan data lives in `src/app.js`. It can later be replaced by calls to the FastAPI backend without changing the dashboard layout.
