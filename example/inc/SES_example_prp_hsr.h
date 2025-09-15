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


#ifndef INC_SES_TEST_PRP_HSR_H_
#define INC_SES_TEST_PRP_HSR_H_

#include <stdint.h>

/**
 * @brief Starts the PRP (Parallel Redundancy Protocol) stack
 * @param[in] portC: PRP host port number, or -1 to select SPI interface
 * @return int32_t SES return status code
 */
int32_t sesPrpStart_Example(int32_t portC);

/**
 * @brief Starts the PRP stack and configures it for Redbox mode.
 * @param[in] portC: PRP host port number, or -1 to select SPI interface
 * @return int32_t SES return status code
 */
int32_t sesPrpRedboxStart_Example(int32_t portC);

/**
 * @brief Start and configure PRP for Redbox mode with PRP ports as access ports and interlink ports as trunk ports
 * @param[in] portC: PRP host port number, or -1 to select SPI interface
 * @return int32_t SES return status code
 */ 
int32_t sesPrpRedboxStartVlan_Example(int32_t portC);

/**
 * @brief Start HSR (High-availability Seamless Redundancy) stack
 * @param[in] portC: HSR host port number, or -1 to select SPI interface
 * @return int32_t SES return status code
 */
int32_t sesHsrStart_Example(int32_t portC);

/**
 * @brief Starts the HSR stack and configures it for Redbox mode.
 * @param[in] portC: HSR host port number, or -1 to select SPI interface
 * @return int32_t SES return status code
 */
int32_t sesHsrRedboxStart_Example(int32_t portC);

/**
 * @brief Configures the duplicate discard mode for the redundancy protocol.
 * @return int32_t SES return status code
 */
int32_t sesDuplicateDiscardModeConfiguration_Example(void);

/**
 * @brief Adds a VLAN tag to supervision frames.
 * @return int32_t SES return status code
 */
int32_t sesAddVlanSupervisionFrame_Example(void);

/**
 * @brief Sets the HSR mode.
 * @return int32_t SES return status code
 */
int32_t sesSetHsrMode_Example(void);

/**
 * @brief Verifies that PRP or HSR is executing.
 * @return int32_t SES return status code
 */
int32_t sesVerifyRedundancyExecuting_Example(void);

/**
 * @brief Retrieve status of LRE configuration.
 * @return int32_t SES return status code
 */
int32_t sesGetLreStatus_Example(void);

/**
 * @brief Gets entries for LRE nodes entries.
 * @return int32_t SES return status code
 */
int32_t sesGetLreNodesEntry_Example(void);

/**
 * @brief Gets entries for LRE proxy node entries.
 * @return int32_t SES return status code
 */
int32_t sesGetLreProxyNodesEntry_Example(void);

/**
 * @brief Sets the MAC address for supervision frames.
 * @return int32_t SES return status code
 */
int32_t sesSetSupervisionFrameMAC_Example(void);

/**
 * @brief Sets the forwarding mode of the switch.
 * @return int32_t SES return status code
 */
int32_t sesSetForwarding_Example(void);

/**
 * @brief Retrieves the current forwarding mode of the switch.
 * @return int32_t SES return status code
 */
int32_t sesGetForwarding_Example(void);

/**
 * @brief Initializing PRP or HSR configuration examples
 * 0: PRP, 1: PRP Redbox, 2: HSR, 3: HSR Redbox
 */
void sesHsrPrp_Example(void);


#endif /* INC_SES_TEST_PRP_HSR_H_ */
