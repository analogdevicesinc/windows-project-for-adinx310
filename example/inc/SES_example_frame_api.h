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


#ifndef INC_SES_TEST_FRAME_API_H_
#define INC_SES_TEST_FRAME_API_H_

#include <stdint.h>

/**
 * @brief Add a static entry for receive callback APIs.
 * @param[in] None
 */
void sesL2ReceiveFrameStaticEntry_Example(void);

/**
 * @brief SES Layer 2 Transmit Example.
 * @param[in] API response code
 */
int32_t sesL2Transmit_Example(void);

/**
 * @brief SES Layer 2 Receive Example by MAC.
 * @param[in] API response code
 */
int32_t sesRxSesFramesByMac_Example(void);

/**
 * @brief Receive Layer 2 frames with matching Ethertype and data at a SES port.
 * @param[in] API response code
 */
int32_t sesRxSesFramesByEtype_Example(void);

/**
 * @brief Receive Layer 2 frames with matching Ethertype only at a SES port.
 * @param[in] API response code
 */
int32_t sesRxSesFramesByEtypeOnly_Example(void);

/**
 * @brief SES Layer 2 Receive Example by Ethertype Stack Processor.
 * @param[in] API response code
 */
int32_t sesRxStackProcessorFramesByMac_Example(void);

/**
 * @brief SES Layer 2 Receive Example by MAC Stack Processor.
 * @param[in] API response code
 */
int32_t sesRxStackProcessorFramesByEtype_Example(void);

/**
 * @brief SES Layer 2 main example.
 * @param[in] None
 */
void seslayer2_Example(void);


#endif /* INC_SES_TEST_FRAME_API_H_ */
