#ifndef _TFT_16BITS_H_
#define _TFT_16BITS_H_

#include "Adafruit_GFX_Simple.h"

class TFT_16bits : public Adafruit_GFX {

public:
  TFT_16bits(uint16_t w, uint16_t h);
  ~TFT_16bits(void);
  size_t createPSRAMFrameBuffer(void);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void fillScreen(uint16_t color);
  void byteSwap(void);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  uint16_t getPixel(int16_t x, int16_t y) const;
  /**********************************************************************/
  /*!
    @brief    Get a pointer to the internal buffer memory
    @returns  A pointer to the allocated buffer
  */
  /**********************************************************************/
  uint16_t *getBuffer(void) const { return buffer; }
  void setBuffer(uint16_t *bufPtr) { buffer = bufPtr; }
  
  void setWidth(uint16_t w) { WIDTH = w; }
  void setHeight(uint16_t h) { HEIGHT = h; }
  void setWidthHeight(uint16_t w, uint16_t h) { _width = WIDTH = w; _height = HEIGHT = h; }
 
protected:
  uint16_t getRawPixel(int16_t x, int16_t y) const;
  void drawFastRawVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void drawFastRawHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

private:
  uint16_t *buffer;
};

#endif
