# Text Datum System - Quick Reference

## What Changed From Previous Version

### BEFORE (without datum):
- Y coordinate referenced the baseline for GFX fonts
- Text appeared higher than expected
- Had to manually calculate offsets for positioning

### AFTER (with datum):
- Y coordinate references the top of text by default (TL_DATUM)
- Text appears exactly where you specify
- Supports 9 different positioning modes

---

## Datum Constants

```
        Left(0)    Center(1)   Right(2)
        
Top(0)   TL_DATUM   TC_DATUM   TR_DATUM
         
Mid(1)   ML_DATUM   MC_DATUM   MR_DATUM
         
Bot(2)   BL_DATUM   BC_DATUM   BR_DATUM
```

### Visual Representation

```
TL -------- TC -------- TR
|          |          |
|     Text Box        |
|          |          |
ML -------- MC -------- MR
|          |          |
|          |          |
|          |          |
BL -------- BC -------- BR (baseline)
```

---

## Usage

### Setting the Datum
```cpp
tft.setTextDatum(TC_DATUM);  // Set once, persists for all subsequent drawString calls
```

### Common Patterns

#### 1. Centered Title (TC_DATUM)
```cpp
tft.setTextDatum(TC_DATUM);
tft.drawString("MAIN MENU", 160, 20, 4);  // Centered at top
```

#### 2. Left-Aligned Labels (TL_DATUM) - DEFAULT
```cpp
tft.setTextDatum(TL_DATUM);
tft.drawString("Status:", 10, 50, 2);
tft.drawString("Ready", 10, 80, 2);
```

#### 3. Fully Centered Text (MC_DATUM)
```cpp
tft.setTextDatum(MC_DATUM);
tft.drawString("CENTERED", 160, 240, 4);  // Dead center of screen
```

#### 4. Right-Aligned Numbers (TR_DATUM)
```cpp
tft.setTextDatum(TR_DATUM);
tft.drawString("$99.99", 300, 100, 2);  // Right edge at x=300
```

---

## Datum Breakdown

### TL_DATUM (0) - Top Left [DEFAULT]
- X: Left edge of text
- Y: Top edge of text
- Use: General UI, labels, left-aligned text
```cpp
tft.setTextDatum(TL_DATUM);
tft.drawString("Hello", 10, 50, 2);  // Starts at (10,50)
```

### TC_DATUM (1) - Top Center [MOST COMMON]
- X: Horizontal center of text
- Y: Top edge of text
- Use: Titles, centered headers, channel labels
```cpp
tft.setTextDatum(TC_DATUM);
tft.drawString("TITLE", 160, 20, 4);  // Centered horizontally
```

### TR_DATUM (2) - Top Right
- X: Right edge of text
- Y: Top edge of text
- Use: Right-aligned text, prices, numbers
```cpp
tft.setTextDatum(TR_DATUM);
tft.drawString("100%", 310, 50, 2);  // Right edge at x=310
```

### ML_DATUM (3) - Middle Left
- X: Left edge of text
- Y: Vertical center of text
- Use: Vertically centered labels
```cpp
tft.setTextDatum(ML_DATUM);
tft.drawString("Label", 10, 240, 2);  // Vertically centered at y=240
```

### MC_DATUM (4) - Middle Center [FULLY CENTERED]
- X: Horizontal center of text
- Y: Vertical center of text
- Use: Centered messages, splash screens
```cpp
tft.setTextDatum(MC_DATUM);
tft.drawString("LOADING", 160, 240, 4);  // Dead center
```

### MR_DATUM (5) - Middle Right
- X: Right edge of text
- Y: Vertical center of text
- Use: Right-aligned, vertically centered
```cpp
tft.setTextDatum(MR_DATUM);
tft.drawString("End", 310, 240, 2);
```

### BL_DATUM (6) - Bottom Left (Baseline)
- X: Left edge of text
- Y: Baseline (bottom of most characters)
- Use: Traditional typography, baseline-aligned text
```cpp
tft.setTextDatum(BL_DATUM);
tft.drawString("Text", 10, 100, 2);  // Baseline at y=100
```

### BC_DATUM (7) - Bottom Center
- X: Horizontal center of text
- Y: Baseline
- Use: Centered text aligned to baseline
```cpp
tft.setTextDatum(BC_DATUM);
tft.drawString("Bottom", 160, 460, 2);  // Centered, baseline at y=460
```

