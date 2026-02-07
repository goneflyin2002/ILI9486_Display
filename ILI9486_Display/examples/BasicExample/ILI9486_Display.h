#ifndef ILI9486_DISPLAY_H
#define ILI9486_DISPLAY_H

#include <Arduino.h>
#include <SPI.h>

// Helper macro for swapping values
#ifndef swap
#define swap(a, b) { typeof(a) t = a; a = b; b = t; }
#endif

// SPI host definition for ESP32-C5
#ifndef SPI2_HOST
#define SPI2_HOST 1
#endif

// Simple 5x7 font (ASCII 32-126)
static const uint8_t font5x7[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, // (space)
  0x00, 0x00, 0x5F, 0x00, 0x00, // !
  0x00, 0x07, 0x00, 0x07, 0x00, // "
  0x14, 0x7F, 0x14, 0x7F, 0x14, // #
  0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
  0x23, 0x13, 0x08, 0x64, 0x62, // %
  0x36, 0x49, 0x55, 0x22, 0x50, // &
  0x00, 0x05, 0x03, 0x00, 0x00, // '
  0x00, 0x1C, 0x22, 0x41, 0x00, // (
  0x00, 0x41, 0x22, 0x1C, 0x00, // )
  0x08, 0x2A, 0x1C, 0x2A, 0x08, // *
  0x08, 0x08, 0x3E, 0x08, 0x08, // +
  0x00, 0x50, 0x30, 0x00, 0x00, // ,
  0x08, 0x08, 0x08, 0x08, 0x08, // -
  0x00, 0x60, 0x60, 0x00, 0x00, // .
  0x20, 0x10, 0x08, 0x04, 0x02, // /
  0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
  0x00, 0x42, 0x7F, 0x40, 0x00, // 1
  0x42, 0x61, 0x51, 0x49, 0x46, // 2
  0x21, 0x41, 0x45, 0x4B, 0x31, // 3
  0x18, 0x14, 0x12, 0x7F, 0x10, // 4
  0x27, 0x45, 0x45, 0x45, 0x39, // 5
  0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
  0x01, 0x71, 0x09, 0x05, 0x03, // 7
  0x36, 0x49, 0x49, 0x49, 0x36, // 8
  0x06, 0x49, 0x49, 0x29, 0x1E, // 9
  0x00, 0x36, 0x36, 0x00, 0x00, // :
  0x00, 0x56, 0x36, 0x00, 0x00, // ;
  0x00, 0x08, 0x14, 0x22, 0x41, // <
  0x14, 0x14, 0x14, 0x14, 0x14, // =
  0x41, 0x22, 0x14, 0x08, 0x00, // >
  0x02, 0x01, 0x51, 0x09, 0x06, // ?
  0x32, 0x49, 0x79, 0x41, 0x3E, // @
  0x7E, 0x11, 0x11, 0x11, 0x7E, // A
  0x7F, 0x49, 0x49, 0x49, 0x36, // B
  0x3E, 0x41, 0x41, 0x41, 0x22, // C
  0x7F, 0x41, 0x41, 0x22, 0x1C, // D
  0x7F, 0x49, 0x49, 0x49, 0x41, // E
  0x7F, 0x09, 0x09, 0x01, 0x01, // F
  0x3E, 0x41, 0x41, 0x51, 0x32, // G
  0x7F, 0x08, 0x08, 0x08, 0x7F, // H
  0x00, 0x41, 0x7F, 0x41, 0x00, // I
  0x20, 0x40, 0x41, 0x3F, 0x01, // J
  0x7F, 0x08, 0x14, 0x22, 0x41, // K
  0x7F, 0x40, 0x40, 0x40, 0x40, // L
  0x7F, 0x02, 0x04, 0x02, 0x7F, // M
  0x7F, 0x04, 0x08, 0x10, 0x7F, // N
  0x3E, 0x41, 0x41, 0x41, 0x3E, // O
  0x7F, 0x09, 0x09, 0x09, 0x06, // P
  0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
  0x7F, 0x09, 0x19, 0x29, 0x46, // R
  0x46, 0x49, 0x49, 0x49, 0x31, // S
  0x01, 0x01, 0x7F, 0x01, 0x01, // T
  0x3F, 0x40, 0x40, 0x40, 0x3F, // U
  0x1F, 0x20, 0x40, 0x20, 0x1F, // V
  0x7F, 0x20, 0x18, 0x20, 0x7F, // W
  0x63, 0x14, 0x08, 0x14, 0x63, // X
  0x03, 0x04, 0x78, 0x04, 0x03, // Y
  0x61, 0x51, 0x49, 0x45, 0x43, // Z
  0x00, 0x00, 0x7F, 0x41, 0x41, // [
  0x02, 0x04, 0x08, 0x10, 0x20, // backslash
  0x41, 0x41, 0x7F, 0x00, 0x00, // ]
  0x04, 0x02, 0x01, 0x02, 0x04, // ^
  0x40, 0x40, 0x40, 0x40, 0x40, // _
  0x00, 0x01, 0x02, 0x04, 0x00, // `
  0x20, 0x54, 0x54, 0x54, 0x78, // a
  0x7F, 0x48, 0x44, 0x44, 0x38, // b
  0x38, 0x44, 0x44, 0x44, 0x20, // c
  0x38, 0x44, 0x44, 0x48, 0x7F, // d
  0x38, 0x54, 0x54, 0x54, 0x18, // e
  0x08, 0x7E, 0x09, 0x01, 0x02, // f
  0x0C, 0x52, 0x52, 0x52, 0x3E, // g
  0x7F, 0x08, 0x04, 0x04, 0x78, // h
  0x00, 0x44, 0x7D, 0x40, 0x00, // i
  0x20, 0x40, 0x44, 0x3D, 0x00, // j
  0x00, 0x7F, 0x10, 0x28, 0x44, // k
  0x00, 0x41, 0x7F, 0x40, 0x00, // l
  0x7C, 0x04, 0x18, 0x04, 0x78, // m
  0x7C, 0x08, 0x04, 0x04, 0x78, // n
  0x38, 0x44, 0x44, 0x44, 0x38, // o
  0x7C, 0x14, 0x14, 0x14, 0x08, // p
  0x08, 0x14, 0x14, 0x18, 0x7C, // q
  0x7C, 0x08, 0x04, 0x04, 0x08, // r
  0x48, 0x54, 0x54, 0x54, 0x20, // s
  0x04, 0x3F, 0x44, 0x40, 0x20, // t
  0x3C, 0x40, 0x40, 0x20, 0x7C, // u
  0x1C, 0x20, 0x40, 0x20, 0x1C, // v
  0x3C, 0x40, 0x30, 0x40, 0x3C, // w
  0x44, 0x28, 0x10, 0x28, 0x44, // x
  0x0C, 0x50, 0x50, 0x50, 0x3C, // y
  0x44, 0x64, 0x54, 0x4C, 0x44, // z
};

