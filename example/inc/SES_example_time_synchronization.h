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


#ifndef INC_SES_TEST_TIME_SYNCHRONIZATION_H_
#define INC_SES_TEST_TIME_SYNCHRONIZATION_H_

#include <stdint.h>


/**
 * @brief Creates the PTP Test instance.
 * @return None
 */
void sesSingleASPtpInstance_Example(void);


/**
 * @brief Creates the multiple PTP instance.
 * @return int8_t SES return status code
 */
int32_t sesMultipleASPtpInstance_Example(void);

/**
 * @brief Main time synch function.
 * @return None
 */
void sesTimeSync_Example(void);

/**
 * @brief Deleted the PTP instance Test.
 * @param[in]: instance index
 */
void sesPtpDeletePtpInstance_Example(uint32_t instanceIndex);

/**
 * @brief Tells you the number of PTP instance Tests.
 * @return None
 */
void sesPtpGetNumberPtpInstances_Example(void);

/**
 * @brief sets the default DSTests.
 * @return None
 */
void sesPtpSetDefaultDs_Example(void);

/**
 * @brief Example for Ordinary clock configuration.
 * @return None
 */
void sesOrdinaryClock1588GM_Example(void);

/**
 * @brief Example for Boundary clock configuration.
 * @return None
 */
void sesBoundaryClock1588_Example(void);


/**
 * @brief Example for Transparent clock configuration.
 * @return None
 */
void sesTransparentClock1588E2E_Example(void);

/**
 * @brief Retrieve PTP parameters.
 * @return None
 */
void sesGetPtpParameters_Example(int input);



#endif /* INC_SES_TEST_TIME_SYNCHRONIZATION_H_ */
