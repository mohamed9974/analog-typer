#include "lcd.h"

void Pulse(void) {
  LCD_EN = 1;
  __delay_us(LCD_PULSE);
  LCD_EN = 0;
  __delay_us(LCD_PULSE);
}

void InitLCD(void) {
  __delay_ms(20);
  PORTD = 0x30;
  Pulse();

  __delay_ms(6);
  PORTD = 0x30;
  Pulse();

  __delay_us(300);
  PORTD = 0x30;
  Pulse();

  __delay_ms(2);
  PORTD = 0x20;
  Pulse();

  LcdCmd(0x2C);
  LcdCmd(0x0C);
  LcdClear();
}

void LcdCmd(uint8_t cmd) {
  // Send 'cmd' as a command to the LCD.
  LCD_EN = 0;
  LCD_RS = 0;
  LCD_PORT = cmd;
  Pulse();
}
void LcdData(uint8_t data) {
  // Send 'data' as data to the LCD.
  LCD_EN = 0;
  LCD_RS = 1;
  LCD_PORT = data;
  Pulse();
  LCD_RS = 0;
}

// Sets the current display cursor of the LCD
//  row : the row at which the text will be displayed, a value from [1, 2]
//  col : the column  at which the text will be displayed, a value from [1, 16]
void LcdSetCursor(uint8_t row, uint8_t col) {
  if (row == 1) {
    LcdCmd(0x80 + col - 1);
  } else if (row == 2) {
    LcdCmd(0xC0 + col - 1);
  }
}

void LcdClear(void) {
  LcdCmd(0x01);
  __delay_ms(2);
}

void CreateChar(uint8_t addr, uint8_t charmap[]) {
  addr &= 0x7;                // we only have 8 locations 0-7
  LcdCmd(0x40 | (addr << 3)); // Set the address for custom char.
  for (int i = 0; i < 8; i++) {
    LcdData(charmap[i]); // Write char data.
  }
}

void LcdPrint(char *str) {
  while (*str) {
    LcdData(*str++);
  }
}

void LcdPrintatlocation(char *buf, uint8_t row, uint8_t col) {
  LcdSetCursor(row, col);
  LcdPrint(buf);
}

void LcdPrintAll(char *buf) {
  // Send 'buf' to the LCD.
  // Prints up to 16 characters.
  // If more than 16 characters are sent,
  // the string will be cycled. from the beginning.
  int x, y = 1;
  uint8_t i = 0;
  while (buf[i] != '\0') {
    LcdData(buf[i]);
    i++;
    x++;
    if (x == 17) {
      x = 1;
      y++;
      if (y == 3) {
        y = 1;
        LcdCmd(0x80);
      } else {
        LcdCmd(0xC0);
      }
      LcdSetCursor(y, x);
    }
  }
}
void LcdPrintFirstRow(char *buf) {
  // Send 'buf' to the LCD.
  // Prints up to 16 characters.
  // If more than 16 characters are sent,
  // the string will be cycled. from the beginning.
  int x = 1;
  uint8_t i = 0;
  for (i = 0; i < 16; i++) {
    LcdData(buf[i]);
    x++;
    if (x == 17) {
      x = 1;
      LcdCmd(0x80);
      LcdSetCursor(1, x);
    }
  }
}
void LcdPrintSecondRow(char *buf){
    // Send 'buf' to the LCD.
    // Prints up to 16 characters.
    // If more than 16 characters are sent,
    // the string will be cycled. from the beginning.
    int x = 1;
    uint8_t i = 0;
    for (i = 0; i < 16; i++) {
        LcdData(buf[i]);
        x++;
        if (x == 17) {
        x = 1;
        LcdCmd(0xC0);
        LcdSetCursor(2, x);
        }
    }
}

void lcd_update() {
  // Updates the current state of the LCD. from values to blinking characters
  // and to string wraping
  // TODO
}