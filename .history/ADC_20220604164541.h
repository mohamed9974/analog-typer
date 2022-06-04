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
  ADCON0bits.ADFM = 1;
  ADCON0bits.VCFG = 0;
  ADCON0bits.ADCS = 0b111;
  ADCON0bits.ADON = 1;
  // Set the ADC module analog pins to be used.
  ADCON1bits.PCFG = 0b11111111;

  // Set the ADC module to use channel 0.
  ADCON1bits.CHS = 0b00000;
  // For 40MHZ -> Tosc = 1/40 us
  // Tad options (2xTosc, 4xTosc, 8xTosc, 16xTosc, 32xTosc, 64xTosc)
  // min Tad 0.7 us - max Tad 25 us (Keep as short as possible)
  // The closest one to min Tad (32xTosc) hence Tad = 32xTosc = 0.8 us
  ADCON2bits.ADCS = 0b010;
  // Acquisition time options (0xTad, 2xTad, 4xTad, 6xTad, 8xTad, 12xTad,
  // 16xTad, 20xTad) Min acquisition time = 2.4 us (the closest acqusition time
  // we can set 4xTad = 4us) (ACQT2:ACQT0=010)
  // The closest one to min acquisition time (4xTad) hence ACQT = 4xTad = 4us
  ADCON2bits.ACQT = 0b010;
}