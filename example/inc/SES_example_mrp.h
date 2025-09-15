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


#ifndef INC_SES_TEST_MRP_H_
#define INC_SES_TEST_MRP_H_

#include <stdint.h>
/**
 * @brief Initialize MRP with below befault configuration
		Ring Role * *: Client
		Recovery Rate * *: 500 ms
		Ring Ports * *: Port 1 & 2
		VLAN * *: No Vlan(0x0FFF)
		Priority * *: Default Manager / AutoManager priorities
		React On Link Change * *: Disabled
 * 
 */
void sesStartMrp(void);


/**
 * @brief Get the operational MRP instance configuration.
 * 
 */
void sesGetInstanceConfig_Example(void);


/**
 * @brief Sets MRP Ring ports
 * 
 */
void sesSetRingPorts_Example(void);


/**
 * @brief This API verifies if MRP is enabled or not.
 * 
 */
int32_t sesVerifyMrpEnabled_Example(void);


/**
 * @brief Get Domain statistics.
 * 
 */
void sesGetDomainStatistics_Example(void);


/**
 * @brief sets MRP Client.
 * 
 */
void  sesSetMrpClient_Example(void);


/**
 * @brief sets MRP Manager.
 * 
 */
int32_t sesSetMrpManager_Example(void);


/**
 * @brief MRP configurationa nd Initilization Below Example first configure the MRP parameters and then initialize MPR protocol
 * 
 */
void sesMRPConfigAndInit_Example(void);


/**
 * @brief Enables MRP.
 * 
 */
void sesMrp_Example();


#endif /* INC_SES_TEST_MRP_H_ */


