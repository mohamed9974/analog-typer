// File: ADC.h
#ifndef _ADC_H
#define _ADC_H

#include "Includes.h"

typedef unsigned char byte;

void ADC_Init(void);
void ADC_Start(void);
void ADC_Stop(void);
void ADC_Read(void);

#endif