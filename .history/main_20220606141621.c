#include "header.h"
#include "lcd.h"
#include <stdint.h>

typedef enum { TMR_IDLE, TMR_RUN, TMR_DONE } tmr_state_t;
typedef enum { BTN_IDLE, BTN_PRESSED, BTN_RELEASED } btn_state_t;
typedef enum { INIT, TEM, CDM, TSM } state_t;

uint8_t customCharPos;
uint8_t preCharPos;
uint8_t customCharCount;
uint8_t adcReading;
tmr_state_t t_state;
btn_state_t b_state;
state_t state;
uint8_t timer_count;
byte *customChar;

//==============================================================================
// Initialize global variables
//==============================================================================
void init_globals(void) {
  t_state = TMR_IDLE;
  b_state = BTN_IDLE;
  state = INIT;
  customCharPos = 0;
  customCharCount = 0;
  timer_count = 0;
  customChar = (byte *)malloc(sizeof(byte) * 8);
}
//==============================================================================
// Initiazlize the Ports
// Ports used:
// PORTA, PORTB, PORTC, PORTD, PORTE, PORTH, PORTJ
// PORT[A-D] are used for the LEDs
// PORT[B,D] are used for the LCD display (Covered in lcd.c)
// PORT[E] is used for the control buttons
// PORT[H-J] are used for the seven segment display (Covered in sevenseg.c)
// ADC ports are used for the potentiometer (Coverd in adc.c) and uses port A
// uninitialized ports are PORT C and PORT E
//==============================================================================
void Initialize_Ports() {
  // initialize the port C to be output for the LEDs
  TRISC = 0x00;
  // initialize the port E to be output for the control buttons
  TRISE = 0x00;
  // Clear port C and E latches
  clrf_ports();
}
//==============================================================================
void clrf_ports() {
  // Clear the port C and E latches
  LATC = 0x00;
  LATE = 0x00;
}
//==============================================================================
/********************** Timer task and fuctions *******************************/
//==============================================================================
// Initialize the timer
// Timer used: TMR0
//==============================================================================
void timer_init() {
  // Timer 0 is used for the delay functions
  // Set the TMR0 prescaler to 1:256
  OPTION_REGbits.T0CS = 0;
  // TMR0 preload value = 61
  // Freq = 40MHz / (256-61) = 1.6kHz
  // Period = 1.6kHz / 61 = 20ms
  // TMR0 = 61
  TMR0 = 61;
  // Enable the TMR0 interrupt
  INTCONbits.TMR0IE = 1;
  // Clear the TMR0 interrupt flag
  INTCONbits.TMR0IF = 0;
  // Enable the TMR0
  T0CONbits.TMR0ON = 1;
  // Set the TMR0 prescaler to 1:256
  T0CONbits.T08BIT = 0;
  T0CONbits.T0CS = 0;
  T0CONbits.PSA = 0;
  // low edge of the clock
  T0CONbits.T0SE = 0;
}
//==============================================================================
// Timer 0 interrupt service routine
// Timer used: TMR0
//==============================================================================
void timer_isr() {
  // Clear the TMR0 interrupt flag
  INTCONbits.TMR0IF = 0;
  // Increment the timer count
  timer_count++;
  // Check if the timer count is greater than the timer period
  if (timer_count > TIMER_PERIOD) {
    // Reset the timer count
    timer_count = 0;
    // Set the timer state to done
    t_state = TMR_DONE;
    // Set the timer preload value to 61
    TMR0 = 61;
  }
}
//==============================================================================
// Delay function
//==============================================================================
void delay_ms(uint16_t delay) {
  // Set the TMR0 prescaler to 1:256
  OPTION_REGbits.T0CS = 0;
  // TMR0 preload value = 61
  // Freq = 40MHz / (256-61) = 1.6kHz
  // Period = 1.6kHz / 61 = 20ms
  // TMR0 = 61
  TMR0 = 61;
  // Enable the TMR0 interrupt
  INTCONbits.TMR0IE = 1;
  // Clear the TMR0 interrupt flag
  INTCONbits.TMR0IF = 0;
  // Enable the TMR0
  T0CONbits.TMR0ON = 1;
  // Set the TMR0 prescaler to 1:256
  T0CONbits.T08BIT = 0;
  T0CONbits.T0CS = 0;
  T0CONbits.PSA = 0;
  // low edge of the clock
  T0CONbits.T0SE = 0;
  // Delay loop
  while (delay > 0) {
    // Wait for the TMR0 interrupt
    while (!INTCONbits.TMR0IF)
      ;
    // Clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;
    delay--;
  }
  // Disable the TMR0
  T0CONbits.TMR0ON = 0;
  // Disable the TMR0 interrupt
  INTCONbits.TMR0IE = 0;
}
// ============================================================================
// timer_update
//==============================================================================
void timer_update() {
  // Check the timer state
  switch (t_state) {
  // If the timer is idle
  case TMR_IDLE:
    // Do nothing
    break;
  // If the timer is running
  case TMR_RUN:
    // Check if the timer count is greater than the timer period
    if (timer_count > TIMER_PERIOD) {
      // Reset the timer count
      timer_count = 0;
      // Set the timer state to done
      t_state = TMR_DONE;
      // Set the timer preload value to 61
      TMR0 = 61;
    }
    break;
  // If the timer is done
  case TMR_DONE:
    // Set the timer state to idle
    t_state = TMR_IDLE;
    // Set the timer preload value to 61
    TMR0 = 61;
    break;
  }
}
// Initialize the buttons on port E RE0-RE4
// Buttons used:
// RE0 - RE4
//==============================================================================
void buttons_init() {
  // Set the port E to be input
  TRISE = 0xFF;
  // Clear the port E latches
  LATE = 0x00;
}
// ============================================================================
// ************* Input task and functions ****************
// The "input task" monitors RE[0-5] and increments associated counters
// whenever a high pulse is observed (i.e. HIGH followed by a LOW).
uint8_t re0_cnt = 0; // Current count for RE0 input
uint8_t re1_cnt = 0; // Current count for RE0 input
uint8_t re2_cnt = 0; // Current count for RE0 input
uint8_t re3_cnt = 0; // Current count for RE0 input
uint8_t re4_cnt = 0; // Current count for RE0 input
uint8_t re5_cnt = 0; // Current count for RE0 input
uint8_t re0_btn_st = 0, re1_btn_st = 0, re2_btn_st = 0, re3_btn_st = 0,
        re4_btn_st = 0, re5_btn_st = 0; // Button state

