#include "header.h"


//==============================================================================
// Initiazlize the Ports 
//==============================================================================
void Initialize_Ports(void){
    // Set all the ports to be outputs
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    TRISF = 0x00;
    TRISG = 0x00;
    
    // Set all the ports to be outputs
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    PORTF = 0x00;
    PORTG = 0x00;
}