#include "adc.h"
#include "Includes.h"

// PIC 18F8722 ADC module initialization @40MHz
//==============================================================================
//  ADC_Init()
//  Initializes the ADC module.
//  Input: None
//  Output: None
//  Chip frequency: 40MHz
//  ADC clock frequency: 40MHz/10 = 4MHz
//  ADC conversion time: 4MHz/16 = 250ns
//  ADC Voltage Reference: 5V (VREF+ = VDD, VREF- = VSS)
//  ADC Resolution: 10 bits
//  ADC Input Channels: [AN0-AN7]
//  ADC Input Buffer Gain: 1x
//  ADC interrupt: Enabled
//  ADC aquisition time: 4*ADC_CLK_PERIOD = 4*250ns = 1us
//  ADC should cycle through 40 samples
//  ADC resolution: 10 bits
//==============================================================================
void ADC_Init(void) {
  // ADCON1 Register
  ADCON1bits.ADCS =
      0b010; // ADC conversion clock period: 4*ADC_CLK_PERIOD = 4*250ns = 1us
  ADCON1bits.ADFM = 1; // ADC result right justified
  ADCON1bits.ADPREF =
      0b00; // ADC Voltage Reference: 5V (VREF+ = VDD, VREF- = VSS)
  ADCON1bits.ADNREF = 0b0;  // ADC Voltage Reference: VSS
  ADCON1bits.ADON = 1;      // ADC module enable
  ADCON1bits.PCFG = 0b1100; // ADC input channels: [AN0-AN7]
  ADCON1bits.VCFG = 0b00;   // ADC Input Buffer Gain: 1x

  // Tristate Register
  ADC_PORT_DIR = 0x05; // AN0-AN3 are inputs
  // ADCON2 Register
  ADCON2bits.ACQT =
      0b010; // ADC aquisition time: 4*ADC_CLK_PERIOD = 4*250ns = 1us
  ADCON2bits.ADCS =
      0b010; // ADC conversion clock period: 4*ADC_CLK_PERIOD = 4*250ns = 1us
  ADCON2bits.ADRC = 0b0; // ADC conversion clock source: FOSC/2
  ADCON2bits.ADFM = 1;   // ADC result right justified

  // ADCON0 Register
  ADCON0bits.CHS = 0b0000; // ADC input channel: AN0
  ADCON0bits.ADCS =
      0b100; // ADC conversion clock period: 4*ADC_CLK_PERIOD = 4*250ns = 1us
  ADCON0bits.GO_DONE = 0b0; // ADC conversion start: Disabled
  ADCON0bits.ADON = 1;      // ADC module enable

  // ADC interrupt
  IPR1bits.ADIP = 1; // ADC interrupt priority: High
  PIR1bits.ADIF = 0; // ADC interrupt flag: Clear
  PIE1bits.ADIE = 1; // ADC interrupt enable
}

// PIC 18F8722 ADC module start conversion
//==============================================================================
//  ADC_Start()
//  Starts the ADC module.
//  Input: None
//  Output: None
//==============================================================================
void ADC_Start(void) {
  ADCON0bits.GO_DONE = 1; // ADC conversion start: Enabled
}

// PIC 18F8722 ADC module stop conversion
//==============================================================================
//  ADC_Stop()
//  Stops the ADC module.
//  Input: None
//  Output: None
//==============================================================================
void ADC_Stop(void) {
  ADCON0bits.GO_DONE = 0; // ADC conversion start: Disabled
}

// PIC 18F8722 ADC module read conversion
//==============================================================================
//  ADC_Read()
//  Reads the ADC module.
//  Input: None
//  Output: None
//==============================================================================
void ADC_Read(byte channel) {
  ADCON0bits.CHS = channel; // ADC input channel: AN0
  ADCON0bits.GO_DONE = 1;   // ADC conversion start: Enabled
  while (ADCON0bits.GO_DONE == 1)
    ; // Wait for conversion to complete
}