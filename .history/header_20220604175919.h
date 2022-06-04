#ifndef _HEADER_H
#define _HEADER_H

#include "adc.c"
#include "lcd.c"

//PIC 18F8722 ADC module initialization @40MHz


//==============================================================================
// Program discreption:
// Using the custom text entry program, the user will be able to enter any character he
// wants at any point in the first line of the LCD. By using the potentiometer, the user will be
// able to move the cursor to the cell he wants to insert a character. By using the buttons on
// the board, the user can select a character from the predefined set of characters ([a-z0-9])
// or he can insert a custom character he defines using the LEDs. When the user is done with
// the text entry, the text will scroll on the LCD infinitely.
// When the user wants to define a custom character, he will go into the custom character
// definition (CCD) mode. In this mode, the user will turn on and off LEDs in a 4x8 LED grid
// on the board. To move around this grid the user will use an invisible cursor which will be
// controlled by the buttons on the board. Since the cursor is invisible, the coordinates of the
// cursor will be displayed in the rightmost two digits of the seven-segment display.
// Due to constraints of the LCD, user can define at most 8 custom characters. Number
// of characters defined by the user will be shown in the leftmost digit of the seven-segment
// display