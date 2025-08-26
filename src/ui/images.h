#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_scanning;
extern const lv_img_dsc_t img_un_successful;
extern const lv_img_dsc_t img_successful;
extern const lv_img_dsc_t img_scanning__1_;
extern const lv_img_dsc_t img_scanning_2;
extern const lv_img_dsc_t img_scanning_3;
extern const lv_img_dsc_t img_scanning_4;
extern const lv_img_dsc_t img_scanning_5;
extern const lv_img_dsc_t img_scanning_6;
extern const lv_img_dsc_t img_scanning_7;
extern const lv_img_dsc_t img_scanning_8;
extern const lv_img_dsc_t img_always_on_display;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[12];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/