// Color definitions (RGB565 format)
#define TFT_BLACK       0x0000
#define TFT_WHITE       0xFFFF
#define TFT_RED         0xF800
#define TFT_GREEN       0x07E0
#define TFT_BLUE        0x001F
#define TFT_CYAN        0x07FF
#define TFT_MAGENTA     0xF81F
#define TFT_YELLOW      0xFFE0
#define TFT_ORANGE      0xFD20
#define TFT_GREENYELLOW 0xAFE5
#define TFT_DARKGREY    0x7BEF
#define TFT_LIGHTGREY   0xC618

// Text datum definitions (Bodmer TFT_eSPI compatible)
#define TL_DATUM 0  // Top Left
#define TC_DATUM 1  // Top Center
#define TR_DATUM 2  // Top Right
#define ML_DATUM 3  // Middle Left
#define MC_DATUM 4  // Middle Center
#define MR_DATUM 5  // Middle Right
#define BL_DATUM 6  // Bottom Left (baseline)
#define BC_DATUM 7  // Bottom Center
#define BR_DATUM 8  // Bottom Right

// GFX font structures (Adafruit GFX format)
typedef struct {
  uint16_t bitmapOffset;     // Pointer into GFXfont->bitmap
  uint8_t  width, height;    // Bitmap dimensions in pixels
  uint8_t  xAdvance;         // Distance to advance cursor (x axis)
  int8_t   xOffset, yOffset; // Dist from cursor pos to UL corner
} GFXglyph;

