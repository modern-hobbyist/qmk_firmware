#pragma once

// #define HAL_USE_GPT TRUE
#define HAL_USE_PWM TRUE
#define HAL_USE_SPI TRUE
#define HAL_USE_I2C FALSE
// #define HAL_USE_SERIAL TRUE
// #define SERIAL_BUFFERS_SIZE 256

// This enables interrupt-driven mode
#define PAL_USE_WAIT TRUE

#define HAL_USE_SERIAL TRUE

#include_next <halconf.h>
