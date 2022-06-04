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


//PIC 18F8722 ADC module initialization @40MHz
//==============================================================================
// ADC_Init()
// Initializes the ADC module.
// Input: None
// Output: None
// Chip frequency: 40MHz
// ADC clock frequency: 40MHz/10 = 4MHz
// ADC conversion time: 4MHz/16 = 250ns
// ADC Voltage Reference: 5V (VREF+ = VDD, VREF- = VSS)
// ADC Resolution: 10 bits
// ADC Input Channels: [AN0-AN7]
// ADC Input Buffer Gain: 1x
// ADC interrupt: Enabled
// ADC aquisition time: 4*ADC_CLK_PERIOD = 4*250ns = 1us
// ADC should cycle through 40 samples 
// ADC resolution: 10 bits
//==============================================================================
void ADC_Init(void){
    //ADCON1 Register 
    ADCON1bits.ADCS = 0b0100; //ADC conversion clock period: 4*ADC_CLK_PERIOD = 4*250ns = 1us
    ADCON1bits.ADFM = 1; //ADC result right justified   
    ADCON1bits.ADPREF = 0b00; //ADC Voltage Reference: 5V (VREF+ = VDD, VREF- = VSS)
    ADCON1bits.ADNREF = 0b0; //ADC Voltage Reference: VSS
    ADCON1bits.ADON = 1; //ADC module enable

    //ADCON2 Register
    ADCON2bits.ACQT = 0b100; //ADC aquisition time: 4*ADC_CLK_PERIOD = 4*250ns = 1us
    ADCON2bits.ADCS2 = 0b1; //ADC conversion clock period: 4*ADC_CLK_PERIOD = 4*250ns = 1us
    ADCON2bits.ADCS1 = 0b0; //ADC conversion clock period: 4*ADC_CLK_PERIOD = 4*250ns = 1us
    ADCON2bits.ADCS0 = 0b0; //ADC conversion clock period: 4*ADC_CLK_PERIOD = 4*250ns = 1us
}