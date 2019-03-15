#ifndef FREUDIAN_FONT
#define FREUDIAN_FONT

#include <stdint.h>
#include "./lvgl/lv_misc/lv_font.h"
#include <ft2build.h>
#include FT_FREETYPE_H

static FT_Library library;
static FT_Face face;

int load_custom_font(void);
const uint8_t * get_ttf_bitmap(const lv_font_t * font, uint32_t unicode_letter);
int16_t get_ttf_width(const lv_font_t * font, uint32_t unicode_letter);

static lv_font_t custom_font = 
{
  .unicode_first = 0,
  .unicode_last = 999,
  .h_px = 20,
  .glyph_bitmap = NULL,
  .glyph_dsc = NULL,
  .unicode_list = NULL,
  .get_bitmap = get_ttf_bitmap,
  .get_width = get_ttf_width,
  .bpp = 8,
  .next_page = NULL
};

#endif // FREUDIAN_FONT
