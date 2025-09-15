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


#ifndef INC_SES_TEST_LLDP_H_
#define INC_SES_TEST_LLDP_H_
#include <stdint.h>

 /**
  * @brief Initialize LLDP stack.
  * @param[in] None
  */
void sesLldpInit_Example(void);

/**
 * @brief Trigger a (nearly) immediate LLDP transmit on the specified port.
 * @param[in] API response code 
 */
int32_t sesLldpTxSendNow_Example(void);

/**
 * @brief Get a bitmap of the peer IDs of the peers connected to a port5.
 * @param[in] API response code
 */
int32_t sesLldpGetActivePeerIds_Example(void);

/**
 * @brief Return the current LLDP admin configuration for port5
 * @param[in] API response code
 */
int32_t sesLldpGetAdminConfig_Example(void);
/**
 * @brief Set admin configuration for LLDP Stack for port5
 * @param[in] API response code
 */
int32_t sesLldpSetAdminConfig_Example(void);

/**
 * @brief update an existing TLV, Update tlvType4 (Port Description TLV) to Analog Devices
 * @param[in] API response code
 */
int32_t sesLldpUpdateTxTlv_Example(void);

/**
 * @brief Remove an existing TLV from the list of TLVs for Port 5
 * @param[in] API response code
 */
int32_t sesLldpRemoveTxTlv_Example(void);

/**
 * @brief Query a TLV from the list of TLVs to be transmitted for Port 5
 * @param[in] API response code
 */
int32_t sesLldpQueryTxTlv_Example(void);

/**
 * @brief Returns the queried RX TLV for Port 5
 * @param[in] API response code
 */
int32_t sesLldpQueryRxTlv_Example(void);

/**
 * @brief Enable or disable LLDP transmit on port 5
 * @param[in] API response code
 */
int32_t sesLldpTxEnable_Example(void);

/**
 * @brief Check if port 5 has LLDP Tx enabled or not
 * @param[in] API response code
 */
int32_t sesCheckLldpTxEnabled_Example(void);

/**
 * @brief Enable or disable LLDP receive on the port 5
 * @param[in] API response code
 */
int32_t sesLLDPRxEnable_Example(void);

/**
 * @brief Check if port 5 has LLDP Rx enabled or not
 * @param[in] API response code
 */
int32_t sesCheckLLDPRxEnabled_Example(void);

/**
 * @brief Get local system data
 * @param[in] API response code
 */
int32_t sesLLDPGetLocalSystemData_Example(void);

/**
 * @brief Get remote statistics
 * @param[in] API response code
 */
int32_t sesLLDPGetRemoteStatistics_Example(void);

/**
 * @brief Get port transmit statistics
 * @param[in] API response code
 */
int32_t sesLLDPGetTxStatistics_Example(void);

/**
 * @brief Get port receive statistics
 * @param[in] API response code
 */
int32_t sesLLDPGetRxStatistics_Example(void); 

/**
 * @brief Get the MAC address currently in use by the stack for the port5
 * @param[in] API response code
 */
int32_t sesLLDPGetPortMac_Example(void);

/**
 * @brief Override default Primary or Port MAC Addresses
 * for LLDP stack for Port 5
 * @param[in] API response code
 */
int32_t sesLLDPSetPortMac_Example(void);



#endif /* INC_SES_TEST_LLDP_H_ */

