#include <Arduino.h>
#include <lvgl.h>
#include "LGFX_Config.h"
#include "ui/ui.h"

#define DISP_HOR_RES 320
#define DISP_VER_RES 240

LGFX tft;   // Our Lovyan display object

/* LVGL draw buffer */
static lv_display_t *disp;
static lv_color_t buf1[DISP_HOR_RES * 20];  // 20 lines

/* Flush callback */
void my_disp_flush(lv_display_t *disp_drv, const lv_area_t *area, uint8_t *px_map) {
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushImage(area->x1, area->y1, w, h, (lgfx::rgb565_t*)px_map);
    tft.endWrite();

    lv_display_flush_ready(disp_drv);
}

uint32_t last_tick = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("LVGL v9 + LovyanGFX demo starting...");

    // Init Lovyan
    tft.begin();
    tft.setRotation(1);

    // Init LVGL
    lv_init();

    // Initialize LVGL display
    disp = lv_display_create(DISP_HOR_RES, DISP_VER_RES);
    lv_display_set_buffers(disp, buf1, NULL,
                           sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(disp, my_disp_flush);

    // Init UI
    ui_init();
}

void loop() {
    lv_timer_handler();
    delay(5);

    uint32_t now = millis();
    if (now - last_tick >= 1) {
        lv_tick_inc(now - last_tick);
        last_tick = now;
    }
}
