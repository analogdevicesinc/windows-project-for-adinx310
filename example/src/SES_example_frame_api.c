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

#include "SES_example_frame_api.h"
#include "SES_frame_api.h"
#include "SES_codes.h"
#include "SES_debug.h"
#include "SES_configuration.h"

/* Example of static entry forwarding frames to Packet Assist Engine */
void sesL2ReceiveFrameStaticEntry_Example() {
	int32_t rv = SES_OK;
	/*Attribute of interest*/
	uint32_t portAttribute = SES_REQUEST_PORT_ATTRIBUTE;
	/*Frames requested with this MAC address*/
	uint8_t macAddr[6] = { 0x00, 0x00, 0x00, 0x11, 0x11, 0x11 };
	/*low priority = 0, entry will be placed towards bottom of table*/
	uint8_t lookupPriority = 0;
	uint8_t macMask[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	int16_t vlanId = 0xFFF;
	uint16_t vlanMask = 0xFFF;
	uint8_t sourceEntry = 0;
	uint8_t override = 0;
	uint8_t sourceOverride = 0;
	uint8_t hsrOrPrpSupervisory = 0;
	SES_dynTblLookup_t lookupType = SES_dynamicTblLookupBasic;
	uint8_t portMap = 0x00; 
	/*Set to 1 to send to Assist Engine*/
	uint8_t sendToAE = 1;
	uint8_t danp = 0;
	/*Store and Forward mode*/
	uint8_t cutThrough = 0;
	/*ADI use only, set to 0*/
	uint8_t syntTimestamp = 0;
	/*ADI use only, set to 0*/
	uint8_t localTimestamp = 0;
	/*SET TO dynamicTblNoSequenceOp*/
	SES_dynTblSeqMgmt_t sequenceMgmt = dynamicTblNoSequenceOp;
	/*NOT CURRENTLY USED, SET TO 0*/
	int rxSequenceSet = 0; 
	/* SET TO -1*/
	int transmitFilter = SES_IGNORE_FIELD;
	/*  SET TO -1*/
	int receiveFilter = SES_IGNORE_FIELD;
	int index;
	printf( "Adding Static Entry :: %d\n",SES_AddStaticTableEntryEx(lookupPriority,
		&macAddr, &macMask,
		vlanId,
		vlanMask,
		sourceEntry,
		override,
		sourceOverride,
		hsrOrPrpSupervisory,
		lookupType,
		portMap,
		sendToAE,
		danp,
		cutThrough,
		syntTimestamp,
		localTimestamp,
		sequenceMgmt,
		rxSequenceSet,
		transmitFilter,
		receiveFilter,
		&index));
}

/* Example of callback printing received frames */
void sesL2RxCallback_Example(int32_t frameLength, uint8_t* frame_p, SES_frameAttributes_t* frameAttributes_p) {

	printf("Packet Received!!! %d\n", frameLength);
	printf("Received Packet :: \n");
	for (int i = 0; i < frameLength; i++) {
		/*Print each element in hexadecimal format*/
		printf("%02X ", frame_p[i]); 
	}
	printf("\n");
}

/*Example of transmitting a frame out on all ports*/
int32_t sesL2Transmit_Example() {
	int32_t rv = SES_OK;
	uint8_t pkt_p[] = { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0x22, 0x22, 0x22,
						0x22, 0x22, 0x22, 0xaa, 0xc5, 0x40, 0x64, 0x81, 0x00, 0x8F,
						0xA7, 0x57, 0xF9, 0xFC, 0xF6, 0xF1, 0x1F, 0xFF, 0xD1, 0xA2,
						0xDA, 0x4E, 0xDE, 0xC8, 0x84, 0xC1, 0xF6, 0x9E, 0x1F, 0xD8,
						0xC9, 0x19, 0x53, 0x8E, 0x46, 0x44, 0x7A, 0xE3, 0xFC, 0x62,
						0x08, 0xC9, 0x52, 0xA6, 0x02, 0x2E, 0x89, 0x21, 0xDC, 0x85,
						0x4B, 0x16, 0x70, 0x22, 0xF5, 0x24, 0x7B, 0x4A, 0x29, 0x82,
						0xB7, 0x0F, 0x79, 0x2B, 0xD6, 0x26, 0x1B, 0x9B, 0x92, 0x56,
						0x75, 0xD6, 0x26, 0x24, 0x82, 0x86, 0x06, 0x22, 0x80, 0x25,
						0x53, 0xA5, 0x98, 0x9F, 0xFF, 0x6D, 0x6C };

	SES_transmitFrameData_t txData_p = {
		.frameType = SES_standardFrame,
		.data_p = &pkt_p,
		.byteCount = sizeof(pkt_p),
		.cb_p = 0,
		.cbParam_p = 0,
		.ses = {
			.generateFcs = 1,
			.xmitPriority = 2,
			.egressPortMap = 0xFF,
			.transformId = SES_NO_TRANSFORM,
			.attributeRequest = 0
		}
	};
	rv = SES_XmitFrame(&txData_p);
	return rv;
}

int32_t sesRxSesFramesByMac_Example() {
	int32_t rv = SES_OK;
	uint8_t macAddress_g[6] = { 0x00, 0x00, 0x00, 0x11, 0x11, 0x11 };
	uint32_t attributeRequest = SES_REQUEST_FREERUN_TIMESTAMP_ATTRIBUTE;

	/*Static entry is required to send the packets to AE*/
	sesL2ReceiveFrameStaticEntry_Example();

	rv = SES_RxSesFramesByMac(macAddress_g, attributeRequest, sesL2RxCallback_Example);
	printf("Requesting L2 Packet Receive by MAC Address :: %d\n", rv);

	while (1) {
		Sleep(30);
	}

	return rv;
}

/* Retrieve the Frames with the specified ethertype and data received at a SES port
 * will be returned to the callback function with the requested attribute data.
 * NOTE : Maximum of 3 distinct matches can be performed apart from the ethertype
 *        using the SES_matchData_t
 */
/*In the below example, the ethertype will be matched along with the data1, data2 and data3 post ethertype data  */
int32_t sesRxSesFramesByEtype_Example(void) {
	int32_t rv = SES_OK;
	const uint8_t data1[] = { 0xaa };
	const uint8_t data2[] = { 0xbb };
	const uint8_t data3[] = { 0xcc };

	const uint8_t mask[] = { 0xff };

	uint16_t ethertype = 0x1234;
	uint16_t ethertypeMask = 0xffff;
	uint8_t matchCount = 3;
	SES_matchData_t matchData_p[] = { {1, data1, mask, 0}, {1, data2, mask, 1}, {1, data3, mask, 2} };
	uint32_t attributeRequest = SES_REQUEST_PORT_ATTRIBUTE;

	/*Static entry is required to send the packets to AE*/
	sesL2ReceiveFrameStaticEntry_Example();

	rv = SES_RxSesFramesByEtype(ethertype, ethertypeMask, matchCount, matchData_p, attributeRequest, sesL2RxCallback_Example);
	printf("L2 Packet Receive by Ethertype along with other matches :: %d\n", rv); 

	while (1) {
		Sleep(30);
	}
	return rv;

}

/* Retrieve the Layes 2 packets from a desiganated Ethertype from a MAC */
int32_t sesRxSesFramesByEtypeOnly_Example(void) {
	int32_t rv = SES_OK;
	uint16_t ethertype = 0x1234;
	uint32_t attributeRequest = SES_REQUEST_PORT_ATTRIBUTE;

	/*Static entry is required to send the packets to AE */
	sesL2ReceiveFrameStaticEntry_Example();

	rv = SES_RxSesFramesByEtypeOnly(ethertype, attributeRequest, sesL2RxCallback_Example);
	printf("L2 Packet Receive by Ethertype Only :: %d\n", rv);

	while (1) {
		Sleep(30);
	}
	return rv;
}

/*Example of requesting frames with the specified DMAC received at the stack processor*/
int32_t sesRxStackProcessorFramesByMac_Example() {
	int32_t rv = SES_OK;
	uint8_t macAddress_g[6] = { 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 }; 

	rv = SES_RxStackProcessorFramesByMac(macAddress_g, sesL2RxCallback_Example);
	printf("Requesting L2 Packet Receive by MAC :: %d\n", rv);

	while (1) {
		Sleep(30);
	}
	return rv;
}

/*Example of requesting frames with the specified ethertype received at the stack processor*/
int32_t sesRxStackProcessorFramesByEtype_Example() {
	int32_t rv = SES_OK;
	/*Frames requested with this Ethertype*/
	uint16_t ethertype = 0x1234; 

	rv = SES_RxStackProcessorFramesByEtype(ethertype, sesL2RxCallback_Example); 
	printf("SES_RxStackProcessorFramesByEtype rv :: %d\n", rv);

	while (1) {
		Sleep(30);
	}
	return rv;
}

void seslayer2_Example() {

	switch (LAYER_2) {

	case 1:
		printf("Layer2 Transmit Example \n");
		sesL2Transmit_Example();
		break;

	case 2:
		printf("Layer2 packet received by Stack Processor with matching MAC Example\n");
		sesRxStackProcessorFramesByMac_Example(); 
		
		break;

	case 3: 
		printf("Layer2 packet received by Stack Processor with matching Ethertype Example\n");
		sesRxStackProcessorFramesByEtype_Example(); 
		break;
		

	case 4:
		printf("Layer2 packet received with matching Ethertype Example\n");
		sesRxSesFramesByEtypeOnly_Example(); 
		break;
	
	case 5:
		printf("Layer2 packet received with matching MAC Example\n");
		sesRxSesFramesByMac_Example();
		break;

	default:
		printf("Invalid Input !! ");
		break;
	}

}