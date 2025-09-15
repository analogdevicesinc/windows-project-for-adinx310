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
#include "SES_example_vlan.h"
#include "SES_configuration.h"
#include "SES_vlan.h"
#include "SES_frer.h"

/*  Set Port 3 and port 4 in Learn and Forward Mode for given VLAN */
int32_t sesSetVlanMode_Example(void) {
	int32_t rv = 0;
	uint16_t VID = 10;
	/**
	*	Reserved|port 5|port 4|port 3|port 2|port 1|port 0|
	*   | 0000  |  00  |  00  |  11  |  11  |  00  |  00  |
	*	 For each port one of the following four values are possible
    *              00 vlanNoLearn_NoForward
    *              01 vlanNoLearn_Forward
    *              10 vlanLearn_NoForward
    *              11 vlanLearn_Forward
	*/
	printf("Configuring Port 3 and port 4 in Learn and Forward Mode for VLAN ID 10 \n");
	uint16_t map = 0x00F0;
	rv = SES_SetVlanMode(VID, map);
	return rv;
}

/* Set VLAN operating mode for vid 20 as Learn and Forward for Port 5*/
int32_t sesSetVlanPortMode_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	uint16_t VID = 20;
	SES_vlanMode_t mode = SES_vlanLearn_Forward;
	rv = SES_SetVlanPortMode(mac, VID, mode);
	return rv;
}

/* Set VLAN operating mode for specific port for all configured VLANs */
int32_t sesSetVlanPortModeAll_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort4;
	SES_vlanMode_t mode = SES_vlanLearn_Forward;
	rv = SES_SetVlanPortModeAll(mac, mode);
	return rv;
}

/* Trunk/Access example with following port configurations: 
		- Port 0 → Host Port
		- Port 1 → Access port, VLAN ID 2, PCP 2
		- Port 2 → Access port, VLAN ID 3, PCP 2
		- Port 3 → Access port, VLAN ID 4, PCP 2
		- Port 4 → Access port, VLAN ID 5, PCP 2
		- Port 5 → Trunk port, VLN ID range 1-5, PCP 2
*/
void sesAccessTrunkMode_Example(void) {

	/* port 1: access port, VLAN ID 2, PCP 2 */
	printf("Port 1 as access Port :: %d\n", SES_SetVlanPortType(SES_macPort1, (uint16_t)2, (uint16_t)2, (uint8_t)2, SES_vlanAccess));
	
	/* port 2: access port, VLAN ID 3, PCP 2 */
	printf("Port 2 as access Port :: %d\n", SES_SetVlanPortType(SES_macPort2, (uint16_t)3, (uint16_t)3, (uint8_t)2, SES_vlanAccess));
	
	/* port 3: access port, VLAN ID 4, PCP 2 */
	printf("Port 3 as access Port :: %d\n", SES_SetVlanPortType(SES_macPort3, (uint16_t)4, (uint16_t)4, (uint8_t)2, SES_vlanAccess));
	
	/* port 4: access port, VLAN ID 5, PCP 2 */
	printf("Port 4 as access Port :: %d\n", SES_SetVlanPortType(SES_macPort4, (uint16_t)5, (uint16_t)5, (uint8_t)2, SES_vlanAccess));

	/* port 5: Trunk port, VLN ID range 1-5, PCP 2 */
	printf("SES_SetVlanPortType 5 :: %d\n", SES_SetVlanPortType(SES_macPort5, (uint16_t) 1, (uint16_t) 5, (uint8_t) 2, SES_vlanTrunk));
	
}


void sesInsertVlanTag_Example(void) {

	int32_t rv = SES_OK;
	SES_mac_t mac = SES_macPort4;
	int timeSize = 0;
	int timeOffset = 0;
	int timeSourceFree = 0;
	int peerDelaySelect = 0;
	SES_timestampOperation_t timeOperation = SES_noTimeOperation;
	int srfIndex = 0;
	int srfEnable = 0;
	SES_tagOperation_t tagOperation = SES_noTagOperation;
	uint64_t destAddress[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	int destAddrSwapEn = 0;
	/* Priority of 7*/
	int vlanPcp = 7;
	int vlanDei = 0;
	/* VLAN ID of 1*/
	uint16_t vlanId = 1; 
	/* Insert VLAN Tag */
	SES_dynTblVlanTagOp_t vlanOperation = SES_dynamicTblVlanInsertTag; 
	int srcAddrReplace = 0;
	int portIdReplace = 0;
	/* Get Tx Transform index for Port 4 */
	int32_t filterindex = SES_GetTxTransformIndex(0x10);
	int entry = filterindex;
	rv = SES_TxPortSetTxXformEntry(mac, entry, timeSize, timeOffset, timeSourceFree, peerDelaySelect, timeOperation, srfIndex, srfEnable, tagOperation, destAddress, destAddrSwapEn, vlanPcp, vlanDei, vlanId, vlanOperation, srcAddrReplace, portIdReplace);


	/* 
	* Now install a static entry with the macMask as all 0�s, so all traffic going out that port has VLAN
	* tag inserted 
	*/

	uint8_t lookupPriority = 0;  
	uint8_t macAddr_p[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x77 };
	uint8_t macMask_p[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; 
	vlanId = 4095;
	uint16_t vlanMask = 0xFFF;
	uint8_t sourceEntry = 0;
	uint8_t override = 0;
	uint8_t sourceOverride = 0;
	uint8_t hsrOrPrpSupervisory = 0;
	SES_dynTblLookup_t lookupType = SES_dynamicTblLookupBasic;
	uint8_t portMap = 0x10;
	uint8_t sendToAE = 0;
	uint8_t danp = 0;
	uint8_t cutThrough = 0;
	uint8_t syntTimestamp = 0;
	uint8_t localTimestamp = 0;
	SES_dynTblSeqMgmt_t sequenceMgmt = dynamicTblNoSequenceOp;
	int rxSequenceSet = 0;
	/* Tx Transform index to insert VLAN tag */
	int transmitFilter = filterindex;
	int receiveFilter = -1;
	int index_p;
	rv = SES_AddStaticTableEntryEx(lookupPriority, &macAddr_p, &macMask_p, vlanId,
		vlanMask, sourceEntry, override, sourceOverride,
		hsrOrPrpSupervisory, lookupType, portMap, sendToAE,
		danp, cutThrough, syntTimestamp, localTimestamp,
		sequenceMgmt, rxSequenceSet, transmitFilter, receiveFilter, &index_p);
}

void sesVlan_Example(void) {

	if (TRUNK_ACCESS) {
		sesAccessTrunkMode_Example();
	}
	else {
		sesSetVlanMode_Example();
	}

}
