/*
 * ILI9486 Display - Color Reference & Additional Colors
 * RGB565 format: RRRRRGGGGGGBBBBB (5-6-5 bits)
 */

// ============================================
// BUILT-IN COLORS (in ILI9486_Display.h)
// ============================================
// #define TFT_BLACK       0x0000
// #define TFT_WHITE       0xFFFF
// #define TFT_RED         0xF800
// #define TFT_GREEN       0x07E0
// #define TFT_BLUE        0x001F
// #define TFT_CYAN        0x07FF
// #define TFT_MAGENTA     0xF81F
// #define TFT_YELLOW      0xFFE0
// #define TFT_ORANGE      0xFD00  // FIXED - Pure orange
// #define TFT_GREENYELLOW 0xAFE5
// #define TFT_DARKGREY    0x7BEF
// #define TFT_LIGHTGREY   0xC618

// ============================================
// ADDITIONAL USEFUL COLORS
// Copy these to your sketch if needed
// ============================================

// Shades of Grey
#define TFT_DARKERGREY  0x4208  // Darker than DARKGREY
#define TFT_MEDIUMGREY  0x8410  // Medium grey
#define TFT_SILVER      0xC618  // Same as LIGHTGREY

// Shades of Red
#define TFT_MAROON      0x7800  // Dark red
#define TFT_DARKRED     0x8800  // Dark red
#define TFT_CRIMSON     0xD8A7  // Crimson red
#define TFT_PINK        0xFE19  // Pink
#define TFT_HOTPINK     0xFB56  // Hot pink

// Shades of Orange
#define TFT_DARKORANGE  0xFC00  // Darker orange (less yellow)
#define TFT_LIGHTORANGE 0xFE00  // Lighter orange
#define TFT_CORAL       0xFBEA  // Coral (orange-pink)

// Shades of Yellow
#define TFT_GOLD        0xFEA0  // Gold
#define TFT_LIGHTYELLOW 0xFFF0  // Light yellow

// Shades of Green
#define TFT_DARKGREEN   0x03E0  // Dark green
#define TFT_FORESTGREEN 0x2444  // Forest green
#define TFT_LIME        0x07E0  // Lime (same as GREEN)
#define TFT_LIGHTGREEN  0x9772  // Light green
#define TFT_OLIVE       0x7BE0  // Olive

// Shades of Blue
#define TFT_NAVY        0x000F  // Navy blue (dark)
#define TFT_DARKBLUE    0x0011  // Dark blue
#define TFT_MEDIUMBLUE  0x0019  // Medium blue
#define TFT_SKYBLUE     0x867D  // Sky blue
#define TFT_LIGHTBLUE   0xAEDC  // Light blue
#define TFT_STEELBLUE   0x4416  // Steel blue

// Purples
#define TFT_PURPLE      0x780F  // Purple
#define TFT_VIOLET      0x901A  // Violet
#define TFT_INDIGO      0x4810  // Indigo

// Browns
#define TFT_BROWN       0xA145  // Brown
#define TFT_DARKBROWN   0x5940  // Dark brown
#define TFT_TAN         0xD5B1  // Tan
#define TFT_BEIGE       0xF7BB  // Beige

// Other useful colors
#define TFT_TURQUOISE   0x471A  // Turquoise
#define TFT_TEAL        0x0410  // Teal
#define TFT_AQUA        0x07FF  // Aqua (same as CYAN)
#define TFT_LAVENDER    0xE73F  // Lavender
#define TFT_PEACH       0xFED7  // Peach

// ============================================
// BREWERY/BEER THEMED COLORS
// ============================================
#define TFT_AMBER       0xFD40  // Amber beer color
#define TFT_STOUT       0x2104  // Dark stout color
#define TFT_WHEAT       0xFFD9  // Wheat beer color
#define TFT_COPPER      0xB388  // Copper color
#define TFT_BRONZE      0xA346  // Bronze color
#define TFT_HOPS_GREEN  0x4E06  // Hops green

// ============================================
// STATUS COLORS
// ============================================
#define TFT_SUCCESS     0x07E0  // Green (same as GREEN)
#define TFT_WARNING     0xFD00  // Orange (same as ORANGE)
#define TFT_ERROR       0xF800  // Red (same as RED)
#define TFT_INFO        0x067F  // Blue-cyan

