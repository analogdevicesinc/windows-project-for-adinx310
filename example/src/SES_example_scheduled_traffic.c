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


#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "SES_example_scheduled_traffic.h"
#include "SES_scheduled_traffic.h"
#include "SES_switch.h"
#include "SES_codes.h"
#include "SES_debug.h"


static int32_t sesQbvGetQueueMaxSduTable_Example(void);
static int32_t sesQbvSetQueueMaxSduTable_Example(void);
static int32_t sesQbvGetGateParameters_Example(void);
static int32_t sesQbvSetGateParameters_Example(void);
static int32_t sesQbvGetStats_Example(void);


int32_t sesScheduledTrafficTimer_Example(void) {
	int32_t rv = 0;

	SES_gpioTimerConfig_t config;
	config.gpioConfig.state = 1;
	config.timerMode = SES_timerModeTsnOut;

	rv = SES_SetGpioTimerConfig(SES_gpio4, &config);
	rv = SES_SetGpioTimerConfig(SES_gpio5, &config);
	rv = SES_SetGpioTimerConfig(SES_gpio7, &config);

	TSN_ieee802_dot1q_types_port_number_t portNumber = 6;
	TSN_ieee802_dot1q_sched_gate_parameters_t gateParam;
	gateParam.gate_enabled = true;
	gateParam.config_change = true;
	gateParam.guard_band_gate_event = false;
	gateParam.guard_band_hold_event = false;
	gateParam.admin_gate_states = 255;
	gateParam.admin_control_list[0].operation_name = TSN_ieee802_dot1q_sched_set_gate_states;
	gateParam.admin_control_list[0].time_interval_value = 100000;
	gateParam.admin_control_list[0].gate_state_value = 0x01;
	gateParam.admin_control_list[1].operation_name = TSN_ieee802_dot1q_sched_set_gate_states;
	gateParam.admin_control_list[1].time_interval_value = 100000;
	gateParam.admin_control_list[1].gate_state_value = 0x02;
	gateParam.admin_control_list[2].operation_name = TSN_ieee802_dot1q_sched_set_gate_states;
	gateParam.admin_control_list[2].time_interval_value = 100000;
	gateParam.admin_control_list[2].gate_state_value = 0x03;
	gateParam.admin_control_list[3].operation_name = TSN_ieee802_dot1q_sched_set_gate_states;
	gateParam.admin_control_list[3].time_interval_value = 100000;
	gateParam.admin_control_list[3].gate_state_value = 0x08;
	gateParam.admin_control_list[4].operation_name = TSN_ieee802_dot1q_sched_set_gate_states;
	gateParam.admin_control_list[4].time_interval_value = 100000;
	gateParam.admin_control_list[4].gate_state_value = 0x09;
	gateParam.admin_control_list[5].operation_name = TSN_ieee802_dot1q_sched_set_gate_states;
	gateParam.admin_control_list[5].time_interval_value = 100000;
	gateParam.admin_control_list[5].gate_state_value = 0x0A;
	gateParam.admin_control_list[6].operation_name = TSN_ieee802_dot1q_sched_set_gate_states;
	gateParam.admin_control_list[6].time_interval_value = 100000;
	gateParam.admin_control_list[6].gate_state_value = 0x0B;
	gateParam.admin_control_list[7].operation_name = TSN_ieee802_dot1q_sched_set_gate_states;
	gateParam.admin_control_list[7].time_interval_value = 0;
	gateParam.admin_control_list[7].gate_state_value = 0x00;
	gateParam.admin_cycle_time.numerator = 1;
	gateParam.admin_cycle_time.denominator = 1000;
	gateParam.admin_cycle_time_extension = 0;
	gateParam.admin_base_time.seconds = 0;
	gateParam.admin_base_time.nanoseconds = 0;

	rv = SES_QbvSetGateParameters(portNumber, &gateParam);
	printf("ses_test_scheduled_traffic_timer_example error code = %d\n\r", rv);
	return rv;
}


