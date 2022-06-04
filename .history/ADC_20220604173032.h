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
// Frequency:
//==============================================================================
void ADC_Init(void) {
