#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>

// =====================
// Wi-Fi credentials
// =====================
const char* ssid = "";
const char* password = "";

// =====================
// GPIO 
// =====================
#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM    21
#define SIOD_GPIO_NUM    26
#define SIOC_GPIO_NUM    27

#define Y9_GPIO_NUM      35
#define Y8_GPIO_NUM      34
#define Y7_GPIO_NUM      39
#define Y6_GPIO_NUM      36
#define Y5_GPIO_NUM      19
#define Y4_GPIO_NUM      18
#define Y3_GPIO_NUM       5
#define Y2_GPIO_NUM       4

#define VSYNC_GPIO_NUM   25
#define HREF_GPIO_NUM    23
#define PCLK_GPIO_NUM    22

WebServer server(80);

// =====================
// Capture endpoint
// =====================
void handleCapture() {
  camera_fb_t* fb = esp_camera_fb_get();

  if (!fb) {
    server.send(500, "text/plain", "Camera capture failed");
    return;
  }

  server.sendHeader("Content-Disposition", "inline; filename=component.jpg");
  server.send_P(200, "image/jpeg", (const char*)fb->buf, fb->len);

  esp_camera_fb_return(fb);
}

// =====================
// Home page
// =====================
void handleRoot() {
  String html = "";
  html += "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<title>ComponentBox ESP32-CAM</title>";
  html += "<style>";
  html += "body { font-family: Arial; text-align: center; margin-top: 40px; }";
  html += "button { padding: 12px 20px; font-size: 16px; cursor: pointer; }";
  html += "img { margin-top: 20px; max-width: 90%; border: 1px solid #ccc; }";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>ComponentBox ESP32-CAM</h1>";
  html += "<p>Use this page to capture component images.</p>";
  html += "<button onclick=\"captureImage()\">Capture Image</button>";
  html += "<br>";
  html += "<img id=\"photo\" src=\"\" />";
  html += "<script>";
  html += "function captureImage() {";
  html += "  document.getElementById('photo').src = '/capture?t=' + new Date().getTime();";
  html += "}";
  html += "</script>";
  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
}

// =====================
// Camera setup
// =====================
void setupCamera() {
  camera_config_t config;

  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;

  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;

  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;

  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;

  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;

  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  esp_err_t error = esp_camera_init(&config);

  if (error != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x\n", error);
    while (true) {
      delay(1000);
    }
  }

  Serial.println("Camera initialized successfully");
}

// =====================
// Main setup
// =====================
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("Starting ComponentBox ESP32-CAM...");

  setupCamera();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected");
  Serial.print("Camera web page: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/capture", handleCapture);

  server.begin();
  Serial.println("Web server started");
}

// =====================
// Main loop
// =====================
void loop() {
  server.handleClient();
}