// This function resets the counter for RE0 input
void re0_reset() { re0_cnt = 0; }
// This function resets the counter for RE1 input
void re1_reset() { re1_cnt = 0; }
// This function resets the counter for RE2 input
void re2_reset() { re2_cnt = 0; }
// This function resets the counter for RE3 input
void re3_reset() { re3_cnt = 0; }
// This function resets the counter for RE4 input
void re4_reset() { re4_cnt = 0; }
// This function resets the counter for RE5 input
void re5_reset() { re5_cnt = 0; }

// This is the input task function
void button_pressing() {
  if (PORTEbits.RE0)
    re0_btn_st = 1;
  else if (re0_btn_st == 1) {
    // A high pulse has been observed on the CONFIGURE input
    re0_btn_st = 0;
    re0_cnt++;
  }
  if (PORTEbits.RE1)
    re1_btn_st = 1;
  else if (re1_btn_st == 1) {
    // A high pulse has been observed on the CONFIGURE input
    re1_btn_st = 0;
    re1_cnt++;
  }
  if (PORTEbits.RE2)
    re2_btn_st = 1;
  else if (re2_btn_st == 1) {
    // A high pulse has been observed on the CONFIGURE input
    re2_btn_st = 0;
    re2_cnt++;
  }
  if (PORTEbits.RE3)
    re3_btn_st = 1;
  else if (re3_btn_st == 1) {
    // A high pulse has been observed on the CONFIGURE input
    re3_btn_st = 0;
    re3_cnt++;
  }
  if (PORTEbits.RE4)
    re4_btn_st = 1;
  else if (re4_btn_st == 1) {
    // A high pulse has been observed on the CONFIGURE input
    re4_btn_st = 0;
    re4_cnt++;
  }
  if (PORTEbits.RE5)
    re5_btn_st = 1;
  else if (re5_btn_st == 1) {
    // A high pulse has been observed on the CONFIGURE input
    re5_btn_st = 0;
    re5_cnt++;
  }
}
//==============================================================================
// buttons interrupt service routine
// Buttons used:
// RE0 - RE5
//==============================================================================
void buttons_isr() {
  // Check the button state
  switch (b_state) {
  // If the button is idle
  case BTN_IDLE:
    // Check if the button is pressed
    if (PORT_E & 0x01) {
      // Set the button state to pressed
      b_state = BTN_PRESSED;
      // Set the button pressed
      b_pressed = 1;
    }
    break;
  // If the button is pressed
  case BTN_PRESSED:
    // Check if the button is released
    if (!(PORT_E & 0x01)) {
      // Set the button state to released
      b_state = BTN_RELEASED;
      // Set the button released
      b_released = 1;
    }
    break;
  // If the button is released
  case BTN_RELEASED:
    // Check if the button is pressed
    if (PORT_E & 0x01) {
      // Set the button state to pressed
      b_state = BTN_PRESSED;
      // Set the button pressed
      b_pressed = 1;
    }
    break;
  }
}
//==============================================================================
// buttons_init_interrupt
//==============================================================================
void buttons_init_interrupt() {
  // Set the interrupt priority
  RCONbits.IPEN = 1;
  // Set the interrupt priority
  INTCON2bits.TMR0IP = 1;
  // Set the interrupt priority
  INTCON2bits.INTEDG0 = 0;
  // Clear the interrupt flags
  INTCONbits.INT0IF = 0;
  INTCONbits.TMR0IF = 0;
  // Enable the interrupt
  INTCONbits.INT0IE = 1;
  // Enable the timer
  T0CONbits.TMR0ON = 1;
}
//==============================================================================
// buttons_update
//==============================================================================
void buttons_update() {
  // Check the button state
  switch (b_state) {
  // If the button is idle
  case BTN_IDLE:
    // Do nothing
    break;
  // If the button is pressed
  case BTN_PRESSED:
    // Check if the button is released
    if (b_released) {
      // Set the button state to released
      b_state = BTN_RELEASED;
      // Clear the button released
      b_released = 0;
    }
    break;
  // If the button is released
  case BTN_RELEASED:
    // Check if the button is pressed
    if (b_pressed) {
      // Set the button state to pressed
      b_state = BTN_PRESSED;
      // Clear the button pressed
      b_pressed = 0;
    }
    break;
  }
}

