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


#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "SES_psfp.h"
#include "SES_codes.h"
#include "SES_switch.h"
#include "TSN_ieee802_dot1q_psfp.h"
#include "SES_configuration.h"

/* Apply stream filter to specific traffic */
int32_t sesStreamFilter_Example(void) {

	int rv;
	int32_t index_p;
	TSN_ieee802_dot1q_psfp_stream_filter_instance_table_config_t streamFilterInstanceTable;

	/* Clear the contents of the structure before configuring */
	memset(&streamFilterInstanceTable, 0, sizeof(TSN_ieee802_dot1q_psfp_stream_filter_instance_table_config_t));

	/* Configure SES to enable stream Filter on Port 2 */

	/* port to apply rx filter at Port 2 */
	SES_mac_t mac = SES_macPort2; 

	/* priority for ingressing frames (wildcard - 0xFF) */
	uint32_t pcp = 0x04; 

	/* Egress port chosen in Port3 of the ADINx310 switch */
	uint8_t portMap = 0x08; 

	/* vlan ID of ingressing stream */
	uint16_t VID = 1; 

	/* Destination mac address of ingressing stream */
	uint8_t macAddr[6] = { 0x00, 0x00, 0x00, 0x00, 0x22, 0x22 };
	uint8_t macMask[6] = { NULL };

	/* Get available stream gate ID for Port2 */
	uint8_t rxStreamGateIndex = SES_PSFP_GetStreamGateIndex(0x04); 
	
	/* Get available stream filter ID for Port2 */
	uint8_t rxFilterIndex = SES_PSFP_GetStreamFilterIndex(0x04); 

	/* Install entry as Store & Forward required for PSFP function to work */
	uint8_t cutThrough = 0; 
	rv = SES_AddStaticTableEntryEx(1, &macAddr, &macMask, VID,
		SES_DYNTBL_VLAN_EXACT_MATCH, 0, 0, 0,
		0, SES_dynamicTblLookupBasic, portMap, 0,
		0, cutThrough, 0, 0,
		dynamicTblNoSequenceOp, 0, SES_IGNORE_FIELD, rxFilterIndex,
		&index_p);

	/* Enable VID 1 for all ports or only for ports of interest) */
	rv = SES_SetVlanMode(VID, 0xFFF);

	/* Configure the stream filter and stream gates */

	/* filterIndex */
	streamFilterInstanceTable.stream_filter_instance_id = rxFilterIndex;

	/* pcp, priority of traffic */
	streamFilterInstanceTable.priority_spec_type.priority_spec = pcp; 

	/* streamID */
	streamFilterInstanceTable.stream_handle_spec.stream_handle = rxFilterIndex;

	/* maxSDU = 850 byte */
	streamFilterInstanceTable.max_sdu_size = 850; 

	/* blockEnable, disabled */
	streamFilterInstanceTable.stream_blocked_due_to_oversize_frame_enabled = 0;

	/* flowMeterID, no flow meter associated with this stream filter */
	streamFilterInstanceTable.flow_meter_ref = 0xFF;

	/* gateID, no stream gate associated with this stream filter */
	streamFilterInstanceTable.stream_gate_ref = 0xFF; 
	
	
	rv = SES_PSFP_SetStreamFilterActive(mac, &streamFilterInstanceTable);
	printf("sesStreamFilter_Example :: %d\n", rv);

	return rv;
}

