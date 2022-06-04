#include "header.h"


//==============================================================================
// Initiazlize the Ports 
//==============================================================================
void Initialize_Ports(void){
    // Set LCD pins as outputs
    
    LCD_D4 = 0;
    LCD_D5 = 0;
    LCD_D6 = 0;
    LCD_D7 = 0;
    LCD_RS = 0;
    LCD_PORT = 0x00;
    // Set LED pins as outputs
    LED_DDR = 0xFF;
    LED_PORT = 0x00;
    // Set button pins as inputs
    BUTTON_DDR = 0x00;
    BUTTON_PORT = 0xFF;
    // Set ADC pins as inputs
    ADC_DDR = 0x00;
    ADC_PORT = 0xFF;
    // Set PWM pins as outputs
    PWM_DDR = 0xFF;
    PWM_PORT = 0x00;
    // Set PWM pins as outputs
    PWM_DDR = 0xFF;
    PWM_PORT = 0x00;

}