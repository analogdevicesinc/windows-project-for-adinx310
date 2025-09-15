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


#ifndef INC_SES_TEST_INIT_H_
#define INC_SES_TEST_INIT_H_


/**
* @brief Initialize Multi switch in daisy chain 
* @return API response code 
*/
int32_t sesETH_ETHInit_Example(void);

/**
 * @brief Initialize SES over Quad SPI 
 * @return API response code 
 */
int32_t sesQSPIInit_Example(void);

/**
 * @brief Initialize multiple SES instances, with the 1st SES connected via SPI and the 2nd SES connected over Ethernet through SES1
 * @return API response code 
 */
int32_t sesSpiEthInit_Example(void);

/**
 * @brief Initialze Multi SES connected in Tree configuration 
 * @return None
 */
void sesInitTreeConfig_Example(void);


#endif /* INC_SES_TEST_INIT_H_ */

