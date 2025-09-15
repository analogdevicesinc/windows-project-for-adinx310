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
#include "SES_example_logical_mac.h"
#include "SES_logical_mac.h"
#include "SES_codes.h"
#include "SES_debug.h"


static int32_t SES_rxlogicalmaccb(int32_t frameLength, uint8_t *frame_p, SES_frameAttributes_t *frameAttributes_p);
static int32_t SES_rxlogicalmaccb2(int32_t frameLength, uint8_t *frame_p, SES_frameAttributes_t *frameAttributes_p);
static int32_t sesTestAddLogicalMac_Example(void);
static int32_t sesTestDeleteLogicalMac_Example(void);
static int32_t sesTestConfigureLogicalMacFrame_Example(void);
static int32_t sesTestApplyForwardMask_Example(void);


int32_t sesTestLogicalMacTwoLogicalGroup_Example(void) {
	int32_t rv = 0;
	uint8_t portMap;
	int8_t LinkPort;
	uint8_t macAddress_g[6] = { 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };
	uint8_t macAddress_g2[6] = { 0x11, 0x12, 0x13, 0x14, 0x15, 0x17 };
	SES_logicalMacConfig_t logicalMacConfig, logicalMacConfig2;
	SES_logicalMacReturns_t logicalMacReturns, logicalMacReturns2;

	memcpy(&logicalMacConfig.logicalMac, macAddress_g, 6);
	logicalMacConfig.portMap = 0x3;
	logicalMacConfig.deviceLinkPort = 0;
	logicalMacConfig.rxLogicalMacCallback = SES_rxlogicalmaccb;
	rv = SES_AddLogicalMac(&logicalMacConfig, &logicalMacReturns);

	
	memcpy(&logicalMacConfig2.logicalMac, macAddress_g2, 6);
	logicalMacConfig2.portMap = 0x5;
	logicalMacConfig2.deviceLinkPort = 0;
	logicalMacConfig2.rxLogicalMacCallback = SES_rxlogicalmaccb2;
	rv = SES_AddLogicalMac(&logicalMacConfig2, &logicalMacReturns2);
	printf("test_SES_logical_mac_two_logical_group_example error code = %d\n\r", rv);
	return rv;
}


int32_t sesTestLogicalMacTwoByThreeLogicalGroup_Example(void) {
	int32_t rv = 0;
	uint8_t portMap;
	int8_t LinkPort;
	uint8_t macAddress_g[6] = { 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };
	uint8_t macAddress_g2[6] = { 0x11, 0x12, 0x13, 0x14, 0x15, 0x17 };
	SES_logicalMacConfig_t logicalMacConfig, logicalMacConfig2;
	SES_logicalMacReturns_t logicalMacReturns, logicalMacReturns2;

	memcpy(&logicalMacConfig.logicalMac, macAddress_g, 6);
	logicalMacConfig.portMap = 0x7;
	logicalMacConfig.deviceLinkPort = 0;
	logicalMacConfig.rxLogicalMacCallback = SES_rxlogicalmaccb;
	rv = SES_AddLogicalMac(&logicalMacConfig, &logicalMacReturns);

	memcpy(&logicalMacConfig2.logicalMac, macAddress_g2, 6);
	logicalMacConfig2.portMap = 0x38;
	logicalMacConfig2.deviceLinkPort = 3;
	logicalMacConfig2.rxLogicalMacCallback = SES_rxlogicalmaccb2;
	rv = SES_AddLogicalMac(&logicalMacConfig2, &logicalMacReturns2);
	printf("test_SES_logical_mac_two_by_three_logical_group_example error code = %d\n\r", rv);
	return rv;
}


int32_t sesTestLogicalMac_Example(void) {
	int32_t rv = 0;
	rv = sesTestAddLogicalMac_Example();
	printf("rv - %d \n", rv);
	rv = sesTestDeleteLogicalMac_Example();
	printf("rv - %d \n", rv);
	rv = sesTestConfigureLogicalMacFrame_Example();
	printf("rv - %d \n", rv);
	rv = sesTestApplyForwardMask_Example();
	printf("rv - %d \n", rv);
	

	printf("test_SES_logical_mac error code = %d\n\r", rv);
	return rv;
}

int32_t sesTestAddLogicalMac_Example(void) {
	int32_t rv = 0;
	uint8_t macAddress_g[6] = { 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };
	SES_logicalMacConfig_t logicalMacConfig;
	SES_logicalMacReturns_t logicalMacReturns;
	memcpy(&logicalMacConfig.logicalMac, macAddress_g, 6);
	logicalMacConfig.portMap = 0x7;
	logicalMacConfig.deviceLinkPort = 0;
	logicalMacConfig.rxLogicalMacCallback = SES_rxlogicalmaccb;
	rv = SES_AddLogicalMac(&logicalMacConfig, &logicalMacReturns);
	return rv;
}

int32_t sesTestDeleteLogicalMac_Example(void) {
	int32_t rv = 0;
	uint16_t entryIndex = 0;
	uint8_t macAddress_g[6] = { 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };
	rv = SES_DeleteLogicalMac(entryIndex, &macAddress_g);
	return rv;
}

int32_t sesTestConfigureLogicalMacFrame_Example(void) {
	int32_t rv = 0;
	uint8_t portNum = 1;
	uint8_t replaceaddr[6] = { 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };
	uint8_t useDeviceMac = 0;
	rv = SES_ConfigureLogicalMacFrame(&replaceaddr, portNum, useDeviceMac);
	return rv;
}

int32_t sesTestApplyForwardMask_Example(void) {
	int32_t rv = 0;
	uint8_t portNum = 0;
	uint8_t portMap = 6;
	rv = SES_ApplyForwardMask(portNum, portMap);
	return rv;
}

int32_t SES_rxlogicalmaccb(int32_t frameLength, uint8_t *frame_p, SES_frameAttributes_t *frameAttributes_p) {
	int32_t rv = 0;
	printf("SES_rxlogicalmaccb Called\n");
	return rv;
}

int32_t SES_rxlogicalmaccb2(int32_t frameLength, uint8_t *frame_p, SES_frameAttributes_t *frameAttributes_p) {
	int32_t rv = 0;
	printf("SES_rxlogicalmaccb2 Called\n");
	return rv;
}


