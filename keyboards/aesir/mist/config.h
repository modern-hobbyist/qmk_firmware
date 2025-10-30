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

// Bootloader
#define STM32_BOOTLOADER_DUAL_BANK TRUE
#define STM32_BOOTLOADER_DUAL_BANK_GPIO B7

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MISO_PIN A6
#define SPI_MOSI_PIN A7
#define SPI_SCK_PAL_MODE 5
#define SPI_MISO_PAL_MODE 5
#define SPI_MOSI_PAL_MODE 5

#define LCD_RST_PIN B5
#define LCD_CS_PIN B6
#define LCD_DC_PIN B4
#ifndef LCD_ACTIVITY_TIMEOUT
#    define LCD_ACTIVITY_TIMEOUT 600000
#endif

// Backlight driver (to control LCD backlight)
#define BACKLIGHT_PWM_DRIVER PWMD1
#define BACKLIGHT_PAL_MODE 6
#define BACKLIGHT_PWM_CHANNEL 1
#define BACKLIGHT_LEVELS 10
#define BACKLIGHT_PIN A8

#define WS2812_PWM_DRIVER PWMD8
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_DMAMUX_ID STM32_DMAMUX1_TIM8_UP

#define SERIAL_DEBUG
#define DEBUG_MATRIX_SCAN_RATE

#undef STM32_ONBOARD_EEPROM_SIZE
#define STM32_ONBOARD_EEPROM_SIZE 2048

#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 0
#define RGB_MATRIX_DISABLE_SHARED_KEYCODES
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

