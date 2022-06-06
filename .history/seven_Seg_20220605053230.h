#ifndef _SEVEN_SEG_H_
#define _SEVEN_SEG_H_

#include "Includes.h"
// This is the PIC to Seven Segment pin mapping
// We use ports H and J for the 7-segment display






// You can use this array to convert numbers in range [0x0-0xF] to seven segment
// glyphs by using the value at the index that you want to convert.
// E.g. SSEGMENT_NUMBERS_GLYPHS[3] -> will display 3 on seven segment display.
volatile uint8_t SSEGMENT_NUMBERS_GLYPHS[] = {
  0x3F, 0x06, 0x5B, 0x4F,
  0x66, 0x6D, 0x7D, 0x07,
  0x7F, 0x6F, 0x77, 0x7c,
  0x58, 0x5E, 0x79, 0x71,
};