/* Apply stream filter and stream gate to specific traffic */
int32_t sesStreamGate_Example(void) {

	int rv;
	int32_t index_p;
	TSN_ieee802_dot1q_psfp_stream_filter_instance_table_config_t streamFilterInstanceTable;
	TSN_ieee802_dot1q_psfp_stream_gate_instance_table_config_t streamGateInstanceTable;

	/* Clear the contents of the structure before configuring */
	memset(&streamFilterInstanceTable, 0, sizeof(TSN_ieee802_dot1q_psfp_stream_filter_instance_table_config_t));
	memset(&streamGateInstanceTable, 0, sizeof(TSN_ieee802_dot1q_psfp_stream_gate_instance_table_config_t));

	/* Configure SES to enable stream Filter on Port 2 */

	/* port to apply rx filter at Port 2 */
	SES_mac_t mac = SES_macPort2;

	/* priority for ingressing frames (wildcard - 0xFF) */
	uint32_t pcp = 0x04; 
	
	/* Egress port, Port 3 */
	uint8_t portMap = 0x08; 

	/* vlan ID of ingressing stream, VLAN ID 1 */
	uint16_t VID = 1; 

	/* Destination mac address of ingressing stream */
	uint8_t macAddr[6] = { 0x00, 0x00, 0x00, 0x00, 0x22, 0x22 };
	uint8_t macMask[6] = { NULL };

	/* Get available stream filter ID for Port2 */
	uint8_t rxFilterIndex = SES_PSFP_GetStreamFilterIndex(0x04); 

	/* Get available stream gate ID for Port2 */
	uint8_t rxStreamGateIndex = SES_PSFP_GetStreamGateIndex(0x04); 

	/* Install entry as Store & Forward required for PSFP function to work */
	uint8_t cutThrough = 0;

	/* 0xFF indicates to use existing traffic class for traffic */
	uint8_t ipv = 0xFF; 

	rv = SES_AddStaticTableEntryEx(1, &macAddr, &macMask, VID,
		SES_DYNTBL_VLAN_EXACT_MATCH, 0, 0, 0,
		0, SES_dynamicTblLookupBasic, portMap, 0,
		0, cutThrough, 0, 0,
		dynamicTblNoSequenceOp, 0, SES_IGNORE_FIELD, rxFilterIndex,
		&index_p);

	/* Enable VID 1 for all ports or only for ports of interest */
	rv = SES_SetVlanMode(VID, 0xFFF); 

	/* Configure the stream filter */

	/* Stream filter Index */
	streamFilterInstanceTable.stream_filter_instance_id = rxFilterIndex; 
	
	/* pcp, traffic class */
	streamFilterInstanceTable.priority_spec_type.priority_spec = pcp;

	/* streamID */
	streamFilterInstanceTable.stream_handle_spec.stream_handle = rxFilterIndex; 

	/* MaxSDU = 850 bytes */
	streamFilterInstanceTable.max_sdu_size = 850; 

	/* blockEnable */
	streamFilterInstanceTable.stream_blocked_due_to_oversize_frame_enabled = 0; 

	/* flowMeterID, 0xFF indicates no flowmeter associated */
	streamFilterInstanceTable.flow_meter_ref = 0xFF;

	/* gateID */
	streamFilterInstanceTable.stream_gate_ref = rxStreamGateIndex; 

	/* Close gate if Octets Exceeded, disabled */
	streamGateInstanceTable.gate_closed_due_to_octets_exceeded_enable = 0;

	/* Close gate if frames received while gate is closed, disabled */
	streamGateInstanceTable.gate_closed_due_to_invalid_rx_enable = false;

	/* Open all the gates */
	streamGateInstanceTable.admin_cycle_time.numerator = 1;

	/* 1ms Cycle Time */
	streamGateInstanceTable.admin_cycle_time.denominator = 1000; 
	streamGateInstanceTable.config_change = true;

	/* Priority for ingressing frames, pass 0xFF as wildcard */
	streamGateInstanceTable.admin_ipv = 0x4;
	streamGateInstanceTable.gate_enable = true;
	streamGateInstanceTable.admin_gate_states = true;
	streamGateInstanceTable.admin_control_list_length = 2;

	/* octetInterval1Enable */
	streamGateInstanceTable.admin_control_list[0].octet_interval_enable = 0; 

	/* ipv set, use to reprioritize traffic class to different gate */
	streamGateInstanceTable.admin_control_list[0].ipv_spec = ipv; 

	/* gateOpen */
	streamGateInstanceTable.admin_control_list[0].gate_state_value = 1;

	/* Time interval value, 100us */
	streamGateInstanceTable.admin_control_list[0].time_interval_value = 100000; 

	/* Interval Octet Max */
	streamGateInstanceTable.admin_control_list[0].interval_octet_max = 0; 
	
	/* octetInterval1Enable */
	streamGateInstanceTable.admin_control_list[1].octet_interval_enable = 0;

	/* ipv set, use to reprioritize traffic class to different gate */
	streamGateInstanceTable.admin_control_list[1].ipv_spec = ipv; 

	/* gate closed */
	streamGateInstanceTable.admin_control_list[1].gate_state_value = 0; 

	/* Time Interval value, 900us */
	streamGateInstanceTable.admin_control_list[1].time_interval_value = 900000;

	/* Interval Octet Max */
	streamGateInstanceTable.admin_control_list[1].interval_octet_max = 0;
	rv = SES_PSFP_SetStreamFilterActive(mac, &streamFilterInstanceTable);
	rv = SES_PSFP_SetStreamGateActive(mac, &streamGateInstanceTable);
	printf("sesStreamGate_Example :: %d\n", rv);

	return rv;
}

