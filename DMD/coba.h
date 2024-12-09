

/*
 * Fareed Read
 * http://www.facebook.com/fareedreads
 *
 * font
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : coba.h
 * Date                : 06.03.2020
 * Font size in bytes  : 377
 * Font width          : 4
 * Font height         : 9
 * Font first char     : 48
 * Font last char      : 59
 * Font used chars     : 11
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef FONT_H
#define FONT_H

#define FONT_WIDTH 4
#define FONT_HEIGHT 9

const static uint8_t font[] PROGMEM = {
    0x01, 0x79, // size
    0x04, // width
    0x09, // height
    0x30, // first char
    0x0B, // char count
    
    // char widths
    0x04, 0x02, 0x04, 0x04, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 
    0x01, 
    
    // font data
    0xFE, 0x01, 0x01, 0xFE, 0x00, 0x80, 0x80, 0x00, // 48
    0x02, 0xFF, 0x00, 0x80, // 49
    0x86, 0x61, 0x19, 0x06, 0x80, 0x80, 0x80, 0x80, // 50
    0xC6, 0x01, 0x11, 0xEE, 0x00, 0x80, 0x80, 0x00, // 51
    0x60, 0x5C, 0x43, 0xF8, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, // 52
    0x9F, 0x11, 0x11, 0xE1, 0x00, 0x80, 0x80, 0x00, // 53
    0xFE, 0x11, 0x11, 0xE6, 0x00, 0x80, 0x80, 0x00, // 54
    0x03, 0x81, 0x79, 0x07, 0x00, 0x80, 0x00, 0x00, // 55
    0xEE, 0x11, 0x11, 0xEE, 0x00, 0x80, 0x80, 0x00, // 56
    0xCE, 0x11, 0x11, 0xFE, 0x00, 0x80, 0x80, 0x00, // 57
    0x10, 0x80 // 58
    
};

#endif
