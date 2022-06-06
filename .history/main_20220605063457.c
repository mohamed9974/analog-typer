#include "header.h"



uint8_t customCharPos ;
uint8_t customCharCount ;
byte *customChar;

//==============================================================================
// Initiazlize the Ports 
// Ports used: 
// PORTA, PORTB, PORTC, PORTD, PORTE, PORTH, PORTJ
// PORT[A-D] are used for the LEDs 
// PORT[B,D] are used for the LCD display (Covered in lcd.c)
// PORT[E] is used for the control buttons
// PORT[H-J] are used for the seven segment display (Covered in sevenseg.c)
// ADC ports are used for the potentiometer (Coverd in adc.c)
//==============================================================================