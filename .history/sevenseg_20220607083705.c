#include "sevenseg.h"
#include <stdint.h>

int segPos= 0;
//==============================================================================
// Initiazlize the Ports H and J 
// we have no need for the port H[1]
// we have no need for the port J[7]
// Ports used:
// PORTH: [0, 2, 3]
// PORTJ: [0, 1, 2, 3, 4, 5, 6]
//==============================================================================
void InitSevenSeg(void){
    // Set the Tristate Register of PORTH to 0
    TRISH = 0x00;
    // Set the Tristate Register of PORTJ to 0
    TRISJ = 0x00;
    // Clear port H and J Latches
    LATH = 0x00;
    LATJ = 0x00;
    ClearSevenSeg();
    DisplaySevenSeg(0,0);
}

//==============================================================================
// DisplaySevenSeg
// Display the number 'num' on the seven segment display
// num: the number to be displayed
// pos: the position of the character to be displayed
// segPos: which 7-segment of the 4 to be displayed
//==============================================================================
void DisplaySevenSeg(uint8_t number, uint8_t custom_char_pos_x, uint8_t custom_char_pos_y){
    segPos = segPos % 4;
    LATH = (0b00000001) << segPos;
    switch (segPos) {
        case 0:
            LATJ = SSEGMENT_NUMBERS_GLYPHS[number];
            break;
        case 1:
            // show nothing on the seveg segment
            LATJ = 0x00;
            break;
        case 2:
            // get the tenths digit of custom_char_pos
            LATJ = SSEGMENT_NUMBERS_GLYPHS[custom_char_pos_x];
            break;
        case 3:
            // get the ones digit of custom_char_pos
            LATJ = SSEGMENT_NUMBERS_GLYPHS[custom_char_pos_y];
            break;
    }
    segPos++;
}
//==============================================================================
// ClearSevenSeg
// Clear the seven segment display
//==============================================================================
void ClearSevenSeg(void){
    LATH = 0x00;
    LATJ = 0x00;
}
//==============================================================================
// UpdateSevenSeg
// Update the seven segment display
// gets the new values of custome char pos and the number of custom characters 
// and loops over the h port to display the new values
//==============================================================================
void UpdateSevenSeg(uint8_t custom_char_num, uint8_t custom_char_pos_x, uint8_t custom_char_pos_y){
    for (segPos = 0; segPos < 4;) {
        DisplaySevenSeg(custom_char_num, custom_char_pos_x, custom_char_pos_y);
        if (segPos == 3) {
            segPos = 0;
        }
    }
}