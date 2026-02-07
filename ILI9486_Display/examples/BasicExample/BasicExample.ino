/*
 * ILI9486_Display Library - Basic Example
 * 
 * Demonstrates basic setup and usage of the ILI9486 display
 * on ESP32-C5 microcontroller.
 * 
 * Hardware:
 * - ESP32-C5
 * - 3.5" TFT LCD with ILI9486 controller
 * 
 * Wiring:
 * ESP32-C5  →  ILI9486
 * GPIO10    →  CS
 * GPIO8     →  DC  
 * GPIO9     →  RST
 * GPIO4     →  MOSI (SDA)
 * GPIO3     →  SCLK (SCL)
 * 3.3V      →  VCC
 * GND       →  GND
 * 3.3V      →  LED
 */

#include "ILI9486_Display.h"

// Pin definitions for ESP32-C5 devboard (tested and verified)
#define TFT_CS    10
#define TFT_DC    8
#define TFT_RST   9
#define TFT_MOSI  4
#define TFT_SCLK  3

// Create display instance
ILI9486_Display tft(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK);

void setup() {
  Serial.begin(115200);
  Serial.println("ILI9486_Display Basic Example");
  
  // Initialize display
  tft.begin(27000000);
  tft.setRotation(0);  // Portrait mode (0-3 for different orientations)
  
  // Clear screen
  tft.fillScreen(TFT_BLACK);
  
  // Draw some graphics
  drawBasicShapes();
  
  delay(2000);
  
  // Display text
  displayText();
  
  Serial.println("Setup complete!");
}

void loop() {
  // Nothing here - all done in setup
}

void drawBasicShapes() {
  // Draw rectangles
  tft.drawRect(10, 10, 100, 50, TFT_CYAN);
  tft.fillRect(120, 10, 80, 50, TFT_RED);
  
  // Draw circles
  tft.drawCircle(60, 120, 40, TFT_GREEN);
  tft.fillCircle(160, 120, 30, TFT_BLUE);
  
  // Draw lines
  tft.drawLine(10, 200, 310, 200, TFT_YELLOW);
  tft.drawFastHLine(10, 220, 300, TFT_MAGENTA);
  tft.drawFastVLine(160, 230, 100, TFT_ORANGE);
  delay(1000);
  // Fill screen
  tft.fillScreen(TFT_BLUE);
  delay(1000);
  tft.fillScreen(TFT_CYAN);
  delay(3000);
}

void displayText() {
  // Clear screen
  tft.fillScreen(TFT_BLACK);
  
  // Set text properties
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  
  // Top-left aligned (default)
  tft.setTextDatum(TL_DATUM);
  tft.drawString("Top Left", 10, 50, 1);
  
  // Top-center aligned
  tft.setTextDatum(TC_DATUM);
  tft.drawString("Top Center", 160, 100, 1);
  
  // Middle-center aligned
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_CYAN);
  tft.drawString("Middle Center", 160, 240, 1);
  
  // Large text
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(TFT_ORANGE);
  tft.setTextSize(2);
  tft.drawString("ESP32-C5", 160, 350, 1);
  
  // Bottom text
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(1);
  tft.drawString("ILI9486 Display", 160, 450, 1);
}
