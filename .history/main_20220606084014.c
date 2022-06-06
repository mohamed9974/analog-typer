#include "header.h"
#include <stdint.h>

typedef enum { TMR_IDLE, TMR_RUN, TMR_DONE } tmr_state_t;

uint8_t customCharPos;
uint8_t customCharCount;
tmr_state_t t_state;
uint8_t timer_count;
byte *customChar;

// Interrupt Service Routine handling lcd, adc, timer , buttons and leds
ISR( TIMER1_COMPA_vect )
{
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
    buttons_update();
    
    // Update the leds
    leds_update();

    // Update the seven segment display
    UpdateSevenSeg(customCharCount, customCharPos);
    
    // Update the game
    game_update();
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