int32_t sesScheduledTrafficCycleTime_Example(void) {
	int32_t rv = 0;

	TSN_ieee802_dot1q_types_port_number_t portNumber = 2;
	TSN_ieee802_dot1q_sched_gate_parameters_t gateParam;
	gateParam.gate_enabled = true;
	gateParam.config_change = true;
	gateParam.guard_band_gate_event = false;
	gateParam.guard_band_hold_event = false;
	gateParam.admin_gate_states = 255;
	gateParam.admin_control_list[0].operation_name = TSN_ieee802_dot1q_sched_set_and_release_mac;
	gateParam.admin_control_list[0].time_interval_value = 300000;
	gateParam.admin_control_list[0].gate_state_value = 0xAA;
	gateParam.admin_control_list[1].operation_name = TSN_ieee802_dot1q_sched_set_and_release_mac;
	gateParam.admin_control_list[1].time_interval_value = 600000;
	gateParam.admin_control_list[1].gate_state_value = 0x55;
	gateParam.admin_control_list[2].operation_name = TSN_ieee802_dot1q_sched_set_and_release_mac;
	gateParam.admin_control_list[2].time_interval_value = 100000;
	gateParam.admin_control_list[2].gate_state_value = 0x80;
	gateParam.admin_control_list[3].operation_name = TSN_ieee802_dot1q_sched_set_and_release_mac;
	gateParam.admin_control_list[3].time_interval_value = 0;
	gateParam.admin_control_list[3].gate_state_value = 0;
	gateParam.admin_cycle_time.numerator = 1;
	gateParam.admin_cycle_time.denominator = 1000;
	gateParam.admin_cycle_time_extension = 500000;
	gateParam.admin_base_time.seconds = 50;
	gateParam.admin_base_time.nanoseconds = 0;

	rv = SES_QbvSetGateParameters(portNumber, &gateParam);
	printf("ses_test_scheduled_traffic_cycle_time_example error code = %d\n\r", rv);
	return rv;
}

int32_t sesScheduledTrafficGuardBand_Example(void) {
	int32_t rv = 0;

	TSN_ieee802_dot1q_types_port_number_t portNumber = 2;
	TSN_ieee802_dot1q_sched_gate_parameters_t gateParam;
	gateParam.gate_enabled = true;
	gateParam.config_change = true;
	gateParam.guard_band_gate_event = true;
	gateParam.guard_band_hold_event = true;
	gateParam.admin_gate_states = 255;
	gateParam.admin_control_list[0].operation_name = TSN_ieee802_dot1q_sched_set_and_release_mac;
	gateParam.admin_control_list[0].time_interval_value = 300000;
	gateParam.admin_control_list[0].gate_state_value = 0xAA;
	gateParam.admin_control_list[1].operation_name = TSN_ieee802_dot1q_sched_set_and_release_mac;
	gateParam.admin_control_list[1].time_interval_value = 600000;
	gateParam.admin_control_list[1].gate_state_value = 0x55;
	gateParam.admin_control_list[2].operation_name = TSN_ieee802_dot1q_sched_set_and_release_mac;
	gateParam.admin_control_list[2].time_interval_value = 100000;
	gateParam.admin_control_list[2].gate_state_value = 0x80;
	gateParam.admin_control_list[3].operation_name = TSN_ieee802_dot1q_sched_set_and_release_mac;
	gateParam.admin_control_list[3].time_interval_value = 0;
	gateParam.admin_control_list[3].gate_state_value = 0;
	gateParam.admin_cycle_time.numerator = 1;
	gateParam.admin_cycle_time.denominator = 1000;
	gateParam.admin_cycle_time_extension = 0;
	gateParam.admin_base_time.seconds = 0;
	gateParam.admin_base_time.nanoseconds = 0;

	rv = SES_QbvSetGateParameters(portNumber, &gateParam);
	printf("ses_test_scheduled_traffic_guard_band_example error code = %d\n\r", rv);
	Sleep(500);
	return rv;
}

