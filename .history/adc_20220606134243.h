// File: ADC.h
#ifndef _ADC_H
#define _ADC_H

#include "Includes.h"
#define ADC_PORT_DIR TRISA



void ADC_Init(void);
void ADC_Start(void);
void ADC_Stop(void);
void ADC_Read(byte);
int adc_update(void);

#endif