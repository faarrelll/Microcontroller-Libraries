

/*
 * Fareed Read
 * http://www.facebook.com/fareedreads
 *
 * bismillah
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : font6x7.h
 * Date                : 06.03.2020
 * Font size in bytes  : 479
 * Font width          : 6
 * Font height         : -7
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

#ifndef BISMILLAH_H
#define BISMILLAH_H

#define BISMILLAH_WIDTH 6
#define BISMILLAH_HEIGHT -7

const static uint8_t bismillah[] PROGMEM = {
    0x01, 0xDF, // size
    0x06, // width
    0xF9, // height
    0x30, // first char
    0x0B, // char count
    
    // char widths
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
    0x06, 
    
    // font data
    0x00, 0xFE, 0x82, 0x82, 0xFE, 0x00, // 48
    0x00, 0x82, 0x82, 0xFE, 0x80, 0x80, // 49
    0x00, 0xF2, 0x92, 0x92, 0x9E, 0x00, // 50
    0x00, 0x92, 0x92, 0x92, 0xFE, 0x00, // 51
    0x30, 0x28, 0x24, 0x22, 0xFE, 0x20, // 52
    0x00, 0x9E, 0x92, 0x92, 0xF2, 0x00, // 53
    0x00, 0xFE, 0x92, 0x92, 0xF2, 0x00, // 54
    0x00, 0x02, 0x02, 0x02, 0xFE, 0x00, // 55
    0x00, 0xFE, 0x92, 0x92, 0xFE, 0x00, // 56
    0x00, 0x9E, 0x92, 0x92, 0xFE, 0x00, // 57
    0x00, 0x00, 0x6C, 0x6C, 0x00, 0x00 // 58
    
};

#endif