//==============================================================================
// Interrupt Service Routine handling lcd, adc, timer , buttons and leds
ISR(TIMER1_COMPA_vect) {
  // Timer1 is used to generate a 1ms interrupt
  // This interrupt is used to update the lcd and the adc
  // The timer is used to update the state of the game
  // The buttons are used to update the state of the game
  // The leds are used to update the state of the game
  // The lcd is used to update the state of the game
  // The adc is used to update the state of the game
  // The game is updated in the main loop

  // Update the lcd
  lcd_update();

  // Update the adc
  adc_update();

  // Update the timer
  timer_update();

  // Update the buttons
  button_isr();

  // Update the leds
  leds_update();

  // Update the seven segment display
  UpdateSevenSeg(customCharCount, customCharPos);
}
//==============================================================================
// Interrupt Handler 
//============================================================================== 
void __interrupt() ISR_Handler() {
  // Check if the interrupt is from the timer
  if (INTCONbits.TMR0IF) {
    // Clear the interrupt flag
    INTCONbits.TMR0IF = 0;
    // Update the timer
    timer_update();
  }
  // Check if the interrupt is from the ADC
  if (PIR1bits.ADIF) {
    // Clear the interrupt flag
    PIR1bits.ADIF = 0;
    // Update the adc
    if (state == TMS)
    adcReading = adc_update();
  }
}
//==============================================================================
// Interrupt intizialization for all the interrupts(buttons,timer)
//==============================================================================
void interrupts_init() {
  timer_init();
  buttons_init_interrupt();
  // initialize global interrupts
  INTCONbits.GIEH = 1;
  INTCONbits.GIEL = 1;
}
//==============================================================================
// Initialize the board
//==============================================================================
void board_init() {
  // initialize global variables
  init_globals();
  // initialize the ports
  Initialize_Ports();
  // Initialize the lcd
  lcd_init();
  // Initialize the adc
  adc_init();
  // Initialize the buttons
  buttons_init();
  // Initialize the leds
  leds_init();
  // Initialize the seven segment display
  InitSevenSeg();
  // Initialize the timer
  timer_init();
  // Initialize the interrupts
  interrupts_init();
  // Set the program state to idle
  state = TEM;
};

//==============================================================================
// Text entry mode routine
//==============================================================================
void text_entry_mode() {
  // Check the program state
  button_pressing();
  // check if the button RE5 is pressed
  if (re5_cnt > 0) {
    re5_reset();
    // Stay at the same program state
    state = TSM;
  } else if (re4_cnt > 0) {
    re4_reset();
    // Go to the CDM program state
    state = CDM;
  } else if (re3_cnt > 0) {
    re3_reset();
    // Scroll backwards in custom characters array
    customCharPos--;
    // Show the custom character on the LCD
    // TODO

  } else if (re2_cnt > 0) {
    re2_reset();
    // Scroll forwards in predefined characters array
    preCharPos++;
    // Show the predefined character on the LCD
    // TODO

  } else if (re1_cnt > 0) {
    re1_reset();
    // Scroll backwards in predefined characters array
    preCharPos--;
    // TODO

  } else if (re0_cnt > 0) {
    re0_reset();
    // Scroll forwards in custom characters array
    customCharPos++;
    // TODO
    // Stay at the same program state
  }
  if (re3_cnt > 0 || re2_cnt > 0 || re1_cnt > 0 || re0_cnt > 0) {
    // stay in the same program state
    state = TEM;
  }
}
// ============================================================================
// Main program routine
// description: the main program routine will initialize the board, and then
//              will call the main loop and depending on the state of the
//              program will call the appropriate function
// ============================================================================
void main(void) {
  board_init();
  while (1) {
    switch (state) {
    case IDLE:
      // the program hasnt been initizalized yet then wait till it is done.
      break;
    case TEM:
      // the program is in the text entry mode and the user can enter the
      // text
      text_entry_mode();
      break;
    case CDM:
      // the program is in the character display mode and the user can
      // display the text
      character_display_mode();
      break;
    case TSM:
      // the program is in the text scroll mode and the user can scroll the
      // text
      text_scroll_mode();
      break;
    }
  }
}