int32_t sesScheduledTraffic_Main(void) {
	int32_t rv = 0;
	Sleep(20000);

	rv = sesQbvGetQueueMaxSduTable_Example();
	rv = sesQbvSetQueueMaxSduTable_Example();
	printf("rv - %d \n", rv);
	printf("ses_test_preemption_main error code = %d\n\r", rv);
	return rv;
}

int32_t sesQbvSetQueueMaxSduTable_Example(void) {
	int32_t rv = 0;
	TSN_ieee802_dot1q_types_port_number_t portNumber = 4;
	TSN_ieee802_dot1q_sched_queue_max_sdu_table_t queueMaxSduTable = { 1520, 1520, 1520, 1520, 1520, 1520, 1520, 1520 };
	rv = SES_QbvSetQueueMaxSduTable(portNumber, &queueMaxSduTable);
	return rv;
}

int32_t sesQbvGetQueueMaxSduTable_Example(void) {
	int32_t rv = 0;
	TSN_ieee802_dot1q_types_port_number_t portNumber = 4;
	TSN_ieee802_dot1q_sched_queue_max_sdu_table_t queueMaxSduTable_p;
	rv = SES_QbvGetQueueMaxSduTable(portNumber, &queueMaxSduTable_p);
	return rv;
}

int32_t sesQbvGetGateParameters_Example(void) {
	int32_t rv = 0;
	TSN_ieee802_dot1q_types_port_number_t portNumber = 4;
	TSN_ieee802_dot1q_sched_gate_parameters_t gateParam_p;
	rv = SES_QbvGetGateParameters(portNumber, &gateParam_p);
	return rv;
}

int32_t sesQbvSetGateParameters_Example(void) {
	int32_t rv = 0;

	TSN_ieee802_dot1q_types_port_number_t portNumber = 2;
	TSN_ieee802_dot1q_sched_gate_parameters_t gateParam;
	gateParam.gate_enabled = true;
	gateParam.config_change = true;
	gateParam.guard_band_gate_event = false;
	gateParam.guard_band_hold_event = false;
	gateParam.admin_gate_states = 255;
	gateParam.admin_control_list[0].operation_name = TSN_ieee802_dot1q_sched_set_and_release_mac;
	gateParam.admin_control_list[0].time_interval_value = 300000;
	gateParam.admin_control_list[0].gate_state_value = 0xAA;
	gateParam.admin_control_list[1].operation_name = TSN_ieee802_dot1q_sched_set_and_release_mac;
	gateParam.admin_control_list[1].time_interval_value = 600000;
	gateParam.admin_control_list[1].gate_state_value = 0x55;
	gateParam.admin_control_list[2].operation_name = TSN_ieee802_dot1q_sched_set_and_release_mac;
	gateParam.admin_control_list[2].time_interval_value = 100000;
	gateParam.admin_control_list[2].gate_state_value = 0x80;
	gateParam.admin_control_list[3].operation_name = TSN_ieee802_dot1q_sched_set_and_release_mac;
	gateParam.admin_control_list[3].time_interval_value = 0;
	gateParam.admin_control_list[3].gate_state_value = 0;
	gateParam.admin_cycle_time.numerator = 1;
	gateParam.admin_cycle_time.denominator = 1000;
	gateParam.admin_cycle_time_extension = 0;
	gateParam.admin_base_time.seconds = 0;
	gateParam.admin_base_time.nanoseconds = 0;

	rv = SES_QbvSetGateParameters(portNumber, &gateParam);
	return rv;
}

int32_t sesQbvGetStats_Example(void) {
	int32_t rv = 0;

	TSN_ieee802_dot1q_types_port_number_t portNumber = 1;
	SES_qbvStats_t qbvStats_p;
	rv = SES_QbvGetStats(portNumber, &qbvStats_p);
	return rv;
}