typedef struct {
  uint8_t  *bitmap;      // Glyph bitmaps, concatenated
  GFXglyph *glyph;       // Glyph array
  uint8_t   first, last; // ASCII extents
  uint8_t   yAdvance;    // Newline distance (y axis)
} GFXfont;

class ILI9486_Display {
private:
  int8_t _cs, _dc, _rst;
  int8_t _mosi, _sclk;
  uint16_t _width, _height;
  uint8_t _rotation;
  
  void writeCommand(uint8_t cmd);
  void writeData(uint8_t data);
  void writeData16(uint16_t data);
  void writeData32(uint32_t data);
  void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
  
public:
  ILI9486_Display(int8_t cs, int8_t dc, int8_t rst, int8_t mosi, int8_t sclk);
  
  void begin(uint32_t freq = 27000000);  // Default.  Try decreasing speed if problems appear.
  void setRotation(uint8_t rotation);
  void fillScreen(uint16_t color);
  void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
  void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
  void drawPixel(uint16_t x, uint16_t y, uint16_t color);
  void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
  void drawFastHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color);
  void drawFastVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color);
  void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
  void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
  
  // Bitmap drawing
  void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
  void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);
  
  // Font rendering
  void setFreeFont(const GFXfont *f = NULL);
  void setCursor(uint16_t x, uint16_t y);
  void setTextColor(uint16_t color);
  void setTextColor(uint16_t fg, uint16_t bg);
  void setTextSize(uint8_t s);
  void setTextDatum(uint8_t datum);
  void print(const char *str);
  void print(int num);
  void print(unsigned long num);
  void print(float num, int decimals = 2);
  void println(const char *str);
  void println(int num);
  void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
  void drawGFXChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
  
  // String drawing with positioning
  int16_t drawString(const String &string, int32_t x, int32_t y, uint8_t font = 0);
  int16_t drawCentreString(const char *string, int32_t x, int32_t y, uint8_t font = 0);
  
  // Color conversion
  uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
  }
  
  // DMA optimized fills
  void fillRectDMA(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
  
  // WiFi icon
  void drawWiFiIcon(uint16_t x, uint16_t y, uint8_t strength, uint16_t color);
  
  uint16_t width() { return _width; }
  uint16_t height() { return _height; }
  
  // Font array for indexed font selection (public for user configuration)
  const GFXfont* fontArray[6];  // Indices: 0=current, 1=builtin, 2-5=user fonts
  
private:
  const GFXfont *gfxFont;
  uint16_t cursor_x, cursor_y;
  uint16_t textcolor, textbgcolor;
  uint8_t textsize;
  uint8_t textdatum;
  bool use_bg;
  
  // DMA buffer for faster transfers  
  static const size_t DMA_BUFFER_SIZE = 1024; // 1024 bytes = 512 pixels in 16-bit mode
  uint8_t dmaBuffer[DMA_BUFFER_SIZE];
  
  void writePixels(uint16_t *colors, uint32_t len);
};

// Constructor
ILI9486_Display::ILI9486_Display(int8_t cs, int8_t dc, int8_t rst, int8_t mosi, int8_t sclk) {
  _cs = cs;
  _dc = dc;
  _rst = rst;
  _mosi = mosi;
  _sclk = sclk;
  _width = 320;
  _height = 480;
  _rotation = 0;
  gfxFont = nullptr;
  cursor_x = 0;
  cursor_y = 0;
  textcolor = TFT_WHITE;
  textbgcolor = TFT_BLACK;
  textsize = 1;
  textdatum = TL_DATUM;  // Default to Top-Left
  use_bg = false;
  
  // Initialize font array
  for (int i = 0; i < 6; i++) {
    fontArray[i] = nullptr;
  }
}

