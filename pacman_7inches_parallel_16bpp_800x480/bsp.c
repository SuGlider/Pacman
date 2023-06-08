#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "esp_heap_caps.h"
#include "esp_log.h"

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "board.h"
#include "lcd.h"
#if (BOARD_DISP_TOUCH_CONTROLLER == BOARD_DISP_TOUCH_GT911)
#include "esp_lcd_touch_gt911.h"
#elif (BOARD_DISP_TOUCH_CONTROLLER == BOARD_DISP_TOUCH_TT21100)
#include "esp_lcd_touch_tt21100.h"
#elif (BOARD_DISP_TOUCH_CONTROLLER == BOARD_DISP_TOUCH_FT5X06)
#include "esp_lcd_touch_ft5x06.h"
#endif

#include "bsp.h"

lcd_disp_t *lcd_parallel8080 = NULL;
esp_lcd_touch_handle_t tp = NULL;

static void app_i2c_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = BOARD_I2C_SDA,
        .scl_io_num = BOARD_I2C_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
    };
    conf.master.clk_speed = 100000;

  esp_err_t retCode = i2c_param_config(CONFIG_I2C_NUM, &conf);
  if (retCode != ESP_OK) {
      printf("i2c_param_config failed\n");
  } else {
      retCode = i2c_driver_install(CONFIG_I2C_NUM, conf.mode, 0, 0, 0);
      if (retCode != ESP_OK) {
          printf("i2c_driver_install failed\n");
      }
  }
}

#if (BOARD_DISP_PARALLEL_CONTROLLER > 0)
volatile bool _disp_flush_ready = false;

static void lcd_8080_flush_ready_cb(lcd_disp_t * disp)
{
   _disp_flush_ready = true;
}
#endif

void lcd_driver_install(void)
{
    /* Initialize I2C */
    app_i2c_init();

#if (BOARD_DISP_PARALLEL_CONTROLLER > 0)
    /* Initialize Parallel Display */
    lcd_cfg_t lcd_parallel8080_cfg = {};
    lcd_parallel8080_cfg.driver = (lcd_driver_t) BOARD_DISP_PARALLEL_CONTROLLER;
    lcd_parallel8080_cfg.flush_ready_cb = lcd_8080_flush_ready_cb;
    lcd_parallel8080 = lcd_parallel8080_init(&lcd_parallel8080_cfg);
    if (lcd_parallel8080 == NULL) {
      printf("lcd_parallel8080_init failed/n");
    }
  #endif

#if (BOARD_DISP_TOUCH_CONTROLLER > 0)
    esp_lcd_panel_io_handle_t io_handle = NULL;
#if (BOARD_DISP_TOUCH_CONTROLLER == BOARD_DISP_TOUCH_GT911)
    esp_lcd_panel_io_i2c_config_t io_config = ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();
#elif (BOARD_DISP_TOUCH_CONTROLLER == BOARD_DISP_TOUCH_TT21100)
    esp_lcd_panel_io_i2c_config_t io_config = ESP_LCD_TOUCH_IO_I2C_TT21100_CONFIG();
#elif (BOARD_DISP_TOUCH_CONTROLLER == BOARD_DISP_TOUCH_FT5X06)
    esp_lcd_panel_io_i2c_config_t io_config = ESP_LCD_TOUCH_IO_I2C_FT5x06_CONFIG();
#endif
ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c((esp_lcd_i2c_bus_handle_t)CONFIG_I2C_NUM, &io_config, &io_handle));

    /* Initialize touch */
    esp_lcd_touch_config_t tp_cfg = {
        .x_max = BOARD_DISP_TOUCH_HRES,
        .y_max = BOARD_DISP_TOUCH_VRES,
        .rst_gpio_num = (gpio_num_t) -1,
        .int_gpio_num = (gpio_num_t) -1,
        .levels = {
            .reset = 0,
            .interrupt = 0,
        },
    };
 
    #if (BOARD_DISP_TOUCH_CONTROLLER == BOARD_DISP_TOUCH_GT911)
        tp_cfg.flags.swap_xy = 1;
        tp_cfg.flags.mirror_x = 0;
        tp_cfg.flags.mirror_y = 1;
        esp_lcdTouch_new_i2c_gt911(io_handle, &tp_cfg, &tp);
    #elif (BOARD_DISP_TOUCH_CONTROLLER == BOARD_DISP_TOUCH_TT21100)
        tp_cfg.flags.swap_xy = 1;
        tp_cfg.flags.mirror_x = 1;
        tp_cfg.flags.mirror_y = 1;
        esp_lcd_touch_new_i2c_tt21100(io_handle, &tp_cfg, &tp);
    #elif (BOARD_DISP_TOUCH_CONTROLLER == BOARD_DISP_TOUCH_FT5X06)
        tp_cfg.flags.swap_xy = 0;
        tp_cfg.flags.mirror_x = 0;
        tp_cfg.flags.mirror_y = 0;
        esp_lcd_touch_new_i2c_ft5x06(io_handle, &tp_cfg, &tp);
    #endif
