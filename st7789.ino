/**************************************************************************
 * 
 * Interfacing ESP8266 NodeMCU (ESP-12E) with ST7789 TFT display
     (240x240 pixel) and DS3231 real time clock chip.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
 *
 *************************************************************************/


#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789

#include "pic.c" //the picture


// ST7789 TFT module connections
#define TFT_RST   D8     // TFT RST pin is connected to NodeMCU pin D8 (GPIO15)
#define TFT_DC    D4     // TFT DC  pin is connected to NodeMCU pin D4 (GPIO2)
#define TFT_CS    -1     // TFT CS  pin is directly connected to GND
// initialize ST7789 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


void setup(void)
{
  // if the display has CS pin try with SPI_MODE0
  tft.init(240, 240, SPI_MODE2);    // init ST7789 display 240x240 pixel

  // if the screen is flipped, remove this command
  tft.setRotation(2);
  // fill the screen with black color

  // tft.fillScreen(ST77XX_BLACK);

  // tft.fillRect(0, 79, tft.width(), 2, ST77XX_BLUE);
  // tft.fillRect(0, 173, tft.width(), 2, ST77XX_BLUE);

  // tft.setTextWrap(false);                        // turn off text wrap option
  // tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);  // set text color to white and black background
  // tft.setTextSize(2);                 // text size = 2
  // tft.setCursor(21, 188);             // move cursor to position (28, 27) pixel
  // tft.print("CHIP TEMPERATURE:");
  // tft.setTextSize(4);                 // text size = 4
  // tft.setTextColor(ST77XX_MAGENTA, ST77XX_BLACK);
  // tft.setCursor(64, 94);
  // tft.print("TIME:");
  // // print degree symbol °C
  // tft.drawCircle(173, 218, 4, ST77XX_RED);
  // tft.drawCircle(173, 218, 5, ST77XX_RED);
  // tft.setCursor(184, 212);
  // tft.setTextColor(ST77XX_RED, ST77XX_BLACK);  // set text color to red and black background
  // tft.print("C");

  tft.fillScreen(ST77XX_BLACK);
  tft.drawRGBBitmap(0, 0, (uint16_t*)picture,240,240);
}


// main loop
void loop()
{

  
  delay(100);      // wait 100 ms
}

// end of code.
// drawRGBBitmap (int16_t x, int16_t y, uint16_t *pcolors, int16_t w, int16_t h)
// unsigned short picture[0xAE00]
