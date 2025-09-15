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


#ifndef INC_SES_TEST_PSFP_H_
#define INC_SES_TEST_PSFP_H_

#include <stdint.h>

/**
 * @brief Configure switch stream filter.
 * @return int32_t SES return status code.
 */
int32_t sesStreamFilter_Example(void);

/**
 * @brief Configure switch stream gate.
 * @return int32_t SES return status code.
 */
int32_t sesStreamGate_Example(void);

/**
 * @brief Configure switch flow meter.
 * @return int32_t SES return status code.
 */
int32_t sesFlowMeter_Example(void);

/**
 * @brief Read PSFP statistics.
 * @return int32_t SES return status code.
 */
int32_t sesReadPsfpStatistics_Example(void);

/**
 * @brief Reprioritive PCP of ingressing frames.
 * @return int32_t SES return status code.
 */
int32_t sesIpvReprioritize_Example(void);

/**
 * @brief Initializes and runs PSFP example routines
 * 0: Disable, 1: Stream Filter Example, 2: Stream Gate Example, 3: Flow Meter Example
 */
void sesPsfp_Example(void);



#endif /* INC_SES_TEST_EVENT_H_ */