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
// ADC aquisition time: 
//==============================================================================
void ADC_Init(void){
    // ADCON1 Register Configuration

}
