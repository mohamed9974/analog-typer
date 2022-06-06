#include "seven_Seg.h"

//==============================================================================
// Initiazlize the Ports H and J 
// we have no need for the port H[1]
// we have no need for the port J[7]
// Ports used:
// PORTH: [0, 2, 3]
// PORTJ: [0, 1, 2, 3, 4, 5, 6]
//==============================================================================
void InitPorts(void){
    // Set all the pins of PORTH as outputs
    DDRH = 0xFF;
    // Set all the pins of PORTJ as outputs
    DDRJ = 0xFF;
    // Set the Tristate Register of PORTH to 0
    TRISH = 0x00;
    // Set the Tristate Register of PORTJ to 0
    TRISJ = 0x00;

}