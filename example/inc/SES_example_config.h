/* 
 * Copyright 2025 Analog Devices, Inc.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     https://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file SES_example_config.h
 * This file contains the generic Core adinx310 configuration for API calls.
 */

#ifndef INC_SES_EXAMPLE_CONFIG_H_
#define INC_SES_EXAMPLE_CONFIG_H_

#include <stdint.h>

/**
 * @brief Initializes the SES driver.
 * @return int32_t SES return status code
 */
int32_t sesConfig(void);


/**
 * @brief Configuration the SES based upon paramters passed in SES_configuration file.
 * 
 */
void sesProtocolInitialization_Example(void);


/**
 * @brief Gives you the firmware details.
 * @return int32_t SES return status code
 */
void sesGetAppInfo_Example(void);

#endif