/* Apply flow meter to allow a certain amount of traffic per unit time*/
int32_t sesFlowMeter_Example(void) {

	int rv;
	int32_t index_p;
	TSN_ieee802_dot1q_psfp_stream_filter_instance_table_config_t streamFilterInstanceTable;
	TSN_ieee802_dot1q_psfp_flow_meter_instance_table_config_t flowMeterInstanceTable;

	/* Clear the contents of the structure before configuring */
	memset(&streamFilterInstanceTable, 0, sizeof(TSN_ieee802_dot1q_psfp_stream_filter_instance_table_config_t));
	memset(&flowMeterInstanceTable, 0, sizeof(TSN_ieee802_dot1q_psfp_flow_meter_instance_table_config_t));

	/* Configure SES to enable stream Filter on Port 2 */

	/* port to apply rx filter at Port 2 */
	SES_mac_t mac = SES_macPort2;

	/* priority for ingressing frames (wildcard - 0xFF) */
	uint32_t pcp = 0x04;

	/* Egress port, Port 3 */
	uint8_t portMap = 0x08;

	/* vlan ID of ingressing stream */
	uint16_t VID = 1;

	/* Destination mac address of ingressing stream */
	uint8_t macAddr[6] = { 0x00, 0x00, 0x00, 0x00, 0x22, 0x22 };
	uint8_t macMask[6] = { NULL };

	/* Get available stream filter ID for Port */
	uint8_t rxFilterIndex = SES_PSFP_GetStreamFilterIndex(0x4);
	uint8_t rxFlowMeterIndex = SES_PSFP_GetFlowMeterIndex(0x4);

	/* Get available stream gate ID for Port2 */
	uint8_t rxStreamGateIndex = SES_PSFP_GetStreamGateIndex(0x04); 

	/* Install entry as Store & Forward required for PSFP function to work */
	uint8_t cutThrough = 0;

	/* Set port flow meter wait time, hardware default 80 (0x50), 10000 or 0x2710 */
	uint16_t waitTime = 0x2710;
	rv = SES_AddStaticTableEntryEx(1, &macAddr, &macMask, VID, SES_DYNTBL_VLAN_EXACT_MATCH, 0, 0, 0,
		0, SES_dynamicTblLookupBasic, portMap, 0, 0, cutThrough, 0, 0, dynamicTblNoSequenceOp, 0, SES_IGNORE_FIELD, rxFilterIndex,
		&index_p);

	/* Enable VID 1 for all ports or only for ports of interest) */
	rv = SES_SetVlanMode(VID, 0xFFF); 

	/* Configure the stream filter */

	/* filterIndex */
	streamFilterInstanceTable.stream_filter_instance_id = rxFilterIndex;

	/*  pcp, priority of traffic */
	streamFilterInstanceTable.priority_spec_type.priority_spec = pcp;

	/* StreamID */
	streamFilterInstanceTable.stream_handle_spec.stream_handle = rxFilterIndex;

	/* maxSDU = 850 bytes */
	streamFilterInstanceTable.max_sdu_size = 850;

	/* blockEnable, disabled */
	streamFilterInstanceTable.stream_blocked_due_to_oversize_frame_enabled = 0;

	/* flowMeterID */
	streamFilterInstanceTable.flow_meter_ref = rxFlowMeterIndex;

	/* stream gateID, no gate associated (0xFF) */
	streamFilterInstanceTable.stream_gate_ref = 0xFF;
	
	/* Configure the flow meter
	* CIR register bytes per flow meter period (flow meter waitTime*8ns),
	* for waitTime = 80 (hardware default), a CIR value = 1 corresponds to 12.5Mbps
	* for waitTime = 10000, a CIR value = 1 corresponds to 100kbps 
	*/

	/* Rate at which tokens are added to commit bucket */
	flowMeterInstanceTable.committed_information_rate = 1;

	/* Maximum capacity of commit bucket */
	flowMeterInstanceTable.comitted_burst_size = 1500;
	flowMeterInstanceTable.commit_bucket_tokens = 0;

	/* Rate at which tokens are added to excess bucket */
	flowMeterInstanceTable.excess_information_rate = 0;

	/* Maximum capacity of excess bucket */
	flowMeterInstanceTable.excess_burst_size = 0;

	/* Color mode, 0= Color Aware, 1 = color blind */
	flowMeterInstanceTable.color_mode = 0;

	/* No coupling of commit overflow tokens to excess bucket */
	flowMeterInstanceTable.coupling_flag = 0;

	/* Drop on Yellow, false = forward yellow frames, true = drop yellow frames */
	flowMeterInstanceTable.drop_on_yellow = false; 
	rv = SES_PSFP_SetFlowMeterWaitTime(mac, waitTime);
	rv = SES_PSFP_SetFlowMeterActive(mac, &flowMeterInstanceTable);
	rv = SES_PSFP_SetStreamFilterActive(mac, &streamFilterInstanceTable);

	printf("sesFlowMeter_Example :: %d\n", rv);

	return rv;
}

