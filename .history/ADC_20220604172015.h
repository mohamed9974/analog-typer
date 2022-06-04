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
void ADC_Init(void) {
    // Set the ADC module to use Vcc as the reference voltage.
    ADCON0bits.ADFM = 1; //ADC result is right justified
    ADCON0bits.VCFG = 0; //Vref+ = Vdd, Vref- = Vss
    // @ 40 MHz, the ADC clock is 4 MHz. 
    // The ADC clock is divided by 16 to produce a 4 us conversion time.
    ADCON0bits.ADCS = 0b111; //ADC clock is Fosc/16
    // Enable the ADC module.
    ADCON0bits.ADON = 1;
    
    // Set the ADC module to use channel 0.
    ADCON1bits.CHS = 0b00000;
    
    // Set the ADC module to use the internal clock.
    ADCON2bits.ADCS = 0b111;
}