// Initialize display
void ILI9486_Display::begin(uint32_t freq) {
  pinMode(_cs, OUTPUT);
  pinMode(_dc, OUTPUT);
  pinMode(_rst, OUTPUT);
  
  digitalWrite(_cs, HIGH);
  digitalWrite(_dc, HIGH);
  
  // Initialize SPI using the standard SPI object (not SPIClass)
  SPI.begin(_sclk, -1, _mosi, -1);
  SPI.setFrequency(freq);
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  
  // Hardware reset
  digitalWrite(_rst, LOW);
  delay(20);
  digitalWrite(_rst, HIGH);
  delay(150);
  
  // Minimal ILI9486 initialization - matches working sketch
  writeCommand(0x01); // Software reset
  delay(120);
  
  writeCommand(0x11); // Sleep out
  delay(120);
  
  writeCommand(0x3A); // Pixel format
  writeData(0x55);    // 16-bit color
  
  writeCommand(0x36); // Memory access control
  writeData(0x08);    // MX=0, MY=0, MV=0, ML=0, BGR=0 (RGB mode, not BGR)
  
  writeCommand(0x29); // Display on
  delay(50);
  
  fillScreen(TFT_BLACK);
}

// Low-level write functions
void ILI9486_Display::writeCommand(uint8_t cmd) {
  digitalWrite(_dc, LOW);
  digitalWrite(_cs, LOW);
  SPI.transfer(cmd);
  digitalWrite(_cs, HIGH);
}

void ILI9486_Display::writeData(uint8_t data) {
  digitalWrite(_dc, HIGH);
  digitalWrite(_cs, LOW);
  SPI.transfer(data);
  digitalWrite(_cs, HIGH);
}

void ILI9486_Display::writeData16(uint16_t data) {
  digitalWrite(_dc, HIGH);
  digitalWrite(_cs, LOW);
  SPI.transfer(data >> 8);
  SPI.transfer(data & 0xFF);
  digitalWrite(_cs, HIGH);
}

void ILI9486_Display::writeData32(uint32_t data) {
  digitalWrite(_dc, HIGH);
  digitalWrite(_cs, LOW);
  SPI.transfer((data >> 24) & 0xFF);
  SPI.transfer((data >> 16) & 0xFF);
  SPI.transfer((data >> 8) & 0xFF);
  SPI.transfer(data & 0xFF);
  digitalWrite(_cs, HIGH);
}

// Set drawing window
void ILI9486_Display::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
  writeCommand(0x2A); // Column address
  writeData(x0 >> 8);
  writeData(x0 & 0xFF);
  writeData(x1 >> 8);
  writeData(x1 & 0xFF);
  
  writeCommand(0x2B); // Row address
  writeData(y0 >> 8);
  writeData(y0 & 0xFF);
  writeData(y1 >> 8);
  writeData(y1 & 0xFF);
  
  writeCommand(0x2C); // Memory write
}

// Set rotation
void ILI9486_Display::setRotation(uint8_t rotation) {
  _rotation = rotation % 4;
  writeCommand(0x36);
  
  switch (_rotation) {
    case 0:
      writeData(0x48);
      _width = 320;
      _height = 480;
      break;
    case 1:
      writeData(0x28);
      _width = 480;
      _height = 320;
      break;
    case 2:
      writeData(0x88);
      _width = 320;
      _height = 480;
      break;
    case 3:
      writeData(0xE8);
      _width = 480;
      _height = 320;
      break;
  }
}

// Fill screen
void ILI9486_Display::fillScreen(uint16_t color) {
  fillRect(0, 0, _width, _height, color);
}