/* Read PSFP statistics */
int32_t sesReadPsfpStatistics_Example(void) {
	int rv;
	SES_mac_t mac = SES_macPort2;
	SES_psfpStatsFilterSdu_t destFilterSdu;
	SES_psfpStatsGate_t destGate;
	SES_psfpStatsFilterMatchMeter_t destFilterMatchMeter;
	rv = SES_PSFP_GetStats(mac, &destFilterSdu, &destGate, &destFilterMatchMeter);
	printf("sesReadPsfpStatistics_Example :: %d\n", rv);
	return rv;
}

/* Reprioritize PCP of ingressing frames */
int32_t sesIpvReprioritize_Example(void) {
	int rv;
	int32_t index_p;
	TSN_ieee802_dot1q_psfp_stream_filter_instance_table_config_t streamFilterInstanceTable;
	TSN_ieee802_dot1q_psfp_stream_gate_instance_table_config_t streamGateInstanceTable;

	/* Clear the contents of the structure before configuring */
	memset(&streamFilterInstanceTable, 0, sizeof(TSN_ieee802_dot1q_psfp_stream_filter_instance_table_config_t));
	memset(&streamGateInstanceTable, 0, sizeof(TSN_ieee802_dot1q_psfp_stream_gate_instance_table_config_t));

	// Configure SES to enable stream Filter on Port 2
	SES_mac_t mac = SES_macPort2; //port to apply rx filter at Port 2
	uint32_t pcp = 0x04; //priority for ingressing frames (wildcard - 0xFF)
	uint8_t portMap = 0x08; //Egress port, Port 3
	uint16_t VID = 1; //vlan ID of ingressing stream, VLAN ID 1
	uint8_t macAddr[6] = { 0x00, 0x00, 0x00, 0x00, 0x22, 0x22 };//Destination mac address of ingressing stream
	uint8_t macMask[6] = { NULL };
	uint8_t rxFilterIndex = SES_PSFP_GetStreamFilterIndex(0x04); //Get available stream filter ID for Port2
	uint8_t rxStreamGateIndex = SES_PSFP_GetStreamGateIndex(0x04); //Get available stream gate ID for Port2
	uint8_t cutThrough = 0; //Install entry as Store & Forward required for PSFP function to work
	uint8_t ipv = 0xFF; //0xFF indicates to use existing traffic class for traffic
	rv = SES_AddStaticTableEntryEx(1, &macAddr, &macMask, VID,
			SES_DYNTBL_VLAN_EXACT_MATCH, 0, 0, 0,
			0, SES_dynamicTblLookupBasic, portMap, 0,
			0, cutThrough, 0, 0,
			dynamicTblNoSequenceOp, 0, SES_IGNORE_FIELD, rxFilterIndex,
			&index_p);
	rv = SES_SetVlanMode(VID, 0xFFF); // Enable VID 1 for all ports or only for ports of interest)
	/* Configure the stream filter */
	streamFilterInstanceTable.stream_filter_instance_id = rxFilterIndex; // Stream filter Index
	streamFilterInstanceTable.priority_spec_type.priority_spec = pcp; // pcp, traffic class
	streamFilterInstanceTable.stream_handle_spec.stream_handle = rxFilterIndex; // streamID
	streamFilterInstanceTable.max_sdu_size = 850; //MaxSDU = 850 bytes
	streamFilterInstanceTable.stream_blocked_due_to_oversize_frame_enabled = 0; // blockEnable
	streamFilterInstanceTable.flow_meter_ref = 0xFF; // flowMeterID, 0xFF indicates no flowmeter associated
	streamFilterInstanceTable.stream_gate_ref = rxStreamGateIndex; // gateID
	streamGateInstanceTable.gate_closed_due_to_octets_exceeded_enable = 0;// Close gate if Octets Exceeded, disabled
	streamGateInstanceTable.gate_closed_due_to_invalid_rx_enable = false;// Close gate if frames received while gate is closed, disabled

	/* Open all the gates */
	streamGateInstanceTable.admin_cycle_time.numerator = 1;
	streamGateInstanceTable.admin_cycle_time.denominator = 1000; // 1ms Cycle Time
	streamGateInstanceTable.config_change = true; 
	streamGateInstanceTable.admin_ipv = 0x4; // Priority for ingressing frames, pass 0xFF as wildcard
	streamGateInstanceTable.gate_enable = true; 
	streamGateInstanceTable.admin_gate_states = true;

	streamGateInstanceTable.admin_control_list_length = 2;
	streamGateInstanceTable.admin_control_list[0].octet_interval_enable = 0; // octetInterval1Enable
	streamGateInstanceTable.admin_control_list[0].ipv_spec = ipv; // ipv set, use to reprioritize traffic class to different gate
	streamGateInstanceTable.admin_control_list[0].gate_state_value = 1; // gateOpen
	streamGateInstanceTable.admin_control_list[0].time_interval_value = 100000; // Time interval value, 100us
	streamGateInstanceTable.admin_control_list[0].interval_octet_max = 0; // Interval Octet Max
	streamGateInstanceTable.admin_control_list[1].octet_interval_enable = 0; // octetInterval1Enable
	streamGateInstanceTable.admin_control_list[1].ipv_spec = ipv; // ipv set, use to reprioritize traffic class to different gate
	streamGateInstanceTable.admin_control_list[1].gate_state_value = 0; // gate closed
	streamGateInstanceTable.admin_control_list[1].time_interval_value = 900000;// Time Interval value, 900us
	streamGateInstanceTable.admin_control_list[1].interval_octet_max = 0; // Interval Octet Max

	rv = SES_PSFP_SetStreamFilterActive(mac, &streamFilterInstanceTable);
	rv = SES_PSFP_SetStreamGateActive(mac, &streamGateInstanceTable);
	
	return rv;
}

void sesPsfp_Example(void) {

	/* 
	* 1: Stream Filter Example();
	* 2: Stream Gate Example();
	* 3: Flow Meter Example();
	*/
	
	switch (PSFP) {

	case 1:
		printf("PSFP Stream Filter Example\n");
		sesStreamFilter_Example();
		break;
	
	case 2:
		printf("PSFP Stream Gate Example\n");
		sesStreamGate_Example();
		break;
	
	case 3:
		printf("PSFP Flow Meter Example\n");
		sesFlowMeter_Example();
		break;

	default:
		printf("ERROR: Wrong input, please check SES_configuration.h!!!\n");
		break;

	}
}