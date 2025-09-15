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


#ifndef INC_SES_TEST_PREEMPTION_H_
#define INC_SES_TEST_PREEMPTION_H_

#include <stdint.h>

/**
 * @brief Configure preemption using a configuration structure.
 * 
 */
void sesSetPreemptionConfigurationStructure_Example(void);

/**
 * @brief Configure preemption using multiple preemption APIs.
 * 
 */
void sesSetPreemptionConfigurationApi_Example(void);

/**
 * @brief Example to disable preemption.
 * 
 */
void sesDisablePreemption_Example(void);

/**
 * @brief Example to retrieve preemption statistics.
 * 
 */
void sesGetPreemptionStatistics_Example(void);



#endif /* INC_SES_TEST_PREEMPTION_H_ */