// Fill rectangle - Full DMA optimization at 27MHz (sweet spot for this display)
void ILI9486_Display::fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
  if (x >= _width || y >= _height) return;
  if (x + w > _width) w = _width - x;
  if (y + h > _height) h = _height - y;
  
  setAddrWindow(x, y, x + w - 1, y + h - 1);
  
  // Prepare color bytes
  uint8_t hi = color >> 8;
  uint8_t lo = color & 0xFF;
  
  // Fill DMA buffer with repeated color
  for (uint16_t i = 0; i < DMA_BUFFER_SIZE; i += 2) {
    dmaBuffer[i] = hi;
    dmaBuffer[i + 1] = lo;
  }
  
  digitalWrite(_dc, HIGH);
  digitalWrite(_cs, LOW);
  
  uint32_t totalBytes = (uint32_t)w * h * 2;
  
  // Write full buffers with DMA
  while (totalBytes >= DMA_BUFFER_SIZE) {
    SPI.writeBytes(dmaBuffer, DMA_BUFFER_SIZE);
    totalBytes -= DMA_BUFFER_SIZE;
  }
  
  // Write remaining bytes
  if (totalBytes > 0) {
    SPI.writeBytes(dmaBuffer, totalBytes);
  }
  
  digitalWrite(_cs, HIGH);
}

// DMA optimized fill (alias for fillRect with better performance)
void ILI9486_Display::fillRectDMA(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
  fillRect(x, y, w, h, color);
}

// Helper function for writing pixel arrays
void ILI9486_Display::writePixels(uint16_t *colors, uint32_t len) {
  digitalWrite(_dc, HIGH);
  digitalWrite(_cs, LOW);
  
  // Convert to bytes and send
  for (uint32_t i = 0; i < len; i++) {
    SPI.transfer(colors[i] >> 8);
    SPI.transfer(colors[i] & 0xFF);
  }
  
  digitalWrite(_cs, HIGH);
}

// Draw rectangle outline
void ILI9486_Display::drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
  drawLine(x, y, x + w - 1, y, color);
  drawLine(x + w - 1, y, x + w - 1, y + h - 1, color);
  drawLine(x + w - 1, y + h - 1, x, y + h - 1, color);
  drawLine(x, y + h - 1, x, y, color);
}

// Draw single pixel
void ILI9486_Display::drawPixel(uint16_t x, uint16_t y, uint16_t color) {
  if (x >= _width || y >= _height) return;
  setAddrWindow(x, y, x, y);
  writeData16(color);
}

// Fast horizontal line
void ILI9486_Display::drawFastHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color) {
  if (x >= _width || y >= _height) return;
  if (x + w > _width) w = _width - x;
  fillRect(x, y, w, 1, color);
}

// Fast vertical line
void ILI9486_Display::drawFastVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color) {
  if (x >= _width || y >= _height) return;
  if (y + h > _height) h = _height - y;
  fillRect(x, y, 1, h, color);
}

// Draw line
void ILI9486_Display::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }
  
  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }
  
  int16_t dx = x1 - x0;
  int16_t dy = abs(y1 - y0);
  int16_t err = dx / 2;
  int16_t ystep = (y0 < y1) ? 1 : -1;
  
  for (; x0 <= x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

// Draw circle
void ILI9486_Display::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;
  
  drawPixel(x0, y0 + r, color);
  drawPixel(x0, y0 - r, color);
  drawPixel(x0 + r, y0, color);
  drawPixel(x0 - r, y0, color);
  
  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    
    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}

// Fill circle - OPTIMIZED
void ILI9486_Display::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  drawFastVLine(x0, y0 - r, 2 * r + 1, color);
  
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;
  
  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    
    drawFastVLine(x0 + x, y0 - y, 2 * y + 1, color);
    drawFastVLine(x0 - x, y0 - y, 2 * y + 1, color);
    drawFastVLine(x0 + y, y0 - x, 2 * x + 1, color);
    drawFastVLine(x0 - y, y0 - x, 2 * x + 1, color);
  }
}

// Font functions
void ILI9486_Display::setFreeFont(const GFXfont *f) {
  gfxFont = (GFXfont *)f;
}

void ILI9486_Display::setTextSize(uint8_t s) {
  textsize = (s > 0) ? s : 1;
}

void ILI9486_Display::setTextDatum(uint8_t datum) {
  textdatum = datum;
}

void ILI9486_Display::setCursor(uint16_t x, uint16_t y) {
  cursor_x = x;
  cursor_y = y;
}

void ILI9486_Display::setTextColor(uint16_t color) {
  textcolor = color;
  use_bg = false;
}

