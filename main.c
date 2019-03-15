#define USE_SDL 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lvgl/lvgl.h"

#if USE_SDL
#include <SDL2/SDL.h>
#include "lv_drivers/display/monitor.h"
#else
#include "lv_drivers/display/fbdev.h"b
#endif

#include "freudian_font.h"

// just a test string
static char * label_text = "Quest the NUzbpP";

static void hal_init(void);
void disp_init(void);
void build_container(lv_obj_t * parent);

int main (int argc, char ** argv)
{
    load_custom_font();
    lv_init();
    hal_init();
    disp_init();

    while (1) {
        lv_tick_inc(5);
        lv_task_handler();
        usleep(5 * 1000);
    }
}

static void hal_init(void)
{
    #if USE_SDL
        monitor_init();
    #else
        fbdev_init();
    #endif

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    #if USE_SDL
        disp_drv.disp_flush = monitor_flush;
        disp_drv.disp_fill = monitor_fill;
        disp_drv.disp_map = monitor_map;
    #else
        disp_drv.disp_flush = fbdev_flush;
        disp_drv.disp_fill = fbdev_fill;
        disp_drv.disp_map = fbdev_map;
    #endif

    lv_disp_drv_register(&disp_drv);
}

void disp_init(void)
{
    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);

    build_container(scr);
}

void build_container(lv_obj_t * parent)
{
    lv_obj_t * main_container = lv_obj_create(parent, NULL);
    lv_obj_set_size(main_container, 800, 480);

    lv_obj_t * label = lv_label_create(main_container, NULL);

    // SET CUSTOM FONT
    static lv_style_t custom_font_style;
    lv_style_copy(&custom_font_style, &lv_style_plain);
    custom_font_style.text.color = LV_COLOR_RED;
    custom_font_style.text.font = &custom_font;
    lv_obj_set_style(label, &custom_font_style);

    lv_label_set_text(label, label_text);

    lv_obj_align(label, main_container, LV_ALIGN_CENTER, 0, 0);
}
