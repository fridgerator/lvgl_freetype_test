#include "freudian_font.h"

int load_custom_font(void)
{
    printf("load custom font\n");
    int error;
    error = FT_Init_FreeType(&library);
    if (error) {
        printf("error init freetype\n");
        return EXIT_FAILURE;
    }

    error = FT_New_Face(library, "./freudian.ttf", 0, &face);
    if (error == FT_Err_Unknown_File_Format) {
        printf("unkown file format\n");
        return EXIT_FAILURE;
    } else if (error) {
        printf("error loading font\n");
        return EXIT_FAILURE;
    }

    // int height = 9 * 64;
    // error = FT_Set_Char_Size(face, 0, 580, 300, 300);
    error = FT_Set_Pixel_Sizes(face, 0, 20);
    if (error) {
        printf("couldnt get char size\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

const uint8_t * get_ttf_bitmap(const lv_font_t * font, uint32_t unicode_letter)
{
    int error;
    error = FT_Load_Char(face, unicode_letter, FT_LOAD_RENDER);
    if (error) {
        printf("Could not load char in bitmap\n");
        return -1;
    }

    return face->glyph->bitmap.buffer;
}

int16_t get_ttf_width(const lv_font_t * font, uint32_t unicode_letter)
{
    int error;
    error = FT_Load_Char(face, unicode_letter, FT_LOAD_RENDER);
    if (error) {
        printf("Could not load char in width\n");
        return -1;
    }

    return face->glyph->bitmap.width;
}
