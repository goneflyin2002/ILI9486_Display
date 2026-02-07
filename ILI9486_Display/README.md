# ILI9486_Display Library for ESP32-C5

A lightweight, feature-rich display library for the ILI9486 TFT LCD (3.5") on ESP32-C5 microcontrollers. Optimized for performance with DMA support, multiple font handling, and flexible text positioning.

## Features

- **ESP32-C5 Optimized**: First library with full support for ESP32-C5 + ILI9486 combination
- **Software SPI**: Works with any GPIO pins - no hardware SPI constraints
- **DMA Acceleration**: Fast screen fills using DMA buffering
- **Multiple Font Support**: 
  - Built-in 5x7 pixel font
  - Adafruit GFX font compatible
  - Indexed font selection (up to 6 fonts)
- **Text Datum System**: TFT_eSPI compatible positioning (9 anchor points)
- **Clean Rendering**: Proper background clearing eliminates artifacts
- **Full Graphics Primitives**: Lines, rectangles, circles, bitmaps
- **RGB565 Color Support**: 16-bit color with convenient color definitions

## Hardware Requirements

- **MCU**: ESP32-C5 (also compatible with other ESP32 variants)
- **Display**: 3.5" TFT LCD with ILI9486 controller
- **Connection**: SPI (software or hardware)

### Typical Wiring

```
ESP32-C5       ILI9486 Display
GPIO10      -> CS (Chip Select)
GPIO8       -> DC (Data/Command)
GPIO9       -> RST (Reset)
GPIO4       -> MOSI (SDA)
GPIO3       -> SCLK (SCL)
3.3V        -> VCC
GND         -> GND
3.3V        -> LED (Backlight)
```

**Note**: These are the tested pin assignments for ESP32-C5 devboards. The C5 has specific GPIO limitations, so these pins have been verified to work reliably.

## Installation

### Method 1: Arduino Library Manager (Recommended - once published)
1. Open Arduino IDE
2. Go to **Sketch** -> **Include Library** -> **Manage Libraries**
3. Search for "ILI9486_Display"
4. Click **Install**

### Method 2: Manual Installation
1. Download this repository as ZIP
2. In Arduino IDE: **Sketch** -> **Include Library** -> **Add .ZIP Library**
3. Select the downloaded ZIP file

### Method 3: Git Clone
```bash
cd ~/Arduino/libraries/
git clone https://github.com/YourUsername/ILI9486_Display.git
```

## Quick Start

```cpp
#include "ILI9486_Display.h"

// Pin definitions for ESP32-C5 devboard
#define TFT_CS    10
#define TFT_DC    8
#define TFT_RST   9
#define TFT_MOSI  4
#define TFT_SCLK  3

// Create display instance
ILI9486_Display tft(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK);

void setup() {
  tft.begin();                          // Initialize display
  tft.setRotation(0);                   // 0-3 for different orientations
  tft.fillScreen(TFT_BLACK);            // Clear screen
  
  tft.setTextColor(TFT_WHITE);          // Set text color
  tft.setTextDatum(TC_DATUM);           // Top-center alignment
  tft.drawString("Hello ESP32-C5!", 160, 50, 2);  // Draw text
}

void loop() {
  // Your code here
}
```

## Usage Examples

### Basic Graphics

```cpp
// Draw shapes
tft.drawRect(10, 10, 100, 50, TFT_CYAN);
tft.fillRect(20, 70, 80, 30, TFT_RED);
tft.drawCircle(160, 240, 50, TFT_GREEN);
tft.fillCircle(160, 240, 30, TFT_BLUE);
tft.drawLine(0, 0, 319, 479, TFT_YELLOW);
```

### Text with Custom Fonts

```cpp
#include "FreeSans9pt7b.h"
#include "Roboto_25.h"

// Configure font array
tft.fontArray[2] = &FreeSans9pt7b;
tft.fontArray[4] = &Roboto_25;

// Use indexed fonts
tft.setTextColor(TFT_WHITE);
tft.drawString("FreeSans", 10, 50, 2);   // Font index 2
tft.drawString("Roboto", 10, 100, 4);    // Font index 4

// Or use setFreeFont
tft.setFreeFont(&FreeSans9pt7b);
tft.drawString("Custom Font", 10, 150);  // Uses current font
```

### Text Datum Positioning

```cpp
// Top-Center (most common for titles)
tft.setTextDatum(TC_DATUM);
tft.drawString("TITLE", 160, 20, 4);

// Middle-Center (centered message)
tft.setTextDatum(MC_DATUM);
tft.drawString("Centered", 160, 240, 2);

// Top-Left (default, for labels)
tft.setTextDatum(TL_DATUM);
tft.drawString("Label:", 10, 100, 2);
```

### Drawing with Background

```cpp
// Transparent background
tft.setTextColor(TFT_ORANGE);
tft.drawString("Transparent", 10, 50, 2);

// Opaque background (clears old text)
tft.setTextColor(TFT_ORANGE, TFT_BLACK);
tft.drawString("Opaque", 10, 100, 2);
```

## Available Colors

```cpp
TFT_BLACK       TFT_NAVY        TFT_DARKGREEN   TFT_DARKCYAN
TFT_MAROON      TFT_PURPLE      TFT_OLIVE       TFT_LIGHTGREY
TFT_DARKGREY    TFT_BLUE        TFT_GREEN       TFT_CYAN
TFT_RED         TFT_MAGENTA     TFT_YELLOW      TFT_WHITE
TFT_ORANGE      TFT_GREENYELLOW
```

Custom colors:
```cpp
uint16_t myColor = tft.color565(255, 128, 64);  // RGB to RGB565
```

## Text Datum Reference

```
TL_DATUM (0) - Top Left         TC_DATUM (1) - Top Center      TR_DATUM (2) - Top Right
ML_DATUM (3) - Middle Left      MC_DATUM (4) - Middle Center   MR_DATUM (5) - Middle Right
BL_DATUM (6) - Bottom Left      BC_DATUM (7) - Bottom Center   BR_DATUM (8) - Bottom Right
```

## API Reference

### Display Control
- `begin(uint32_t freq = 20000000)` - Initialize display (optional SPI frequency)
- `setRotation(uint8_t r)` - Set screen rotation (0-3)
- `fillScreen(uint16_t color)` - Fill entire screen

### Graphics Primitives
- `drawPixel(x, y, color)` - Draw single pixel
- `drawLine(x0, y0, x1, y1, color)` - Draw line
- `drawRect(x, y, w, h, color)` - Draw rectangle outline
- `fillRect(x, y, w, h, color)` - Draw filled rectangle
- `drawCircle(x0, y0, r, color)` - Draw circle outline
- `fillCircle(x0, y0, r, color)` - Draw filled circle
- `drawBitmap(x, y, bitmap, w, h, color)` - Draw 1-bit bitmap

### Text Functions
- `setTextColor(color)` - Set text color (transparent background)
- `setTextColor(fg, bg)` - Set text color with background
- `setTextSize(size)` - Set text scaling (1-n)
- `setTextDatum(datum)` - Set text anchor point (TL_DATUM, TC_DATUM, etc.)
- `setFreeFont(font)` - Set GFX font
- `drawString(string, x, y, font=0)` - Draw text at position
- `drawCentreString(string, x, y, font=0)` - Draw centered text
- `setCursor(x, y)` - Set cursor position
- `print(text)` - Print at cursor position
- `println(text)` - Print with newline

### Utility
- `width()` - Get screen width
- `height()` - Get screen height
- `color565(r, g, b)` - Convert RGB to RGB565

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This library is released under the MIT License. See LICENSE file for details.

## Acknowledgments

- Inspired by Bodmer's TFT_eSPI library
- Compatible with Adafruit GFX font format
- Built specifically for the ESP32-C5 community

## Support

- **Issues**: Report bugs or request features via [GitHub Issues](https://github.com/Don_M/ILI9486_Display/issues)
- **Discussions**: Ask questions in [GitHub Discussions](https://github.com/Don_M/ILI9486_Display/discussions)

## Why This Library?

Existing solutions for ILI9486 displays don't support the ESP32-C5 properly. This library was built from the ground up to provide:
-  Full ESP32-C5 compatibility
-  Reliable software SPI implementation
-  TFT_eSPI-like API for easy migration
-  Performance optimization with DMA
-  Clean text rendering without artifacts
-  Flexible font management

## Performance

- Screen fill (320x480): ~45ms
- Text rendering: Optimized with horizontal run-length encoding
- DMA transfers: 1024-byte buffer for efficient pixel writes

## Roadmap

- [ ] Hardware SPI support
- [ ] Touch screen support
- [ ] Additional graphics primitives (triangles, arcs)
- [ ] Image loading (JPEG, PNG)
- [ ] Sprite support
- [ ] Anti-aliased fonts

---

Made for the ESP32-C5 community