#endif

  if (tp == NULL) {
    printf("\nTouchpad setup ERROR!\n");
  }

#if 1
  //printf("\napp_main:: STARTING!\n");

  uint16_t tile[64];
  int xs = BOARD_DISP_PARALLEL_HRES / 8;
  int ys = BOARD_DISP_PARALLEL_VRES / 8;
  for (int y = 0; y < ys; y++)
    for (int x = 0; x < xs; x++) {
       uint16_t color = (y<<6) + x; // testing...
       color = 0; // clear screen
       memset(tile, color, sizeof(tile));
       //printf("drawing (%d, %d) color %x in screen\n===============\n", x*8, y*8, color);
       bsp_lcd_flush(x * 8, y * 8, x * 8 + 8, y * 8 + 8, (void *)tile);
       //lcd_parallel8080_draw(lcd_parallel8080, x * 8, y * 8, x * 8 + 8, y * 8 + 8, (void *)tile);

    }

  //printf("\napp_main:: DONE!\n");
  //delay(5000);
#endif
}

void  bsp_lcd_flush(int x0, int y0, int x1, int y1, void *pixels) {
  if (lcd_parallel8080 == NULL || pixels == NULL) {
    printf("bsp_lcd_flush:: NULL pointer!\n");
    return;
  }
  lcd_parallel8080_draw(lcd_parallel8080, x0, y0, x1, y1, (void *)pixels);

  // FIX-ME :: delay shall be replaced by a flag set when the display is flushed
  //vTaskDelay(1);
  while (!_disp_flush_ready) {}
  _disp_flush_ready = false;
}

esp_err_t touchPadRead(uint8_t *numTouchedPoints, uint16_t *scrTouchX, uint16_t *scrTouchY) {
    
    if (tp == NULL) {
      printf("\nTouchpad not initialized. NULL pointer.\n");
      return ESP_FAIL;
    }
#if 0 // code for the Esp32-Box
    uint8_t state = 0;
    esp_lcd_touch_get_button_state(tp, 0, &state);

    if (state == 0) {
      numTouchedPoints = 0;
      return ESP_OK;
    }
#endif
    
    esp_lcd_touch_read_data(tp);

    /* Read data from touch controller */
    uint16_t touchpad_x[1] = {0};
    uint16_t touchpad_y[1] = {0};
    uint8_t touchpad_cnt = 0;

    bool touchpad_pressed = esp_lcd_touch_get_coordinates(tp, touchpad_x, touchpad_y, NULL, &touchpad_cnt, 1);

    if (touchpad_pressed && touchpad_cnt > 0) {
        *scrTouchX = BOARD_DISP_TOUCH_VRES - touchpad_x[0];
        *scrTouchY = touchpad_y[0];
        *numTouchedPoints = touchpad_cnt;
        //printf("Touch Detected: #%d - (%d, %d)\n", *numTouchedPoints, *scrTouchX, *scrTouchY);
    } else {
        *numTouchedPoints = 0;
    }
  return ESP_OK;
}
