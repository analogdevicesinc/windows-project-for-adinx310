/* 
 * Copyright 2024 Analog Devices, Inc.
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

#ifndef INC_SES_TEST_SCHEDULED_TRAFFIC_H_
#define INC_SES_TEST_SCHEDULED_TRAFFIC_H_

#include <stdint.h>

/**
 * @brief sends the list.
 * @return int32_t SES return status code
 */
int32_t ses_test_scheduled_traffic_timer_example(void);

/**
 * @brief sends the list.
 * @return int8_t SES return status code
 */
int32_t ses_test_scheduled_traffic_cycle_time_example(void);

/**
 * @brief sends the list.
 * @return int8_t SES return status code
 */
int32_t ses_test_scheduled_traffic_guard_band_example(void);

/**
 * @brief sends the list.
 * @return int8_t SES return status code
 */
int32_t ses_test_scheduled_traffic_main(void);

#endif /* INC_SES_TEST_SCHEDULED_TRAFFIC_H_ */
