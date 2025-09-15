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


#ifndef INC_SES_TEST_FIRMWARE_H_
#define INC_SES_TEST_FIRMWARE_H_

#include <stdint.h>

/**
 * @brief This will load the firmware in a single block.
 * @return int8_t SES return status code
 */
void sesImageLoaderSingleblock_Example(void);

/**
 * @brief This will load the firmware in a multiple block.
 * @return int8_t SES return status code
 */
void sesFirmwareUpdateFileSytem_Example(void);

/**
 * @brief This function will load the firmware based upon if image is in single block or multiple block.
 * 
 */
void sesFirmwareUpdate_Example(void);



#endif /* INC_SES_TEST_FIRMWARE_H_ */