void ILI9486_Display::setTextColor(uint16_t fg, uint16_t bg) {
  textcolor = fg;
  textbgcolor = bg;
  use_bg = true;
}

// Draw character using GFX font - HIGHLY OPTIMIZED with horizontal runs and smooth edges
void ILI9486_Display::drawGFXChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
  if (!gfxFont) return;
  
  c -= gfxFont->first;
  if (c > (gfxFont->last - gfxFont->first)) return;
  
  GFXglyph *glyph = &(((GFXglyph *)gfxFont->glyph)[c]);
  uint8_t *bitmap = gfxFont->bitmap;
  
  uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
  uint8_t w = pgm_read_byte(&glyph->width);
  uint8_t h = pgm_read_byte(&glyph->height);
  int8_t xo = pgm_read_byte(&glyph->xOffset);
  int8_t yo = pgm_read_byte(&glyph->yOffset);
  
  if (size == 1) {
    // Clear background if needed
    if (use_bg) {
      fillRect(x + xo, y + yo, w, h, bg);
    }
    
    // Draw using horizontal runs for speed
    uint8_t bits = 0, bit = 0;
    uint16_t bitOffset = bo;
    
    for (uint8_t yy = 0; yy < h; yy++) {
      int16_t runStart = -1;
      
      for (uint8_t xx = 0; xx < w; xx++) {
        if (!(bit++ & 7)) {
          bits = pgm_read_byte(&bitmap[bitOffset++]);
        }
        
        if (bits & 0x80) {
          // Pixel is ON
          if (runStart < 0) {
            runStart = xx; // Start new run
          }
        } else {
          // Pixel is OFF
          if (runStart >= 0) {
            // End of run - draw it with fillRect for perfect edges
            fillRect(x + xo + runStart, y + yo + yy, xx - runStart, 1, color);
            runStart = -1;
          }
        }
        bits <<= 1;
      }
      
      // Draw any remaining run at end of row
      if (runStart >= 0) {
        fillRect(x + xo + runStart, y + yo + yy, w - runStart, 1, color);
      }
    }
  } else {
    // Scaled characters - use original method
    uint8_t bits = 0, bit = 0;
    uint16_t bitOffset = bo;
    
    for (uint8_t yy = 0; yy < h; yy++) {
      for (uint8_t xx = 0; xx < w; xx++) {
        if (!(bit++ & 7)) {
          bits = pgm_read_byte(&bitmap[bitOffset++]);
        }
        if (bits & 0x80) {
          fillRect(x + (xo + xx) * size, y + (yo + yy) * size, size, size, color);
        } else if (use_bg) {
          fillRect(x + (xo + xx) * size, y + (yo + yy) * size, size, size, bg);
        }
        bits <<= 1;
      }
    }
  }
}

// Draw character (simple 5x7 font or GFX font)
void ILI9486_Display::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
  if (gfxFont) {
    drawGFXChar(x, y, c, color, bg, size);
    return;
  }
  
  // Built-in 5x7 font
  if (c < 32 || c > 122) c = 32; // Limit to printable ASCII
  
  const uint8_t *glyph = &font5x7[(c - 32) * 5];
  
  for (int8_t i = 0; i < 5; i++) {
    uint8_t line = pgm_read_byte(&glyph[i]);
    for (int8_t j = 0; j < 8; j++) {
      if (line & 0x1) {
        if (size == 1) drawPixel(x + i, y + j, color);
        else fillRect(x + i * size, y + j * size, size, size, color);
      } else if (use_bg) {
        if (size == 1) drawPixel(x + i, y + j, bg);
        else fillRect(x + i * size, y + j * size, size, size, bg);
      }
      line >>= 1;
    }
  }
}

