#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *scan;
    lv_obj_t *successful;
    lv_obj_t *unsuccessful;
    lv_obj_t *background_imag;
    lv_obj_t *hour_tens;
    lv_obj_t *hour_ones;
    lv_obj_t *minutes_ones;
    lv_obj_t *minutes_tens;
    lv_obj_t *minutes_tens_1;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_SCAN = 2,
    SCREEN_ID_SUCCESSFUL = 3,
    SCREEN_ID_UNSUCCESSFUL = 4,
};

void create_screen_main();
void tick_screen_main();

void create_screen_scan();
void tick_screen_scan();

void create_screen_successful();
void tick_screen_successful();

void create_screen_unsuccessful();
void tick_screen_unsuccessful();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/