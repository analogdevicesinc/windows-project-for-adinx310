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

 /**
  * @file SES_example_event.h
  *
  */

#ifndef INC_SES_TEST_EVENT_H_
#define INC_SES_TEST_EVENT_H_
#include <stdint.h>

  /**
   * @brief Enabling event example based upon parameter based in in ses_configuration.
   * @param[in] 0:disable, 1: Enable LinkEventExample, 2: Enable LLDP Event Example, 3: Timer Event Example
   */
void sesEvent_Example(void);

/**
 * @brief Subscribe to Link up and Link down events.
 * @return int32_t SES return status code
 */
int32_t sesLinkEvent_Example(void);

/**
 * @brief This example demonstrates LLDP event handling with two SES devices connected
 *				in a daisy-chain configuration. For daisy-chain setup, refer the provoded example 
 *				"sesETH_ETHInit_Example" in SES_example_init.c.
 *				The example subscribes to multiple LLDP-related events defined in SES_event.h.
 *				The user must define a callback function on the host side to handle these events.
 * @return int32_t SES return status code
 */
int32_t sesEventLldp_Example(void);

/**
 * @brief Subscribe to Input Capture Event
 * @param[in] 0:disable, 1: Enable LinkEventExample, 2: Enable LLDP Event Example, 3: Timer Event Example
 *
 */
void sesTimerEventTest_Example(void);




#endif /* INC_SES_TEST_EVENT_H_ */