void ILI9486_Display::print(const char *str) {
  if (gfxFont) {
    // GFX font
    while (*str) {
      char c = *str++;
      if (c == '\n') {
        cursor_x = 0;
        cursor_y += gfxFont->yAdvance * textsize;
        continue;
      }
      if (c < gfxFont->first || c > gfxFont->last) continue;
      
      uint8_t glyph_index = c - gfxFont->first;
      GFXglyph *glyph = &(((GFXglyph *)gfxFont->glyph)[glyph_index]);
      drawGFXChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
      cursor_x += pgm_read_byte(&glyph->xAdvance) * textsize;
    }
  } else {
    // Built-in font
    while (*str) {
      if (*str == '\n') {
        cursor_x = 0;
        cursor_y += 8 * textsize;
        str++;
        continue;
      }
      drawChar(cursor_x, cursor_y, *str++, textcolor, textbgcolor, textsize);
      cursor_x += 6 * textsize;
    }
  }
}

void ILI9486_Display::print(int num) {
  char buf[12];
  itoa(num, buf, 10);
  print(buf);
}

void ILI9486_Display::print(unsigned long num) {
  char buf[12];
  ultoa(num, buf, 10);
  print(buf);
}

void ILI9486_Display::print(float num, int decimals) {
  char buf[20];
  dtostrf(num, 0, decimals, buf);
  print(buf);
}

void ILI9486_Display::println(const char *str) {
  print(str);
  cursor_x = 0;
  if (gfxFont) {
    cursor_y += gfxFont->yAdvance * textsize;
  } else {
    cursor_y += 8 * textsize;
  }
}

void ILI9486_Display::println(int num) {
  print(num);
  cursor_x = 0;
  if (gfxFont) {
    cursor_y += gfxFont->yAdvance * textsize;
  } else {
    cursor_y += 8 * textsize;
  }
}

// Draw string at specific position, restore cursor, return width
int16_t ILI9486_Display::drawString(const String &string, int32_t x, int32_t y, uint8_t font) {
  // Save current state
  uint16_t old_x = cursor_x;
  uint16_t old_y = cursor_y;
  uint8_t old_size = textsize;
  const GFXfont *old_font = gfxFont;
  
  // Font selection logic
  if (font == 0) {
    // Use current font from setFreeFont() (could be nullptr for built-in 5x7)
    // gfxFont already set, no change needed
    textsize = old_size;  // Keep current textsize
  } else if (font == 1) {
    // Explicitly select built-in 5x7 font
    gfxFont = nullptr;
    textsize = old_size;  // Allow scaling
  } else if (font < 6) {
    // Select from font array (indices 2-5)
    if (fontArray[font] != nullptr) {
      gfxFont = fontArray[font];
      textsize = old_size;  // Allow scaling
    } else {
      // Font slot empty, fall back to built-in 5x7
      gfxFont = nullptr;
      textsize = old_size;
    }
  } else {
    // Out of bounds, fall back to built-in 5x7
    gfxFont = nullptr;
    textsize = old_size;
  }
  
  // Calculate width and height before drawing
  int16_t width = 0;
  int16_t height = 0;
  int16_t ascent = 0;
  
  if (gfxFont) {
    // GFX font - calculate bounds
    int16_t minY = 127, maxY = -128;  // Track min/max Y offsets
    
    for (unsigned int i = 0; i < string.length(); i++) {
      char c = string[i];
      if (c >= gfxFont->first && c <= gfxFont->last) {
        uint8_t glyph_index = c - gfxFont->first;
        GFXglyph *glyph = &(((GFXglyph *)gfxFont->glyph)[glyph_index]);
        width += pgm_read_byte(&glyph->xAdvance) * textsize;
        
        // Track Y bounds for height calculation
        int8_t yo = pgm_read_byte(&glyph->yOffset);
        uint8_t h = pgm_read_byte(&glyph->height);
        if (yo < minY) minY = yo;
        if (yo + h > maxY) maxY = yo + h;
      }
    }
    
    ascent = -minY * textsize;   // Distance above baseline (minY is negative)
    height = (maxY - minY) * textsize;
  } else {
    // Built-in font - 6 pixels per char (5 + 1 spacing), 8 pixels tall
    width = string.length() * 6 * textsize;
    height = 8 * textsize;
    ascent = height;  // All above baseline for built-in font
  }
  
  // Apply datum positioning
  int16_t adjusted_x = x;
  int16_t adjusted_y = y;
  
  // Horizontal adjustment based on datum
  uint8_t h_datum = textdatum % 3;  // 0=Left, 1=Center, 2=Right
  if (h_datum == 1) {
    adjusted_x -= width / 2;  // Center
  } else if (h_datum == 2) {
    adjusted_x -= width;  // Right
  }
  
  // Vertical adjustment based on datum
  uint8_t v_datum = textdatum / 3;  // 0=Top, 1=Middle, 2=Bottom
  if (v_datum == 0) {
    // Top datum - adjust so y is at top of text
    if (gfxFont) {
      adjusted_y += ascent;  // Move down by ascent
    }
    // Built-in font: no adjustment needed (draws from top)
  } else if (v_datum == 1) {
    // Middle datum - adjust so y is at vertical center
    if (gfxFont) {
      adjusted_y += ascent - (height / 2);
    } else {
      adjusted_y += height / 2;
    }
  }
  // Bottom/Baseline datum (v_datum == 2): no adjustment (default GFX behavior)
  
  // Set position
  cursor_x = adjusted_x;
  cursor_y = adjusted_y;
  
  // Draw the string using existing print method
  print(string.c_str());
  
  // Restore original cursor position, size, and font
  cursor_x = old_x;
  cursor_y = old_y;
  textsize = old_size;
  gfxFont = old_font;
  
  return width;
}

