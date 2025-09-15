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


#ifndef INC_SES_TEST_VLAN_H_
#define INC_SES_TEST_VLAN_H_

#include <stdint.h>


/**
 * @brief VLAN main example as per the configuration.h.
 * @return None 
 * 
 */
void sesVlan_Example(void);

/**
 * @brief Set Port 3 and port 4 in Learn and Forward Mode for given VLAN
 * @return int32_t SES return status code
 */
int32_t sesSetVlanMode_Example(void);

/**
 * @brief Set VLAN operating mode for vid 20 as Learn and Forward for Port 5
 * @return int32_t SES return status code
 */
int32_t sesSetVlanPortMode_Example(void);

/**
 * @brief Set VLAN operating mode for port 4 for all configured VLANs
 * @return int32_t SES return status code
 */
int32_t sesSetVlanPortModeAll_Example(void);


/**
 * @brief Trunk/Access example with following port configurations: 
		- Port 0 → Host Port
		- Port 1 → Access port, VLAN ID 2, PCP 2
		- Port 2 → Access port, VLAN ID 3, PCP 2
		- Port 3 → Access port, VLAN ID 4, PCP 2
		- Port 4 → Access port, VLAN ID 5, PCP 2
		- Port 5 → Trunk port, VLN ID range 1-5, PCP 2
 * @return None
 */
void sesAccessTrunkMode_Example(void);

/**
 * @brief Insert VLAN tag example 
 * @return None
 */
void sesInsertVlanTag_Example(void);


#endif /* INC_SES_TEST_VLAN_H_ */
