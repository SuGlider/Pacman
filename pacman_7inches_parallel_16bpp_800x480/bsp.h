#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void lcd_driver_install(void);
void  bsp_lcd_flush(int x0, int y0, int x1, int y1, void *pixels);
esp_err_t touchPadRead(uint8_t *numTouchedPoints, uint16_t *scrTouchX, uint16_t *scrTouchY);

#ifdef __cplusplus
}
#endif
