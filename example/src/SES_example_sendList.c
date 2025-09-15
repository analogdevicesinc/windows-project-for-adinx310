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
#include "SES_example_sendlist.h"
#include "SES_sendList.h"
#include "SES_scheduled_traffic.h"
#include "SES_switch.h"
#include "SES_codes.h"
#include "SES_debug.h"



int32_t sesSendlist_Example(void) {
	int32_t rv = 0;

	/* Initialize send list */
	int32_t* frameID_A;
	int32_t* frameID_B;
	int32_t* frameID_C;
	int32_t* frameID_D;

	TSN_ieee802_dot1q_sched_gate_parameters_t gateParams;
	TSN_ieee802_dot1q_sched_gate_oper_parameters_t opergateParams;

	/* Port number for loopback port */
	TSN_ieee802_dot1q_types_port_number_t portNumber = 5; 

	/* 
	* example frame data, same DMAC for all, SMAC has AA, BB, CC, DD addresses to simplify visibility in 
	* wireshark example
	*/

	uint8_t frameData_A[] = { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0x11, 0x11, 0x11, 
            0x11, 0x11, 0xAA, 0x12, 0x34, 0x40, 0x64, 0x81, 0x00, 0x8F, 
            0xA7, 0x57, 0xF9, 0xFC, 0xF6, 0xF1, 0x1F, 0xFF, 0xD1, 0xA2, 
            0xDA, 0x4E, 0xDE, 0xC8, 0x84, 0xC1, 0xF6, 0x9E, 0x1F, 0xD8, 
            0xC9, 0x19, 0x53, 0x8E, 0x46, 0x44, 0x7A, 0xE3, 0xFC, 0x62, 
            0x08, 0xC9, 0x52, 0xA6, 0x02, 0x2E, 0x89, 0x21, 0xDC, 0x85, 
            0x4B };
	uint8_t frameData_B[] = { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0x11, 0x22, 0x22, 
            0x22, 0x22, 0xBB, 0x56, 0x78, 0x40, 0x64, 0x81, 0x00, 0x8F, 
            0xA7, 0x57, 0xF9, 0xFC, 0xF6, 0xF1, 0x1F, 0xFF, 0xD1, 0xA2, 
            0xDA, 0x4E, 0xDE, 0xC8, 0x84, 0xC1, 0xF6, 0x9E, 0x1F, 0xD8, 
            0xC9, 0x19, 0x53, 0x8E, 0x46, 0x44, 0x7A, 0xE3, 0xFC, 0x62, 
            0x08, 0xC9, 0x52, 0xA6, 0x02, 0x2E, 0x89, 0x21, 0xDC, 0x85, 
            0x4B, 0x16, 0x70, 0x22, 0xF5 };
	uint8_t frameData_C[] = { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0x11, 0x33, 0x33, 
            0x33, 0x33, 0xCC, 0x43, 0x21, 0x40, 0x64, 0x81, 0x00, 0x8F, 
            0xA7, 0x57, 0xF9, 0xFC, 0xF6, 0xF1, 0x1F, 0xFF, 0xD1, 0xA2, 
            0xDA, 0x4E, 0xDE, 0xC8, 0x84, 0xC1, 0xF6, 0x9E, 0x1F, 0xD8, 
            0xC9, 0x19, 0x53, 0x8E, 0x46, 0x44, 0x7A, 0xE3, 0xFC, 0x62, 
            0x08, 0xC9, 0x52, 0xA6, 0x02, 0x2E, 0x89, 0x21, 0xDC, 0x85, 
            0x4B, 0x16, 0x70, 0x22, 0xF5 };
	uint8_t frameData_D[] = { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0x11, 0x44, 0x44, 
            0x44, 0x44, 0xDD, 0x78, 0x65, 0x40, 0x64, 0x81, 0x00, 0x8F, 
            0xA7, 0x57, 0xF9, 0xFC, 0xF6, 0xF1, 0x1F, 0xFF, 0xD1, 0xA2, 
            0xDA, 0x4E, 0xDE, 0xC8, 0x84, 0xC1, 0xF6, 0x9E, 0x1F, 0xD8, 
            0xC9, 0x19, 0x53, 0x8E, 0x46, 0x44, 0x7A, 0xE3, 0xFC, 0x62, 
            0x08, 0xC9, 0x52, 0xA6, 0x02, 0x2E, 0x89, 0x21, 0xDC, 0x85, 
            0x4B, 0x16, 0x70, 0x22, 0xF5, 0x24, 0x7B, 0x4A, 0x29, 0x82, 
            0xB7, 0x0F, 0x79, 0x2B, 0xD6, 0x26, 0x1B, 0x9B, 0x92, 0x56, 
            0x75, 0xD6, 0x26, 0x24, 0x82, 0x86, 0x06, 0x22, 0x80, 0x25, 
            0x53, 0xA5, 0x98, 0x9F, 0xFF, 0x6D, 0x6C, 0x22, 0x80, 0x25,
			0x53, 0xA5, 0x98, 0x9F, 0xFF, 0x6D, 0x6C, 0x22, 0x80, 0x25,
			0x53, 0xA5, 0x98, 0x9F, 0xFF, 0x6D, 0x6C, 0x22, 0x80, 0x25,
			0x53, 0xA5, 0x98, 0x9F, 0xFF, 0x6D, 0x6C, 0x22, 0x80 };
	
	/*
	* The function below disables MSTP on specific port (loopback port 5)
	*/
	// rv = SES_MstpEnableSpanningTreePort(6, false);

	/* 
	* Add a static table entry (or entries) to steer the traffic out intended port. No entry is required 
	* for loopback port 
	*/
	uint8_t macAddr_p[6] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc };
	int16_t vlanId = 0xFFF;

	/* Egress on Port3 */
	uint8_t portMap = 0x4;
	rv = SES_AddStaticTableEntry(&macAddr_p, vlanId, portMap);

	/* 
	* Initialize send list, identifying number of sublists, four in this case, with a repeat period of 
	* 100ms & loopback port of 5 
	*/
	rv = SES_SendListCreate(4, 100000000, portNumber);
	
	/* Create sublists, identify number of entries and time offset*/
	rv = SES_SublistCreate(0, 3, 0);
	rv = SES_SublistCreate(1, 2, 800000);
	rv = SES_SublistCreate(2, 2, 1600000);
	rv = SES_SublistCreate(3, 2, 2400000);
	
	/* Register send list frames with transmit priority */
	rv = SES_RegisterFrame(&frameID_A, sizeof(frameData_A), 1, 7);
	rv = SES_RegisterFrame(&frameID_B, sizeof(frameData_B), 1, 4);
	rv = SES_RegisterFrame(&frameID_C, sizeof(frameData_C), 1, 4);
	rv = SES_RegisterFrame(&frameID_D, sizeof(frameData_D), 1, 0);
	
	/* Add frame A to first entry of each sublist */
	rv = SES_AddFrameToSublist(frameID_A, 0, 0);
	rv = SES_AddFrameToSublist(frameID_A, 1, 0);
	rv = SES_AddFrameToSublist(frameID_A, 2, 0);
	rv = SES_AddFrameToSublist(frameID_A, 3, 0);
	
	/* Add frame B to second entry of sublist 0 and 2 */
	rv = SES_AddFrameToSublist(frameID_B, 0, 1);
	rv = SES_AddFrameToSublist(frameID_B, 2, 1);

	/* Add frame C to second entry of sublist 1 and 3 */
	rv = SES_AddFrameToSublist(frameID_C, 1, 1);
	rv = SES_AddFrameToSublist(frameID_C, 3, 1);

	/* Add frame D to third entry of sublist 0 */
	rv = SES_AddFrameToSublist(frameID_D, 0, 2);
	
	/* Set up schedule for loopback port (5), 800us schedule with three intervals */
	rv = SES_QbvGetGateParameters(portNumber, &opergateParams);
	uint64_t currentTimeSec = opergateParams.current_time.seconds;
	uint32_t currentTimeNSec = opergateParams.current_time.nanoseconds;
	if (currentTimeNSec > 500000000) {
	currentTimeSec += 1;
	}

	gateParams.gate_enabled = true;
	gateParams.config_change = true;
	gateParams.guard_band_gate_event = false;
	gateParams.guard_band_hold_event = false;
	gateParams.admin_gate_states = 255;
	gateParams.admin_control_list[0].operation_name = TSN_ieee802_dot1q_sched_set_gate_states;
	gateParams.admin_control_list[0].time_interval_value = 200000;
	gateParams.admin_control_list[0].gate_state_value = 0x80; 
	gateParams.admin_control_list[0].tcu_state_value = 0;
	gateParams.admin_control_list[1].operation_name = TSN_ieee802_dot1q_sched_set_gate_states;
	gateParams.admin_control_list[1].time_interval_value = 200000;
	gateParams.admin_control_list[1].gate_state_value = 0x10;
	gateParams.admin_control_list[1].tcu_state_value = 0;
	gateParams.admin_control_list[2].operation_name = TSN_ieee802_dot1q_sched_set_gate_states;
	gateParams.admin_control_list[2].time_interval_value = 200000;
	gateParams.admin_control_list[2].gate_state_value = 0x01;
	gateParams.admin_control_list[2].tcu_state_value = 0;
	gateParams.admin_control_list[3].operation_name = TSN_ieee802_dot1q_sched_set_gate_states;
	gateParams.admin_control_list[3].time_interval_value = 0;
	gateParams.admin_control_list[3].gate_state_value = 0x00;
	gateParams.admin_control_list[3].tcu_state_value = 0;
	gateParams.admin_cycle_time.numerator = 8;
	gateParams.admin_cycle_time.denominator = 10000;
	gateParams.admin_cycle_time_extension = 0;
	gateParams.admin_base_time.seconds = currentTimeSec + 1;
	gateParams.admin_base_time.nanoseconds = 0;

	/* Set schedule for loopback port */
	rv = SES_QbvSetGateParameters(portNumber, &gateParams);

	/* Update send list frames */
	rv = SES_UpdateRegisteredFrame(frameID_A, 1, sizeof(frameData_A), &frameData_A);
	rv = SES_UpdateRegisteredFrame(frameID_B, 1, sizeof(frameData_B), &frameData_B);
	rv = SES_UpdateRegisteredFrame(frameID_C, 1, sizeof(frameData_C), &frameData_C);
	rv = SES_UpdateRegisteredFrame(frameID_D, 1, sizeof(frameData_D), &frameData_D);

	/* Start send list */
	rv = SES_SendListStart(3200000);

	/* Example of stopping one registered frame, to stop a sendlist, call this API for each frame */
	rv = SES_StopRegisteredFrame(frameID_A);
	
	printf("ses_example_sendlist :: %d\n\r", rv);

	return rv;
}
