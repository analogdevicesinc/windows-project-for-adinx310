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


#ifndef INC_SES_TEST_FRER_H_
#define INC_SES_TEST_FRER_H_

#include <stdint.h>

/**
 * @brief Demonstrates a null stream identification configuration.
 */
void sesNullStream_Example(void);

/**
 * @brief Demonstrates SMAC VLAN identification configuration.
 */
void sesSmacVlan_Example(void);

/**
 * @brief Demonstrates DMAC VLAN identification configuration.
 */
void sesDmacVlan_Example(void);

/**
 * @brief Demonstrates IP stream identification configuration.
 */
void sesIp_Example(void);

/**
 * @brief Demonstrates mask and match identification configuration.
 */
void sesMaskAndMatch_Example(void);

/**
 * @brief Demonstrates configuring the switch as a talker proxy for a null stream
 * @return int32_t SES return status code
 */
int32_t sesFrerTalker_Example(void);

/**
 * @brief Demonstrates configuring the switch as a listener proxy for a null stream
 * @return int32_t SES return status code
 */
int32_t sesFrerListener_Example(void);

/**
 * @brief Demonstrates configuring the switch as a relay proxy for a null stream
 * @return int32_t SES return status code
 */
int32_t sesFrerRelay_Example(void);

/**
 * @brief Configures the switch as a listener proxy and
 * demonstrates individual recovery for a null stream
 * @return int32_t SES return status code
 */
int32_t sesFrerIndividualRecovery_Example(void);

/**
 * @brief Configures the switch as a listener proxy and
 * demonstrates reading FRER recovery statistics
 * @return int32_t SES return status code
 */
int32_t sesFrerRecoveryStatistics_Example(void);

/**
 * @brief Select switch configuration using macro FRER_CONFIG
 * 1: Talker Proxy, 2: Listener Proxy, 3: Talker and Listener Proxy
 */
void sesFrer_Example(void);


#endif /* INC_SES_TEST_FRER_H_ */