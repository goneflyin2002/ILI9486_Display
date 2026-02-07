/*
 * ILI9486 Display - Text Datum System Example
 * Demonstrates how to use setTextDatum() for precise text positioning
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

// Screen dimensions
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 480
#define CENTER_X      (SCREEN_WIDTH / 2)
#define CENTER_Y      (SCREEN_HEIGHT / 2)

void setup() {
  Serial.begin(115200);
  
  // Initialize display
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  
  // Configure font array
  tft.fontArray[2] = FreeSans9;
  tft.fontArray[4] = Roboto25;
  
  demonstrateDatumSystem();
}

void loop() {
  // Nothing here
}

void demonstrateDatumSystem() {
  
  // ===========================================
  // Example 1: TC_DATUM (Top Center)
  // This is what you typically use for titles
  // ===========================================
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(TFT_CYAN);
  tft.setTextSize(1);
  
  // Draw title centered at top
  tft.drawString("MAIN MENU", CENTER_X, 20, 4);  // Roboto25 centered
  
  // Draw a horizontal line to show the Y=20 position
  tft.drawFastHLine(0, 20, SCREEN_WIDTH, TFT_RED);
  
  Serial.println("TC_DATUM: Text centered horizontally, Y is at TOP of text");
  
  // ===========================================
  // Example 2: TL_DATUM (Top Left) - DEFAULT
  // This is the default, most common for UI
  // ===========================================
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(TFT_WHITE);
  
  // Draw labels from top-left
  int16_t y = 100;
  tft.drawString("Status:", 10, y, 2);        // FreeSans9
  tft.setTextColor(TFT_GREEN);
  tft.drawString("READY", 80, y, 2);          // Same Y line
  y += 30;
  
  tft.setTextColor(TFT_WHITE);
  tft.drawString("Temp:", 10, y, 2);
  tft.setTextColor(TFT_YELLOW);
  tft.drawString("25.3C", 80, y, 2);
  
  Serial.println("TL_DATUM: Text positioned from top-left corner");
  
  // ===========================================
  // Example 3: MC_DATUM (Middle Center)
  // Perfect for centered messages
  // ===========================================
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_MAGENTA);
  
  // Draw centered both horizontally and vertically
  tft.drawString("CENTER", CENTER_X, CENTER_Y, 4);
  
  // Draw crosshairs to show the exact center point
  tft.drawFastHLine(CENTER_X - 20, CENTER_Y, 40, TFT_RED);
  tft.drawFastVLine(CENTER_X, CENTER_Y - 20, 40, TFT_RED);
  
  Serial.println("MC_DATUM: Text centered both horizontally and vertically");
  
  // ===========================================
  // Example 4: Your typical use case
  // Channel labels with TC_DATUM
  // ===========================================
  tft.setTextDatum(TC_DATUM);
  
  int16_t CHANNEL_A_CENTER = 80;
  int16_t CHANNEL_B_CENTER = 240;
  int16_t label_y = 380;
  
  // Channel A
  tft.setTextColor(TFT_WHITE);
  tft.drawString("CHANNEL A", CHANNEL_A_CENTER, label_y, 2);
  tft.setTextColor(TFT_CYAN);
  tft.drawString("TAP", CHANNEL_A_CENTER, label_y + 20, 4);
  
  // Channel B
  tft.setTextColor(TFT_WHITE);
  tft.drawString("CHANNEL B", CHANNEL_B_CENTER, label_y, 2);
  tft.setTextColor(TFT_GREEN);
  tft.drawString("LAGER", CHANNEL_B_CENTER, label_y + 20, 4);
  
  Serial.println("TC_DATUM for channel labels: Perfect alignment!");
  
  // ===========================================
  // Example 5: All 9 datum positions
  // Visual reference grid
  // ===========================================
  delay(3000);
  tft.fillScreen(TFT_BLACK);
  
  int16_t grid_x[] = {60, 160, 260};  // Left, Center, Right
  int16_t grid_y[] = {60, 160, 260};  // Top, Middle, Bottom
  const char* datum_names[] = {"TL", "TC", "TR", "ML", "MC", "MR", "BL", "BC", "BR"};
  
  tft.setTextSize(1);
  
  for (int datum = 0; datum < 9; datum++) {
    int col = datum % 3;
    int row = datum / 3;
    int16_t px = grid_x[col];
    int16_t py = grid_y[row];
    
    // Draw crosshair at reference point
    tft.drawFastHLine(px - 15, py, 30, TFT_DARKGREY);
    tft.drawFastVLine(px, py - 15, 30, TFT_DARKGREY);
    
    // Draw text with this datum
    tft.setTextDatum(datum);
    tft.setTextColor(TFT_YELLOW);
    tft.drawString(datum_names[datum], px, py, 2);
  }
  
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("9 Datum Positions", CENTER_X, 10, 1);
  tft.drawString("+ marks reference point", CENTER_X, 30, 1);
  
  Serial.println("Datum grid complete - shows all 9 positioning modes");
  
  // ===========================================
  // Example 6: drawCentreString still works
  // It ignores datum and always centers on X
  // ===========================================
  delay(3000);
  tft.fillScreen(TFT_BLACK);
  
  tft.setTextDatum(TL_DATUM);  // Even with TL_DATUM...
  tft.setTextColor(TFT_CYAN);
  
  // drawCentreString still centers (independent of datum)
  tft.drawCentreString("drawCentreString", CENTER_X, 100, 2);
  tft.setTextColor(TFT_WHITE);
  tft.drawCentreString("ignores datum", CENTER_X, 130, 1);
  tft.drawCentreString("always centers on X", CENTER_X, 150, 1);
  
  Serial.println("drawCentreString works independently of datum setting");
}

/*
 * DATUM QUICK REFERENCE:
 * 
 * TL_DATUM (0) - Top Left      - X=left edge, Y=top edge
 * TC_DATUM (1) - Top Center    - X=center, Y=top edge      ← Most common for titles
 * TR_DATUM (2) - Top Right     - X=right edge, Y=top edge
 * 
 * ML_DATUM (3) - Middle Left   - X=left edge, Y=vertical center
 * MC_DATUM (4) - Middle Center - X=center, Y=vertical center  ← Centered text
 * MR_DATUM (5) - Middle Right  - X=right edge, Y=vertical center
 * 
 * BL_DATUM (6) - Bottom Left   - X=left edge, Y=baseline
 * BC_DATUM (7) - Bottom Center - X=center, Y=baseline
 * BR_DATUM (8) - Bottom Right  - X=right edge, Y=baseline
 * 
 * USAGE PATTERN:
 * 
 * void drawChannelInfo() {
 *   tft.setTextDatum(TC_DATUM);  // Set once per function
 *   tft.setTextColor(TFT_WHITE);
 *   tft.drawString("CHANNEL A", 80, 100, 2);   // All subsequent calls
 *   tft.drawString("TAP", 80, 120, 4);         // use TC_DATUM
 *   tft.drawString("4.5%", 80, 160, 2);
 * }
 */