// Draw string centered horizontally around x coordinate
int16_t ILI9486_Display::drawCentreString(const char *string, int32_t x, int32_t y, uint8_t font) {
  // Save current state
  uint8_t old_size = textsize;
  const GFXfont *old_font = gfxFont;
  
  // Font selection logic (same as drawString)
  if (font == 0) {
    // Use current font from setFreeFont()
    textsize = old_size;
  } else if (font == 1) {
    // Explicitly select built-in 5x7 font
    gfxFont = nullptr;
    textsize = old_size;
  } else if (font < 6) {
    // Select from font array (indices 2-5)
    if (fontArray[font] != nullptr) {
      gfxFont = fontArray[font];
      textsize = old_size;
    } else {
      // Font slot empty, fall back to built-in 5x7
      gfxFont = nullptr;
      textsize = old_size;
    }
  } else {
    // Out of bounds, fall back to built-in 5x7
    gfxFont = nullptr;
    textsize = old_size;
  }
  
  // Calculate width to determine center offset
  int16_t width = 0;
  
  if (gfxFont) {
    // GFX font - sum character advances
    const char *p = string;
    while (*p) {
      char c = *p++;
      if (c >= gfxFont->first && c <= gfxFont->last) {
        uint8_t glyph_index = c - gfxFont->first;
        GFXglyph *glyph = &(((GFXglyph *)gfxFont->glyph)[glyph_index]);
        width += pgm_read_byte(&glyph->xAdvance) * textsize;
      }
    }
  } else {
    // Built-in font - 6 pixels per char (5 + 1 spacing)
    width = strlen(string) * 6 * textsize;
  }
  
  // Restore font and textsize
  gfxFont = old_font;
  textsize = old_size;
  
  // Draw centered by offsetting x by half the width
  return drawString(String(string), x - (width / 2), y, font);
}

// Draw bitmap (1-bit per pixel, MSB first)
void ILI9486_Display::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
  int16_t byteWidth = (w + 7) / 8;
  uint8_t byte = 0;
  
  for (int16_t j = 0; j < h; j++) {
    for (int16_t i = 0; i < w; i++) {
      if (i & 7) {
        byte <<= 1;
      } else {
        byte = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
      }
      if (byte & 0x80) {
        drawPixel(x + i, y + j, color);
      }
    }
  }
}

// Draw bitmap with background color
void ILI9486_Display::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {
  int16_t byteWidth = (w + 7) / 8;
  uint8_t byte = 0;
  
  for (int16_t j = 0; j < h; j++) {
    for (int16_t i = 0; i < w; i++) {
      if (i & 7) {
        byte <<= 1;
      } else {
        byte = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
      }
      if (byte & 0x80) {
        drawPixel(x + i, y + j, color);
      } else {
        drawPixel(x + i, y + j, bg);
      }
    }
  }
}

#endif // ILI9486_DISPLAY_H
