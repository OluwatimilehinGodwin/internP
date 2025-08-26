#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Background imag
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.background_imag = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_always_on_display);
        }
        {
            // Hour tens
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.hour_tens = obj;
            lv_obj_set_pos(obj, 59, 95);
            lv_obj_set_size(obj, 34, 38);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "1");
        }
        {
            // Hour ones
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.hour_ones = obj;
            lv_obj_set_pos(obj, 108, 95);
            lv_obj_set_size(obj, 34, 38);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "1");
        }
        {
            // Minutes ones
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.minutes_ones = obj;
            lv_obj_set_pos(obj, 229, 95);
            lv_obj_set_size(obj, 34, 38);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "1");
        }
        {
            // Minutes tens
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.minutes_tens = obj;
            lv_obj_set_pos(obj, 180, 95);
            lv_obj_set_size(obj, 34, 38);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "1");
        }
        {
            // Minutes tens_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.minutes_tens_1 = obj;
            lv_obj_set_pos(obj, 143, 91);
            lv_obj_set_size(obj, 34, 38);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfff97316), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, ":");
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
}

void create_screen_scan() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.scan = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_animimg_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            static const lv_image_dsc_t *images[8] = {
                &img_scanning__1_,
                &img_scanning_2,
                &img_scanning_3,
                &img_scanning_4,
                &img_scanning_5,
                &img_scanning_6,
                &img_scanning_7,
                &img_scanning_8,
            };
            lv_animimg_set_src(obj, (const void **)images, 8);
            lv_animimg_set_duration(obj, 1000);
            lv_animimg_set_repeat_count(obj, LV_ANIM_REPEAT_INFINITE);
            lv_animimg_start(obj);
        }
    }
    
    tick_screen_scan();
}

void tick_screen_scan() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
}

void create_screen_successful() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.successful = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_successful);
        }
    }
    
    tick_screen_successful();
}

void tick_screen_successful() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
}

void create_screen_unsuccessful() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.unsuccessful = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_un_successful);
        }
    }
    
    tick_screen_unsuccessful();
}

void tick_screen_unsuccessful() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
}


static const char *screen_names[] = { "Main", "scan", "successful", "Unsuccessful" };
static const char *object_names[] = { "main", "scan", "successful", "unsuccessful", "background_imag", "hour_tens", "hour_ones", "minutes_ones", "minutes_tens", "minutes_tens_1" };


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_scan,
    tick_screen_successful,
    tick_screen_unsuccessful,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_scan();
    create_screen_successful();
    create_screen_unsuccessful();
}
