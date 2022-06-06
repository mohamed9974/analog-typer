#ifndef _SEVENSEG_H_
#define _SEVENSEG_H_

#include "Includes.h"
#include <cstdint>
#include <stdint.h>
// This is the PIC to Seven Segment pin mapping
// We use ports H and J for the 7-segment display
// The 7-segment display is connected to the PIC's
// port h pins 0-3 and port j pins 0-7 respectively
// PORT H is the one responsible for which 7-segment display is on
// PORT J is the one responsible for which digit is on
#define SEG_PORT_H PORTH
#define SEG_PORT_J PORTJ
#define SEG_PORT_H_DIR TRISH
#define SEG_PORT_J_DIR TRISJ
#define SEG_PORT_H_MASK 0b00001111
#define SEG_PORT_J_MASK 0b11111111
#define SEG_PORT_H_SHIFT 4
#define SEG_PORT_J_SHIFT 0

// You can use this array to convert numbers in range [0x0-0xF] to seven segment
// glyphs by using the value at the index that you want to convert.
// E.g. SSEGMENT_NUMBERS_GLYPHS[3] -> will display 3 on seven segment display.
volatile uint8_t SSEGMENT_NUMBERS_GLYPHS[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
    0x7F, 0x6F, 0x77, 0x7c, 0x58, 0x5E, 0x79, 0x71,
};

// initialize the 7-segment display
void InitSevenSeg(void);

// display a number on the 7-segment display
void DisplaySevenSeg(uint8_t number, uint8_t custom_char_pos);

// clear the 7-segment display
void ClearSevenSeg(void);

// update the 7-segment display
void UpdateSevenSeg(uint8_t,uint8_t);

#endif