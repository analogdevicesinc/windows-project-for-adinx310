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


#ifndef INC_SES_TEST_MSTP_H_
#define INC_SES_TEST_MSTP_H_

#include <stdint.h>

/**
 * @brief Initialize MSTP Stack and Start.
 * @return int32_t SES return status code
 */
int32_t sesMstpStackStart_Example(void);

/**
 * @brief This example initializes and creates multiple MST instances.
 * @return int32_t SES return status code
 */
int32_t sesMultipleMsti_Example(void);

/**
 * @brief This example retrieves the mapping of VLAN IDs to MSTI.
 * @return int32_t SES return status code
 */
int32_t sesGetVlanToMstiMap_Example(void);

/**
 * @brief This example demonstrates the bridge forward delay configuration.
 * @return int32_t SES return status code
 */
int32_t sesBridgeForwardDelay_Example(void);


#endif /* INC_SES_TEST_MSTP_H_ */