// Copyright 2024 Modern Hobbyist
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include_next <mcuconf.h>

#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2 TRUE

#define I2C_DRIVER I2CD2

// In mcuconf.h

#define STM32_I2C_BUSY_TIMEOUT 50
#define STM32_I2C_USE_DMA TRUE
#define STM32_I2C_I2C2_RX_DMA_STREAM STM32_DMA_STREAM_ID(1, 5)
#define STM32_I2C_I2C2_TX_DMA_STREAM STM32_DMA_STREAM_ID(1, 4)
#define STM32_I2C_DMA_ERROR_HOOK(i2cp) osalSysHalt("DMA failure")
