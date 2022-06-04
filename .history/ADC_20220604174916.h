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

#endif