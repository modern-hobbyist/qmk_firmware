/* Copyright 2024 Modern Hobbyist <https://github.com/modern-hobbyist>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

/* Use the custom font */
#define OLED_FONT_H "./lib/glcdfont.c"

// #ifdef RGB_MATRIX_TIMEOUT
//  #undef RGB_MATRIX_TIMEOUT
// #endif

#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 60000

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN B3
#define SPI_MISO_PIN B4
#define SPI_MOSI_PIN B5
#define SPI_SCK_PAL_MODE 0
#define SPI_MISO_PAL_MODE 0
#define SPI_MOSI_PAL_MODE 0

#define LCD_RST_PIN B6
#define LCD_CS_PIN A0
#define LCD_DC_PIN A1
#define LCD_ENABLE_PIN B7
#ifndef LCD_ACTIVITY_TIMEOUT
#    define LCD_ACTIVITY_TIMEOUT 60000
#endif

// Backlight driver (to control LCD backlight)
// #define BACKLIGHT_PWM_DRIVER PWMD1
// #define BACKLIGHT_PWM_CHANNEL 3
// #define BACKLIGHT_LEVELS 10
// #define BACKLIGHT_PAL_MODE 2
// #define BACKLIGHT_PIN B8
#define EE_HANDS
#define SPLIT_TRANSFORM_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_USB_DETECT
#define SPLIT_WATCHDOG_ENABLE

#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 2
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM5

#define SERIAL_USART_SPEED 57600
#define SERIAL_DEBUG
#define DEBUG_MATRIX_SCAN_RATE

#undef SERIAL_USART_DRIVER
#define SERIAL_USART_DRIVER SD2

#undef SERIAL_USART_TX_PAL_MODE
#define SERIAL_USART_TX_PAL_MODE 1

#define SERIAL_USART_CONFIG                          \
    {.speed = (SERIAL_USART_SPEED),                  \
     .cr1   = (SERIAL_USART_CR1),                    \
     .cr2   = ((SERIAL_USART_CR2) | USART_CR2_SWAP), \
     .cr3   = ((SERIAL_USART_CR3) | USART_CR3_HDSEL)}
