# ILI9486 Display Library - Font System Reference

## Option D: Hybrid Font Selection System

### Overview
The library supports three ways to select fonts:
1. **Built-in 5x7 font** (default, no external files needed)
2. **setFreeFont()** - Set a GFX font that persists
3. **Indexed fonts** - Select fonts by number (0-5)

---

## Font Array Configuration

### Setup in test Sketch
```cpp
#include "ILI9486_Display.h"
#include "FreeSans9pt7b.h"
#include "Roboto_25.h"

#define FreeSans9 &FreeSans9pt7b
#define Roboto25 &Roboto_25

ILI9486_Display tft(CS, DC, RST, MOSI, SCLK);

void setup() {
  tft.begin();
  
  // Configure font slots
  tft.fontArray[2] = FreeSans9;
  tft.fontArray[4] = Roboto25;
  // Slots 0, 1, 3, 5 remain available
}
```

### Font Array Indices
| Index | Purpose | Example |
|-------|---------|---------|
| 0 | Reserved: "Use current font" | Auto-selected when no parameter given |
| 1 | Reserved: Built-in 5x7 (explicit) | `tft.drawString("text", x, y, 1)` |
| 2 | User-defined | example FreeSans9 |
| 3 | User-defined | (Available) |
| 4 | User-defined | example Roboto25 |
| 5 | User-defined | (Available) |

---

## Method Signatures

### drawString()
```cpp
int16_t drawString(const String &string, int32_t x, int32_t y, uint8_t font = 0)
```
- **Returns**: Width of rendered string in pixels
- **Parameters**:
  - `string`: Text to display (String object)
  - `x, y`: Top-left position
  - `font`: Font index (0-5, default=0)

### drawCentreString()
```cpp
int16_t drawCentreString(const char *string, int32_t x, int32_t y, uint8_t font = 0)
```
- **Returns**: Width of rendered string in pixels
- **Parameters**:
  - `string`: Text to display (C-string)
  - `x`: Center point X coordinate
  - `y`: Top position
  - `font`: Font index (0-5, default=0)

---

## Font Selection Behavior

### Font Parameter Values

| Value | Behavior | Example |
|-------|----------|---------|
| **0** (default) | Use current font set by `setFreeFont()` | `tft.drawString("text", 10, 50)` |
| **1** | Point to built-in 5x7 font | `tft.drawString("text", 10, 50, 1)` |
| **2-5** | Use `fontArray[index]` if set, else fall back to 5x7 | `tft.drawString("text", 10, 50, 2)` |
| **6+** | Out of bounds -> fall back to 5x7 | `tft.drawString("text", 10, 50, 99)` |

### Error Handling
- **Empty slot** (e.g., `fontArray[3] = nullptr`): Falls back to built-in 5x7
- **Out of bounds** (e.g., `font = 99`): Falls back to built-in 5x7
- **No error messages** - silently falls back for robustness

---

## Usage Examples

### Example 1: Default Built-in Font
```cpp
tft.setTextColor(TFT_WHITE);
tft.setTextSize(1);
tft.drawString("Hello World", 10, 50);  // Uses built-in 5x7
```

### Example 2: Using setFreeFont
```cpp
tft.setFreeFont(&DejaVuSerif12pt7b);
tft.setTextSize(1);
tft.drawString("Serif Text", 10, 100);  // Uses DejaVuSerif
```

### Example 3: Indexed Font Selection
```cpp
// Assumes fontArray[2] = FreeSans9, fontArray[4] = Roboto25
tft.setTextSize(1);

tft.drawString("FreeSans", 10, 50, 2);   // Uses FreeSans9
tft.drawString("Roboto", 10, 100, 4);    // Uses Roboto25
```

### Example 4: Scaled Text
```cpp
tft.setTextSize(2);  // 2x scaling

tft.drawString("Big Text", 10, 50, 1);   // Built-in 5x7, scaled 2x
tft.drawString("Big Font", 10, 100, 4);  // Roboto25, scaled 2x
```

