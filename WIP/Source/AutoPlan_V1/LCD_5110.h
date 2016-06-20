#ifndef LCD_5110_H
#define LCD_5110_H

#if ((DISPLAY_CONTROL == ENABLE) && (DISPLAY_MODE == iNOKIA5110))
/* Pin definitions:
Most of these pins can be moved to any digital or analog pin.
DN(MOSI)and SCLK should be left where they are (SPI pins). The
LED (backlight) pin should remain on a PWM-capable pin. */

#define LCD5110_PIN_SCE         7     // SCE - Chip select, pin 3 on LCD.
#define LCD5110_PIN_RST         6     // RST - Reset, pin 4 on LCD.
#define LCD5110_PIN_DC          5     // DC - Data/Command, pin 5 on LCD.
#define LCD5110_PIN_SD          11    // DN(MOSI) - Serial data, pin 6 on LCD.
#define LCD5110_PIN_SCL         13    // SCLK - Serial clock, pin 7 on LCD.
#define LCD5110_PIN_BLK         9     // LED - Backlight LED, pin 8 on LCD.

/* PCD8544-specific defines: */
#define LCD_COMMAND  0
#define LCD_DATA     1

/* 84x48 LCD Defines: */
#define LCD_WIDTH   84 // Note: x-coordinates go wide
#define LCD_HEIGHT  48 // Note: y-coordinates go high
#define WHITE       0  // For drawing pixels. A 0 draws white.
#define BLACK       1  // A 1 draws black.


extern void LCD5110_Hard_Init(void);
extern void UpdateDisplay(void);
#endif  /* ( (DISPLAY_CONTROL == ENABLE) && (DISPLAY_MODE == iNOKIA5110) ) */

#endif  /* LCD_5110_H */

