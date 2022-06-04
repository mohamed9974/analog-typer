// File: ADC.h
#ifndef ADC_H
#define ADC_H

#include "Includes.h"
#include "lcd.h"

typedef unsigned char byte;

void ADC_Init(void);
void ADC_Start(void);
void ADC_Stop(void);
void ADC_Read(void);
//==============================================================================
// ADC_Init()
// Initializes the ADC module.
// Input: None
// Output: None
//==============================================================================
//PIC 18F8722 analog input pins:
//AN0 - AN7 - analog inputs
//RA0 - RA7 - digital inputs
//RB0 - RB7 - digital inputs
//RC0 - RC7 - digital inputs
//RD0 - RD7 - digital inputs
//RE0 - RE7 - digital inputs
//RF0 - RF7 - digital inputs
//RG0 - RG7 - digital inputs
//RH0 - RH7 - digital inputs
//RI0 - RI7 - digital inputs
//==============================================================================
//PIC 18F8722 ADC module initialization:
void ADC_Init(void) {
    // Set the ADC module to use Vcc as the reference voltage.
    ADCON0bits.ADFM = 1; //ADC result is right justified
    ADCON0bits.VCFG = 0; //Vref+ = Vdd, Vref- = Vss
    // @ 40 MHz, the ADC clock is 4 MHz. 
    // The ADC clock is divided by 16 to produce a 4 us conversion time.
    ADCON0bits.ADCS = 0b111; //ADC clock is Fosc/16
    // Enable the ADC module.
    ADCON0bits.ADON = 1;
    
    //ADCON1 configures the pin functions, and the voltage reference.
    ADCON1bits.ADFM = 1; //ADC result is right justified
    ADCON1bits.ADCS = 0b111; //ADC clock is Fosc/16
    ADCON1bits.VCFG = 0; //Vref+ = Vdd, Vref- = Vss
    //TODO - configure the correct pins as analog inputs
    ADCON1bits.PCFG = 0b1111; //AN0-AN7 are configured as analog inputs
    // Set the ADC module to use the internal clock.
    ADCON2bits.ADCS = 0b111;
}