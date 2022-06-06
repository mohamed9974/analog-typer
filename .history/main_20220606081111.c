#include "header.h"



uint8_t customCharPos ;
uint8_t customCharCount ;
uint8_t timer_count ;
byte *customChar;

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
void Initialize_Ports(){
    //initialize the port C to be output for the LEDs 
    TRISC = 0x00;
    //initialize the port E to be output for the control buttons
    TRISE = 0x00;
    // Clear port C and E latches
    LATC = 0x00;
    LATE = 0x00;
}
/********************** Timer task and fuctions *******************************/
//==============================================================================
// Initialize the timer
// Timer used: TMR0
//==============================================================================
void timer_init(){
    // Timer 0 is used for the delay functions
    // Set the TMR0 prescaler to 1:256
    OPTION_REGbits.T0CS = 0;
    //TMR0 preload value = 61
    //Freq = 40MHz / (256-61) = 1.6kHz
    //Period = 1.6kHz / 61 = 20ms
    //TMR0 = 61
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
void timer_isr(){
    // Clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;
    // Increment the timer count
    timer_count++;
}
//==============================================================================
/***************** Utility Functions *****************/
//==============================================================================
//==============================================================================
// Delay function
//==============================================================================
void delay_ms(uint16_t delay){
    // Set the TMR0 prescaler to 1:256
    OPTION_REGbits.T0CS = 0;
    //TMR0 preload value = 61
    //Freq = 40MHz / (256-61) = 1.6kHz
    //Period = 1.6kHz / 61 = 20ms
    //TMR0 = 61
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
    while(delay > 0){
        // Wait for the TMR0 interrupt
        while(!INTCONbits.TMR0IF);
        // Clear the TMR0 interrupt flag
        INTCONbits.TMR0IF = 0;
        delay--;
    }
    // Disable the TMR0
    T0CONbits.TMR0ON = 0;
    // Disable the TMR0 interrupt
    INTCONbits.TMR0IE = 0;
}
//==============================================================================
// interrupt requests
//==============================================================================
void init_irq(){
    // Enable the global interrupt
    INTCONbits.GIE = 1;
    // Enable the peripheral interrupt
    INTCONbits.PEIE = 1;
}
//==============================================================================
//==============================================================================
void init_variables(){
    // Initialize the custom character position
    customCharPos = 0;
    // Initialize the custom character count
    customCharCount = 0;
}
//==============================================================================
//==============================================================================
void clrf_ports(){
    // Clear the port C and E latches
    LATC = 0x00;
    LATE = 0x00;
}
//==============================================================================
