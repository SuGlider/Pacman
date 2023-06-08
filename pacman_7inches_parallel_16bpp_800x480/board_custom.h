/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#define BOARD_DISP_COUNT 3     /* Count of LCD displays connected to this board */

/* SD card */
#define BOARD_SD_CLK    GPIO_NUM_35
#define BOARD_SD_CMD    GPIO_NUM_0
#define BOARD_SD_D0     GPIO_NUM_36

/* I2C pins */
#define BOARD_I2C_SCL   GPIO_NUM_41
#define BOARD_I2C_SDA   GPIO_NUM_42

/* I2C Touch */
#define BOARD_DISP_TOUCH_CONTROLLER BOARD_DISP_TOUCH_GT911
#define BOARD_DISP_TOUCH_INT GPIO_NUM_2
#define BOARD_DISP_TOUCH_HRES 800
#define BOARD_DISP_TOUCH_VRES 480

/* I2C display */
#define BOARD_DISP_I2C_CONTROLLER BOARD_DISP_LCD_SH1107
#define BOARD_DISP_I2C_RST  GPIO_NUM_40
#define BOARD_DISP_I2C_BL   GPIO_NUM_NC
#define BOARD_DISP_I2C_HRES 128
#define BOARD_DISP_I2C_VRES 64

/* SPI display */
#define BOARD_DISP_SPI_CONTROLLER BOARD_DISP_LCD_GC9A01
#define BOARD_DISP_SPI_MOSI GPIO_NUM_19
#define BOARD_DISP_SPI_SCLK GPIO_NUM_20
#define BOARD_DISP_SPI_CS   GPIO_NUM_21
#define BOARD_DISP_SPI_DC   GPIO_NUM_47
#define BOARD_DISP_SPI_RST  GPIO_NUM_48
#define BOARD_DISP_SPI_BL   GPIO_NUM_45
#define BOARD_DISP_SPI_HRES 240
#define BOARD_DISP_SPI_VRES 240

/* Parallel display */
#define BOARD_DISP_PARALLEL_CONTROLLER BOARD_DISP_LCD_RA8875
#define BOARD_DISP_PARALLEL_WIDTH   16
#define BOARD_DISP_PARALLEL_DB0     GPIO_NUM_13
#define BOARD_DISP_PARALLEL_DB1     GPIO_NUM_12
#define BOARD_DISP_PARALLEL_DB2     GPIO_NUM_11
#define BOARD_DISP_PARALLEL_DB3     GPIO_NUM_10
#define BOARD_DISP_PARALLEL_DB4     GPIO_NUM_9
#define BOARD_DISP_PARALLEL_DB5     GPIO_NUM_46
#define BOARD_DISP_PARALLEL_DB6     GPIO_NUM_3
#define BOARD_DISP_PARALLEL_DB7     GPIO_NUM_8
#define BOARD_DISP_PARALLEL_DB8     GPIO_NUM_18
#define BOARD_DISP_PARALLEL_DB9     GPIO_NUM_17
#define BOARD_DISP_PARALLEL_DB10    GPIO_NUM_16
#define BOARD_DISP_PARALLEL_DB11    GPIO_NUM_15
#define BOARD_DISP_PARALLEL_DB12    GPIO_NUM_7
#define BOARD_DISP_PARALLEL_DB13    GPIO_NUM_6
#define BOARD_DISP_PARALLEL_DB14    GPIO_NUM_5
#define BOARD_DISP_PARALLEL_DB15    GPIO_NUM_4
#define BOARD_DISP_PARALLEL_CS      GPIO_NUM_NC
#define BOARD_DISP_PARALLEL_DC      GPIO_NUM_37
#define BOARD_DISP_PARALLEL_WR      GPIO_NUM_38
#define BOARD_DISP_PARALLEL_RD      GPIO_NUM_NC
#define BOARD_DISP_PARALLEL_RST     GPIO_NUM_39
#define BOARD_DISP_PARALLEL_WAIT    GPIO_NUM_1
#define BOARD_DISP_PARALLEL_BL      GPIO_NUM_NC
#define BOARD_DISP_PARALLEL_HRES    800
#define BOARD_DISP_PARALLEL_VRES    480