### BR_DATUM (8) - Bottom Right
- X: Right edge of text
- Y: Baseline
- Use: Right-aligned baseline text
```cpp
tft.setTextDatum(BR_DATUM);
tft.drawString("End", 310, 100, 2);
```

---

## Practical Examples

### Example 1: Channel Display (Your Use Case)
```cpp
void drawChannelInfo() {
  tft.setTextDatum(TC_DATUM);  // Set once at top of function
  tft.setTextColor(TFT_WHITE);
  
  int16_t centerX = 80;
  int16_t y = 100;
  
  // All centered horizontally on centerX
  tft.drawString("CHANNEL A", centerX, y, 2);
  tft.setTextColor(TFT_CYAN);
  tft.drawString("TAP", centerX, y + 20, 4);
  tft.setTextColor(TFT_YELLOW);
  tft.drawString("4.5%", centerX, y + 60, 2);
}
```

### Example 2: Dashboard Layout
```cpp
void drawDashboard() {
  // Title at top center
  tft.setTextDatum(TC_DATUM);
  tft.drawString("BREWERY CONTROL", 160, 10, 4);
  
  // Labels on left
  tft.setTextDatum(TL_DATUM);
  tft.drawString("Temperature:", 10, 100, 2);
  tft.drawString("Pressure:", 10, 130, 2);
  
  // Values on right
  tft.setTextDatum(TR_DATUM);
  tft.drawString("68F", 310, 100, 2);
  tft.drawString("15 PSI", 310, 130, 2);
}
```

### Example 3: Centered Message
```cpp
void showMessage(const char* msg) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_WHITE);
  tft.drawString(msg, 160, 240, 4);
}
```

---

## Important Notes

### Datum Persistence
- Datum setting persists across multiple drawString() calls
- Set it once per function/section
- Default is TL_DATUM (Top-Left)

### drawCentreString() Behavior
- drawCentreString() ignores the datum setting
- Always centers horizontally on X coordinate
- Useful when you need one-off centered text

### Built-in vs GFX Fonts
- Datum works with both built-in 5x7 and GFX fonts
- Positioning is consistent across font types
- Built-in font assumes all pixels above baseline (simplified)

### Return Value
- drawString() still returns the width in pixels
- Useful for chaining text or calculating positions

---

## Migration from Old Code

### OLD CODE (baseline positioning):
```cpp
// Text appeared too high
tft.drawString("Hello", 100, 50, 2);
```

### NEW CODE (with datum):
```cpp
// Option 1: Use default TL_DATUM (top positioning)
tft.drawString("Hello", 100, 50, 2);  // Works correctly now!

// Option 2: Be explicit
tft.setTextDatum(TL_DATUM);
tft.drawString("Hello", 100, 50, 2);

// Option 3: Center it
tft.setTextDatum(TC_DATUM);
tft.drawString("Hello", 160, 50, 2);  // Centered!
```

---

## Debugging Tips

### Draw Reference Lines
```cpp
// Show where your reference point is
int16_t x = 160, y = 100;

tft.drawFastHLine(x - 20, y, 40, TFT_RED);  // Horizontal line
tft.drawFastVLine(x, y - 20, 40, TFT_RED);  // Vertical line

tft.setTextDatum(TC_DATUM);
tft.drawString("Text", x, y, 2);
```

### Test All Datums
```cpp
for (int d = 0; d < 9; d++) {
  tft.setTextDatum(d);
  tft.drawString("TEST", 100, 100, 2);
  delay(1000);
  tft.fillScreen(TFT_BLACK);
}
```

---

## Summary Table

| Datum | Name | X Position | Y Position | Common Use |
|-------|------|------------|------------|------------|
| 0 | TL_DATUM | Left | Top | [DEFAULT] Labels, UI |
| 1 | TC_DATUM | Center | Top | [MOST USED] Titles, headers |
| 2 | TR_DATUM | Right | Top | Right-aligned text |
| 3 | ML_DATUM | Left | Middle | Vertical center |
| 4 | MC_DATUM | Center | Middle | [CENTERED] Messages |
| 5 | MR_DATUM | Right | Middle | - |
| 6 | BL_DATUM | Left | Baseline | Typography |
| 7 | BC_DATUM | Center | Baseline | - |
| 8 | BR_DATUM | Right | Baseline | - |

Most Used: TL_DATUM (0), TC_DATUM (1), MC_DATUM (4)
