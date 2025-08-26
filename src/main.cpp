#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <lvgl.h>
#include <TFT_eSPI.h>        // TFT_eSPI instead of LovyanGFX
#include "ui/ui.h"
#include "ui/screens.h"

#define DISP_HOR_RES 320
#define DISP_VER_RES 240

TFT_eSPI tft = TFT_eSPI();   // TFT_eSPI instance

/* LVGL display + buffer pointers */
static lv_display_t *disp = nullptr;
static lv_color_t *buf1 = nullptr;
static uint16_t buf_lines = 0;

/* Flush callback: send LVGL pixels to TFT_eSPI */
void my_disp_flush(lv_display_t *disp_drv, const lv_area_t *area, uint8_t *px_map) {
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;

  // TFT_eSPI expects 16-bit color data in a uint16_t array
  // Ensure proper byte order - we set swapBytes in setup()
  tft.pushImage(area->x1, area->y1, w, h, (uint16_t *)px_map);

  lv_display_flush_ready(disp_drv);
}

/* --- ESP-NOW instruction handling --- */
static char lastInstruction[32] = "main";  // default
static volatile bool newInstruction = false;

void onReceive(const uint8_t *mac, const uint8_t *incomingData, int len) {
  size_t copyLen = (len < (int)sizeof(lastInstruction)-1) ? (size_t)len : sizeof(lastInstruction)-1;
  memcpy(lastInstruction, incomingData, copyLen);
  lastInstruction[copyLen] = '\0';
  newInstruction = true;
  // keep callback short: just copy + flag
}

/* ---------- Setup / Loop ---------- */
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("TFT_eSPI + LVGL + ESP-NOW receiver starting...");

  // Check PSRAM
  if (psramFound()) {
    Serial.println("PSRAM detected.");
  } else {
    Serial.println("PSRAM NOT detected. Using internal RAM (may need smaller buffers).");
  }

  // Init TFT
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true); // important for pushImage byte order

  // Init LVGL
  lv_init();

  // Allocate LVGL draw buffer (prefer PSRAM). Start with 20 lines
  uint16_t desired_lines = 20;
  size_t bytes_needed = (size_t)DISP_HOR_RES * desired_lines * sizeof(lv_color_t);

  if (psramFound()) {
    buf1 = (lv_color_t *) ps_malloc(bytes_needed);
    if (buf1) {
      buf_lines = desired_lines;
      Serial.printf("Allocated LVGL buffer in PSRAM: %u lines (%u bytes)\n", buf_lines, (unsigned)bytes_needed);
    }
  }

  if (!buf1) { // PSRAM not available or allocation failed -> fallback to smaller internal RAM buffer
    desired_lines = 10; // smaller fallback
    bytes_needed = (size_t)DISP_HOR_RES * desired_lines * sizeof(lv_color_t);
    buf1 = (lv_color_t *) malloc(bytes_needed);
    if (!buf1) {
      Serial.println("ERROR: Cannot allocate LVGL buffer (PSRAM and RAM failed). Reduce LVGL resource usage.");
      while (1) { delay(1000); }
    }
    buf_lines = desired_lines;
    Serial.printf("Allocated LVGL buffer in internal RAM: %u lines (%u bytes)\n", buf_lines, (unsigned)bytes_needed);
  }

  // Create LVGL display + buffers
  disp = lv_display_create(DISP_HOR_RES, DISP_VER_RES);
  lv_display_set_buffers(disp, buf1, NULL,
                         (uint32_t)(DISP_HOR_RES * buf_lines * sizeof(lv_color_t)),
                         LV_DISPLAY_RENDER_MODE_PARTIAL);
  lv_display_set_flush_cb(disp, my_disp_flush);

  // Initialize your UI (generated UI code)
  ui_init();

  // Show default screen
  lv_scr_load(objects.main);

  // Setup ESP-NOW receiver
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
  } else {
    esp_now_register_recv_cb(onReceive);
    Serial.println("ESP-NOW receiver ready. Waiting for instructions...");
  }

  // Optionally show an initial message on the screen (LVGL objects.main should handle it)
}

void loop() {
  static uint32_t last_tick = millis();
  uint32_t now = millis();

  // LVGL tick: pass elapsed ms
  uint32_t diff = now - last_tick;
  if (diff > 0) {
    lv_tick_inc(diff);
    last_tick = now;
  }

  // LVGL handler
  lv_timer_handler();

  // Process new ESP-NOW instruction (do UI changes in main loop, not in callback)
  if (newInstruction) {
    newInstruction = false;

    Serial.printf("Instruction received: %s\n", lastInstruction);

    if (strcmp(lastInstruction, "main") == 0) {
      lv_scr_load(objects.main);
      Serial.println("Switched to MAIN");
    } else if (strcmp(lastInstruction, "scan") == 0) {
      lv_scr_load(objects.scan);
      Serial.println("Switched to SCAN");
    } else if (strcmp(lastInstruction, "successful") == 0) {
      lv_scr_load(objects.successful);
      Serial.println("Switched to SUCCESSFUL");
    } else if (strcmp(lastInstruction, "unsuccessful") == 0) {
      lv_scr_load(objects.unsuccessful);
      Serial.println("Switched to UNSUCCESSFUL");
    } else {
      Serial.println("Unknown instruction - ignored.");
    }
  }

  // small yield — keep WiFi/other RTOS tasks happy
  delay(5);
}