// ============================================
// HOW TO USE color565() FOR CUSTOM COLORS
// ============================================

/*
// In your sketch:

// Method 1: Use color565() for RGB values
uint16_t myColor = tft.color565(255, 100, 50);  // RGB(255, 100, 50)
tft.setTextColor(myColor);

// Method 2: Define constants
#define MY_CUSTOM_COLOR tft.color565(128, 64, 200)

// Method 3: Calculate RGB565 manually
// Formula: color565 = (R & 0xF8) << 8 | (G & 0xFC) << 3 | B >> 3
// Where R, G, B are 0-255

// Example: RGB(200, 100, 50)
// R: 200 → (200 & 0xF8) = 200 → shift left 8 = 0xC800
// G: 100 → (100 & 0xFC) = 96 → shift left 3 = 0x0300
// B: 50 → (50 >> 3) = 6 → 0x0006
// Result: 0xC800 | 0x0300 | 0x0006 = 0xCB06
*/

// ============================================
// COLOR TESTING SKETCH
// ============================================

/*
// Test colors on your display:

#include "ILI9486_Display.h"

ILI9486_Display tft(CS, DC, RST, MOSI, SCLK);

void setup() {
  tft.begin();
  tft.fillScreen(TFT_BLACK);
  
  // Test orange variations
  tft.fillRect(0, 0, 80, 50, TFT_ORANGE);      // Pure orange (fixed)
  tft.fillRect(80, 0, 80, 50, TFT_DARKORANGE); // Darker orange
  tft.fillRect(160, 0, 80, 50, TFT_CORAL);     // Coral
  tft.fillRect(240, 0, 80, 50, TFT_AMBER);     // Amber
  
  // Label them
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("ORANGE", 40, 55, 1);
  tft.drawString("DARK", 120, 55, 1);
  tft.drawString("CORAL", 200, 55, 1);
  tft.drawString("AMBER", 280, 55, 1);
}

void loop() {}
*/

// ============================================
// RGB565 COLOR PICKER
// ============================================

/*
// Use this to find RGB565 values:

void showColorTest(uint8_t r, uint8_t g, uint8_t b) {
  uint16_t color = tft.color565(r, g, b);
  tft.fillRect(100, 100, 120, 120, color);
  
  // Show hex value
  char buf[20];
  sprintf(buf, "0x%04X", color);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString(buf, 160, 230, 2);
  
  // Show RGB values
  sprintf(buf, "R:%d G:%d B:%d", r, g, b);
  tft.drawString(buf, 160, 250, 1);
}

// Call with different RGB values:
showColorTest(255, 165, 0);  // Pure orange
showColorTest(255, 128, 0);  // Dark orange
showColorTest(255, 200, 0);  // Light orange
*/

// ============================================
// GRADIENT EXAMPLE
// ============================================

/*
// Create smooth color gradients:

void drawGradient(int16_t x, int16_t y, int16_t w, int16_t h, 
                  uint8_t r1, uint8_t g1, uint8_t b1,
                  uint8_t r2, uint8_t g2, uint8_t b2) {
  for (int16_t i = 0; i < h; i++) {
    float ratio = (float)i / (float)h;
    uint8_t r = r1 + (r2 - r1) * ratio;
    uint8_t g = g1 + (g2 - g1) * ratio;
    uint8_t b = b1 + (b2 - b1) * ratio;
    uint16_t color = tft.color565(r, g, b);
    tft.drawFastHLine(x, y + i, w, color);
  }
}

// Usage: Gradient from orange to red
drawGradient(0, 0, 320, 100, 255, 165, 0, 255, 0, 0);
*/

// ============================================
// NOTES
// ============================================

/*
RGB565 Precision Loss:
- Red: 8-bit (256 values) → 5-bit (32 values) = Lost 3 bits
- Green: 8-bit (256 values) → 6-bit (64 values) = Lost 2 bits  
- Blue: 8-bit (256 values) → 5-bit (32 values) = Lost 3 bits

This means:
- Not all RGB values can be displayed exactly
- Similar RGB values may look identical
- Green has better precision than red/blue

For best results:
- Stick to multiples of 8 for R and B (8, 16, 24... 248)
- Stick to multiples of 4 for G (4, 8, 12... 252)
- Or use the color565() function and let it handle conversion
*/
