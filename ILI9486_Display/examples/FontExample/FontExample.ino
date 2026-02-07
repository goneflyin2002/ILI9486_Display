/*
 * ILI9486 Display - Font System Example
 * Demonstrates Option D: Hybrid font selection with indexed fonts
 */

#include "ILI9486_Display.h"
#include "FreeSans9pt7b.h"
#include "Roboto_25.h"

// Define font pointers
#define FreeSans9 &FreeSans9pt7b
#define Roboto25 &Roboto_25

// Pin definitions
#define TFT_MOSI 4
#define TFT_SCLK 3
#define TFT_CS   10
#define TFT_DC   8
#define TFT_RST  9

ILI9486_Display tft(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK);

void setup() {
  Serial.begin(115200);
  
  // Initialize display
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  
  // Configure font array
  // fontArray[0] = reserved for "use current font"
  // fontArray[1] = reserved for built-in 5x7
  tft.fontArray[2] = FreeSans9;   // Index 2
  tft.fontArray[4] = Roboto25;    // Index 4
  // fontArray[3] and [5] remain nullptr (unused)
  
  demonstrateFontSystem();
}

void loop() {
  // Nothing here
}

void demonstrateFontSystem() {
  int16_t y = 20;
  int16_t width;
  
  // ========================================
  // Example 1: Using built-in 5x7 font (default)
  // ========================================
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  
  // Method A: No font parameter (uses current font - built-in 5x7)
  width = tft.drawString("Built-in 5x7 (default)", 10, y);
  Serial.print("Width: "); Serial.println(width);
  y += 20;
  
  // Method B: Explicit built-in (font=1)
  width = tft.drawString("Built-in 5x7 (explicit)", 10, y, 1);
  y += 30;
  
  // ========================================
  // Example 2: Using setFreeFont + drawString
  // ========================================
  tft.setFreeFont(FreeSans9);
  tft.setTextSize(1);
  
  // No font parameter - uses current font (FreeSans9)
  width = tft.drawString("FreeSans via setFreeFont", 10, y);
  y += 30;
  
  // ========================================
  // Example 3: Using indexed fonts
  // ========================================
  tft.setTextSize(1);
  
  // Font index 2 = FreeSans9
  width = tft.drawString("FreeSans via index 2", 10, y, 2);
  y += 30;
  
  // Font index 4 = Roboto25
  tft.setTextColor(TFT_CYAN);
  width = tft.drawString("Roboto25", 10, y, 4);
  y += 50;
  
  // ========================================
  // Example 4: Scaled text
  // ========================================
  tft.setTextColor(TFT_YELLOW);
  tft.setTextSize(2);  // 2x scaling
  
  // Built-in 5x7 scaled 2x
  width = tft.drawString("Scaled 2x", 10, y, 1);
  y += 40;
  
  // FreeSans9 scaled 2x
  tft.setTextSize(2);
  width = tft.drawString("FreeSans 2x", 10, y, 2);
  y += 60;
  
  // ========================================
  // Example 5: Centered text
  // ========================================
  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(1);
  
  int16_t centerX = 160;  // Assuming 320px wide screen
  
  width = tft.drawCentreString("Centered built-in", centerX, y, 1);
  y += 30;
  
  width = tft.drawCentreString("Centered FreeSans9", centerX, y, 2);
  y += 40;
  
  width = tft.drawCentreString("Centered Roboto25", centerX, y, 4);
  y += 50;
  
  // ========================================
  // Example 6: Error handling
  // ========================================
  tft.setTextColor(TFT_RED);
  
  // Font index 99 (out of bounds) - falls back to built-in 5x7
  width = tft.drawString("Font 99->fallback 5x7", 10, y, 99);
  y += 30;
  
  // Font index 3 (empty slot) - falls back to built-in 5x7
  width = tft.drawString("Font 3->fallback 5x7", 10, y, 3);
  y += 30;
  
  // ========================================
  // Example 7: Practical use case
  // ========================================
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(1);
  
  // Draw a channel label
  int16_t CHANNEL_A_CENTER = 80;
  
  tft.drawCentreString("CHANNEL A", CHANNEL_A_CENTER, 400, 2);  // FreeSans9
  tft.drawCentreString("TAP", CHANNEL_A_CENTER, 420, 4);        // Roboto25
  
  Serial.println("Font demonstration complete!");
}
