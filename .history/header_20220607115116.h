#ifndef _HEADER_H
#define _HEADER_H

#include "adc.c"
#include "lcd.c"
#include "lcd.h"
#include "sevenseg.h"

// PIC 18F8722 ADC module initialization @40MHz

//==============================================================================
// Program discreption:
// Using the custom text entry program, the user will be able to enter any
// character he wants at any point in the first line of the LCD. By using the
// potentiometer, the user will be able to move the cursor to the cell he wants
// to insert a character. By using the buttons on the board, the user can select
// a character from the predefined set of characters ([a-z0-9]) or he can insert
// a custom character he defines using the LEDs. When the user is done with the
// text entry, the text will scroll on the LCD inifintly. When the user wants
// to define a custom character, he will go into the custom character definition
// (CCD) mode. In this mode, the user will turn on and off LEDs in a 4x8 LED
// grid on the board. To move around this grid the user will use an invisible
// cursor which will be controlled by the buttons on the board. Since the cursor
// is invisible, the coordinates of the cursor will be displayed in the
// rightmost two digits of the seven-segment display. Due to constraints of the
// LCD, user can define at most 8 custom characters. Number of characters
// defined by the user will be shown in the leftmost digit of the seven-segment
// display
//==============================================================================
// Program Structure:
// The program is divided into 4 sections:
// 1. Initial configuration of the LCD and the ADC module
// 2. Text entry mode
// 3. Custom character definition mode
// 4. text scrolling mode
//==============================================================================
//==============================================================================
// 1. Initial configuration of the LCD and the ADC module
//==============================================================================
// The LCD is configured to be used in 4-bit mode. The LCD is configured to be
// used in 8-bit mode by setting the LCD_MODE_8BITS bit in the LCD_MODE
// register. The LCD is configured to be used in 8-bit mode by setting the
// LCD_MODE_8BITS bit in the LCD_MODE register. The ADC module is configured to
// be used in 8-bit mode. The ADC module is configured to be used in 8-bit mode
// by setting the ADCON1 register. All interrupts are enabled. programs moves to
// Text entry mode after it initializes ADC , LCD , Port and Interrupts
//==============================================================================
// Initialization Fuctions:
// void Initialize_ADC(void);
// void Initialize_LCD(void);
// void Initialize_sevseg(void);
// void Initialize_Ports(void);
// void Initialize_Interrupts(void);
// void initialize_variables(void);
// void intialize_timer(void);
//==============================================================================
void timer_init(void);
void timer_isr(void);
void delay_ms(uint16_t);
void timer_update(void);

void buttons_init();
void buttons_isr();
void buttons_update();
void button_pressing();

void init_globals(void);
void clrf_ports(void);
void Initialize_Ports(void);

void interrupts_init(void);
void board_init(void);

//==============================================================================
// 2. Text entry mode
//==============================================================================
// The text entry mode is activated by pressing the button on the board.n this
// state, the user is able to move the cursor around the first line of the LCD
// using the potentiometer. To change the text at the cursor’s position, the
// user will use the RE2 and RE1 buttons single press of the RE2 button will
// cycle the displayed character through the set of predefined characters in the
// forward direction. And pressing the RE1 button will cycle the displayed
// character in the backward direction
// In addition to the ability to insert predefined characters, the user can also
// insert the custom characters he/she already defined to the cursor’s position.
// Pressing the RE0 and RE3 buttons will cycle through the defined custom
// characters RE0 will go forward through the custom characters and RE3 will go
// backwards
// ==============================================================================
// Text entry mode functions:
// ==============================================================================
void text_entry_mode_init(void);
void text_entry_mode(void);
//TODO add the custom characters to the  text entry mode
// 3. Custom character definition mode
//==============================================================================
// The custom character definition mode is activated by pressing the
// button on the board. and using the LED grid. The custom character definition
// mode is activated.he user will use the R[ABCD][0-7] LEDs to enter a
// custom character. Each cell in the LCD is a 5x8 dot matrix and each LED
// corresponds to a single dot in the LCD cell. The user will use
// the RE4 button to turn on/off the LEDs
// the user will use the RE2, RE1, RE3, and RE0 buttons to move an invisible
// cursor up, down, left, and right over the LEDs, respectively.
// Meanwhile the cursor’s coordinates will be displayed in the
// seven-segment display.
// After entering a custom character by turning LEDs on and off, the user will
// press the RE5 button to go back into the TEM.
//==============================================================================
// Custom character definition mode functions:
void leds_grid_update(void);
void cdm_State_init(void);
void custom_character_definition_mode(void);
void move_cursor_up(void);    // RE2
void move_cursor_down(void);  // RE1
void move_cursor_left(void);  // RE3
void move_cursor_right(void); // RE0
void confirm_selection(void); // RE4


//==============================================================================
// 4. text scrolling mode (Text Scroll Mode)
//==============================================================================
// In Text Scroll Mode (TSM), the text entered by the user will start to scroll
// on the second line of the LCD. Meanwhile there will be a static “finished”
// text on the first line.  The cursor on the LCD will also disappear. At this
// mode no inputs will be accepted, and the program will stay in this state
// until the board has been reset
//==============================================================================
// text scrolling mode functions:
void text_scroll_mode(void);


#endif