#include "seven_Seg.h"

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

    DisplaySevenSeg(0,0);
}

//==============================================================================
// DisplaySevenSeg
// Display the number 'num' on the seven segment display
// num: the number to be displayed
//==============================================================================
