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


#ifndef INC_SES_TEST_SWITCH_H_
#define INC_SES_TEST_SWITCH_H_

#include <stdint.h>

/**
 * @brief Read entrire dynamic table.
 * @return Print the entries.
 */

void sesReadDynamicTable_Example(void);

/**
 * @brief Retrieve Port Statistics
 * @return None
 */
void sesGetStatistics_Example(void);

/**
 * @brief Installing extended Static table entry
 * @return None
 */
void sesAddStaticTableEntryEx_Example(void);

/**
 * @brief Switch Exmaple selector
 * @return None
 */
void sesSwitch_Example(void);

/**
 * @brief Add extended table entry using simple static route API.
 * @return int32_t SES return status code.
 */
int32_t sesExtendedTableStaticRouteSimple_Example(void);

/**
 * @brief Update port map of existing extended table entry.
 * @return int32_t SES return status code.
 */
int32_t sesUpdateExtendedTable_Example(void);

/**
 * @brief Add IPV4 extended table entry.
 * @return int32_t SES return status code.
 */
int32_t sesExtendedTableStaticRouteIpv4_Example(void);

/**
 * @brief Install IPV4 extended lookup entry.
 * @return int32_t SES return status code.
 */
int32_t sesInstallExtendedLookupEntryIpv4_Example(void);

/**
 * @brief Add IPV6 extended table entry.
 * @return int32_t SES return status code.
 */
int32_t sesExtendedTableStaticRouteIpv6_Example(void);

/**
 * @brief Install IPV6 extended lookup entry.
 * @return int32_t SES return status code.
 */
int32_t sesInstallExtendedLookupEntryIpv6_Example(void);

/**
 * @brief Reprioritze ingress traffic based on ethertpye for all ingress traffic on specific port.
 * @return int32_t SES return status code.
 */
int32_t sesEthertypeReprioritizationRxlookup_Example(void);

/**
 * @brief Reprioritze ingress traffic based on ethertpye using static table entry.
 * @return int32_t SES return status code.
 */
int32_t sesEthertypeReprioritizationStaticTable_Example(void);

/**
 * @brief Update either source or destination MAC using TX transform for Port 1 nad Port 2 with matching destination address 
 * @return None
 */
void sesUpdateMACAddress_Example(void);


#endif /* INC_SES_TEST_SWITCH_H_ */
