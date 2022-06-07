#ifndef INCLUDES_H_
#define	INCLUDES_H_

// PIC18F8722 Configuration Bit Settings @ 40MHz

#include <xc.h>
#include <p18cxxx.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define _XTAL_FREQ   40000000

#pragma config  OSC = HSPLL, FCMEN = OFF, IESO = OFF
#pragma config  PWRT = OFF, BOREN = OFF, BORV = 3
#pragma config  WDT = OFF, WDTPS = 32768
#pragma config  MODE = MC, ADDRBW = ADDR20BIT, DATABW = DATA16BIT, WAIT = OFF
#pragma config  CCP2MX = PORTC, ECCPMX = PORTE, LPT1OSC = OFF, MCLRE = ON
#pragma config  STVREN = ON, LVP = OFF, BBSIZ = BB2K, XINST = OFF
#pragma config  CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CP4 = OFF, CP5 = OFF
#pragma config  CP6 = OFF, CP7 = OFF
#pragma config  CPB = OFF, CPD = OFF
#pragma config  WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRT4 = OFF
#pragma config  WRT5 = OFF, WRT6 = OFF, WRT7 = OFF
#pragma config  WRTC = OFF, WRTB = OFF, WRTD = OFF
#pragma config  EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTR4 = OFF
#pragma config  EBTR5 = OFF, EBTR6 = OFF, EBTR7 = OFF
#pragma config  EBTRB = OFF
#pragma config DEBUG = ON


typedef unsigned char byte;


#endif	/* _INCLUDES_H_ */