### Example 5: Centered Text
```cpp
int16_t centerX = tft.width() / 2;

tft.drawCentreString("Centered", centerX, 50, 1);    // Built-in
tft.drawCentreString("Title", centerX, 100, 2);      // FreeSans9
tft.drawCentreString("BIG", centerX, 150, 4);        // Roboto25
```

### Example 6: Practical Application
```cpp
void drawChannelLabel(int16_t centerX, int16_t y) {
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  
  // Small label
  tft.drawCentreString("CHANNEL A", centerX, y, 2);
  
  // Large status
  tft.setTextColor(TFT_CYAN);
  tft.drawCentreString("TAP", centerX, y + 20, 4);
}
```

### Example 7: Chaining Strings
```cpp
int16_t x = 10;
int16_t y = 50;

tft.setTextColor(TFT_YELLOW);
int16_t w1 = tft.drawString("Temp: ", x, y, 2);
tft.setTextColor(TFT_RED);
int16_t w2 = tft.drawString("25.3°C", x + w1, y, 4);
```

---

## Important Notes

### State Management
- `drawString()` and `drawCentreString()` **restore** cursor position, text size, and font after rendering
- This allows non-destructive text drawing without affecting subsequent operations
- Use `setFreeFont()` to change the "current" font persistently

### Text Scaling
- `setTextSize()` affects **all fonts** including indexed ones
- Call `setTextSize()` before drawing to scale text
- Scaling works with both built-in and GFX fonts

### Color Settings
- Use `setTextColor(fg)` for transparent background
- Use `setTextColor(fg, bg)` for opaque background
- Color settings persist across font changes

### Memory Considerations
- Font header files must be included in your sketch (eg.  dejavuSerif.h)
- Font data stored in PROGMEM (Flash, not RAM)
- Font array holds only 6 pointers (minimal RAM usage)

---

## Font Header File Format

Your font header files should follow Adafruit GFX format:

```cpp
// FreeSans9pt7b.h
const uint8_t FreeSans9pt7bBitmaps[] PROGMEM = { /* bitmap data */ };
const GFXglyph FreeSans9pt7bGlyphs[] PROGMEM = { /* glyph data */ };
const GFXfont FreeSans9pt7b PROGMEM = {
  (uint8_t *)FreeSans9pt7bBitmaps,
  (GFXglyph *)FreeSans9pt7bGlyphs,
  0x20, 0x7E,  // First & last char
  18           // yAdvance
};
```

---

## Troubleshooting

### Problem: Text not appearing
- **Check**: Is `setTextColor()` called? Is color different from background?
- **Check**: Are coordinates on-screen?
- **Check**: Is font array slot populated?

### Problem: Wrong font displayed
- **Check**: Font array indices (did you set `fontArray[2]` correctly?)
- **Check**: Is the font header file included?
- **Check**: Font parameter value (0-5 valid range)

### Problem: Text garbled or corrupt
- **Check**: Font header file matches the pointer definition
- **Check**: PROGMEM keyword present in font definition
- **Check**: Font file generated correctly (use Adafruit font converter)

---

## Quick Reference Table

| What You Want | Code |
|---------------|------|
| Built-in 5x7 (default) | `tft.drawString("text", x, y)` |
| Built-in 5x7 (explicit) | `tft.drawString("text", x, y, 1)` |
| Use setFreeFont font | `tft.setFreeFont(&font); tft.drawString("text", x, y)` |
| FreeSans9 (index 2) | `tft.drawString("text", x, y, 2)` |
| Roboto25 (index 4) | `tft.drawString("text", x, y, 4)` |
| Centered text | `tft.drawCentreString("text", centerX, y, font)` |
| Scaled 2x | `tft.setTextSize(2); tft.drawString("text", x, y, font)` |
| With background | `tft.setTextColor(fg, bg); tft.drawString("text", x, y, font)` |

