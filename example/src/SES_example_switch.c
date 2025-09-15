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
#include "SES_example_switch.h"
#include "SES_switch.h"
#include "SES_psfp.h"
#include "SES_codes.h"
#include "SES_debug.h"
#include "SES_configuration.h"
#include "SES_frer.h"

/* Example of getting the default Miss return for unicast on Port 0 */
int32_t sesGetUnicastMissReturn_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort0;
	uint16_t portMap;
	bool cutThrough;
	uint8_t lookupDone;
	uint8_t txFilter;
	bool txFilterValid;
	uint8_t rxFilter;
	bool rxFilterValid;
	rv = SES_GetUnicastMissReturn(mac, &portMap, &cutThrough, &lookupDone, &txFilter, &txFilterValid, &rxFilter, &rxFilterValid);
	return rv;
}

/*
* Example of configuring default Unicast Miss Return for incoming traffic on Port 0 to egress only on
* Port 1 and for switching behaviour to be Store& Forward
*/

int32_t sesSetUnicastMissReturn_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort0;
	/* Forward only to Port 1 */
	uint16_t portMap = 0x2;

	/* Enable Store & Forward mode */
	bool cutThrough = false;

	/* No further lookup required */
	uint8_t lookupDone = 11;
	uint8_t txFilter = 0;
	bool txFilterValid = false;
	uint8_t rxFilter = 0;
	bool rxFilterValid = false;
	rv = SES_SetUnicastMissReturn(mac, portMap, cutThrough, lookupDone, txFilter, txFilterValid, rxFilter, rxFilterValid);
	return rv;
}

/*Example of configuring Store and Forward operation on Port 0 on all queues */
int32_t sesStoreForward_Example(void) {
	
	int32_t rv = SES_OK;
	SES_mac_t port = SES_macPort0;

	/* set store and forward mode on allqueues */
	SES_queueFrameSwitching_t storeandforward = { 0,0,0,0,0,0,0,0 }; 
	rv = SES_SetStoreAndForwardMask(port, &storeandforward);

	return rv;
}

int32_t sesAddSimpleStaticEntry_Example(void) {

	/* Simple example of adding a static entry */
	int32_t rv = SES_OK; 
	uint8_t macAddr[6] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 }; 
	
	/* VLAN ID 0xF */
	int16_t vlanId = 0xF; 

	/* Egress on Port 4 */ 
	uint16_t portMap = 0x10; 
	rv = SES_AddStaticTableEntry(&macAddr, vlanId, portMap);
	return rv;
}

void sesAddStaticTableEntryEx_Example(void) {

	int32_t rv;
	uint8_t lookupPriority = 0; 

	/* Destination Address */
	uint8_t macAddr[6] = { 0x11, 0x11, 0x11, 0x11,  0x11, 0x11 };
	
	uint8_t macMask[6] = { 0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF }; 
	int16_t vlanId = 0x0FF; 
	uint16_t vlanMask = 0xFFF; 
	uint8_t sourceEntry = 0; 
	uint8_t override = 0; 
	uint8_t sourceOverride = 0; 
	uint8_t hsrOrPrpSupervisory = 0; 
	SES_dynTblLookup_t lookupType = SES_dynamicTblLookupSrc; 
	
	/* egress on all port */
	uint8_t portMapPers = 0x3F;  
	uint8_t sendToAE = 1;
	uint8_t danp = 0;
	uint8_t cutThrough = 0;
	uint8_t syntTimestamp = 0;
	uint8_t localTimestamp = 0;
	SES_dynTblSeqMgmt_t sequenceMgmt = dynamicTblNoSequenceOp;
	int rxSequenceSet = 0;

	/* transmit transform to insert/remove VLAN tag for Access port */
	int transmitFilter = SES_IGNORE_FIELD;  
	int receiveFilter = SES_IGNORE_FIELD;
	int index;


	rv = SES_AddStaticTableEntryEx(lookupPriority, macAddr, macMask, vlanId, vlanMask, sourceEntry, override,
		sourceOverride, hsrOrPrpSupervisory, lookupType, portMapPers, sendToAE, danp, cutThrough,
		syntTimestamp, localTimestamp, sequenceMgmt, rxSequenceSet, transmitFilter, receiveFilter, &index);

	printf("Add Static Entry:: %d :: %d\n", rv, index);

}

/* Example of reading a static entry back from the device at index location 120 */
void sesReadStaticEntry_Example(void) {

	int32_t rv = SES_OK;
	uint8_t macAddr[6];
	uint8_t macMask[6];
	uint16_t vlanId;
	uint16_t vlanMask;
	int sourceEntry;
	int override;
	int sourceOverride;
	int hsrOrPrpSupervisory;
	SES_dynTblLookup_t lookupType; 
	uint8_t portMap; 
	int sendToAE; 
	int danp;
	int cutThrough;
	int syntTimestamp;
	int localTimestamp;
	SES_dynTblSeqMgmt_t sequenceMgmt; 
	int rxSequenceSet;
	int transmitFilter;
	int receiveFilter;
	int index = 120;
	rv = SES_ReadStaticTableEntry(index, &macAddr, &macMask, &vlanId, &vlanMask, sourceEntry, override, sourceOverride, hsrOrPrpSupervisory,
		&lookupType, &portMap, sendToAE, danp, cutThrough, syntTimestamp, localTimestamp, &sequenceMgmt, &rxSequenceSet,&transmitFilter, &receiveFilter);
	
	
	printf("Result % d, vlanID % d, msk 0x % 04X, srcEntry % d, override % d, srcOverride % d, hsrOrPrpSupervisory % d, lookupType % d, portMap % d, danp % d, cutThrough % d \r\n",
		rv, vlanId, vlanMask, sourceEntry, override, sourceOverride, hsrOrPrpSupervisory, lookupType, portMap, danp, cutThrough);


	printf("mac % 02X: % 02X : % 02X : % 02X : % 02X : % 02X\r\n", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]); 
	printf("msk % 02X: % 02X : % 02X : % 02X : % 02X : % 02X\r\n", macMask[0], macMask[1], macMask[2], macMask[3], macMask[4], macMask[5]);

}

//==================================Reading Dynamic Table=================================


/*The SES_ReadDynamicTable() API supports reading back the full contents of
the dynamic table and supports a maximum of 50 table entries per call.
To read the full dynamic table, iterative calls are required.The following 
example demonstrates how to read the full dynamic table in blocks of 50 
entries.During dynamic table read operation, learning is disabled until 
the read operation is completed.New entries will not be learned during this time.
*/
void sesReadDynamicTable_Example(void) {

	/*Read 50 entries*/
	int count = 0;
	int startIndex = 0;
	int lastIndex = 49;

	/*Array to store 50 entries */
	SES_dynTblEntry_t dynTblEntry[50];
	uint16_t validEntries_p;
	uint16_t entryCount;

	/*Get valid table entries */
	printf("Entry count %d\n", SES_GetDynTblEntryUsage(&entryCount));
	printf("Entry count :: %d\n", entryCount);

	/* Condition check if entries are less than 50 */
	/* initial 128 entries are blocked by Static entries */
	if ((entryCount - (int16_t)128) < lastIndex) {
		lastIndex = (entryCount - (int16_t)128) - 1;
	}

	/* Read table until all the valid entries are not retrieved */
	while (lastIndex < ((entryCount - (int16_t)128))) {

		if (SES_OK != SES_ReadDynamicTable(startIndex, lastIndex, dynTblEntry, &validEntries_p)) {
			printf("Reading Dynamic Table failed!!\n");
			break;
		}

		for (int i = 0; i <= (lastIndex - startIndex); i++) {
			printf("Index :: %d\t", i);
			printf("Dynamic Table MacAddress % 02x % 02x % 02x % 02x % 02x % 02x \n\n",
				dynTblEntry[i].macAddress[0],
				dynTblEntry[i].macAddress[1],
				dynTblEntry[i].macAddress[2], 
				dynTblEntry[i].macAddress[3], 
				dynTblEntry[i].macAddress[4],
				dynTblEntry[i].macAddress[5]);
		}
		/* Control variables to maintain starts and last index */
		if (lastIndex + 1 == (entryCount - (int16_t)128)) {
			break;
		}
		startIndex = lastIndex + 1;
		if ((startIndex + 49) < (entryCount - (int16_t)128)) {
			lastIndex = startIndex + 49;
		}
		else {
			lastIndex = (entryCount - (int16_t)128) - 1;
		}
	}
}

/*Retrieve Port Statistics*/
void sesGetStatistics_Example(void) {

	SES_mac_t mac = SES_macPort0;
	SES_statistic_t stat_p;

	printf("Get Port Statistics :: %d\n", SES_GetStatistics(mac, &stat_p, sizeof(stat_p)));

	printf("RxByte :: %d\n", stat_p.rxByte);
	printf("rxUnicast :: %d\n", stat_p.rxUnicast);
	printf("rxBroadcast :: %d\n", stat_p.rxBroadcast);

	printf("txByte :: %d\n", stat_p.txByte);
	printf("txUnicast :: %d\n", stat_p.txUnicast);
	printf("txBroadcast :: %d\n", stat_p.txBroadcast);
	printf("txMacError :: %d\n", stat_p.txMacError);

}


void sesSwitch_Example(void) {

	switch (SWITCH_EXAMPLE) {
	case 1:
		printf("Reading Dynamic Table!!\n");
		sesReadDynamicTable_Example();
		break;

	case 2:
		printf("Reading Port 0 Statistics\n");
		sesGetStatistics_Example();
		break;


	default:
		printf("Wrong configuration !!!");
		break;

	}
}

//==================================Extended Table=================================

int32_t sesExtendedTableStaticRouteSimple_Example(void){
	int32_t rv = SES_ERROR;
	
	/* Example of adding an extended table entry, note that to perform extended table lookup, user must also either 
	install a static table entry passing passing SES_dynamicTblLookupExt for the lookup mode or alternatively enable 
	extended table lookup for the port using SES_SetRxPortLookupMode() */

	/* Egress on Port 4 */
	uint8_t portMap = 0x10; 
	uint8_t cutThrough = 0;
	int override = 0;
	/* Ethertype to match in frame */
	uint16_t ethertype = 0xA000;

	/* Data to match in frame */
	uint8_t data[14] = { 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
							0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA };
	/* Mask information, match on first two bytes */
	uint8_t mask[14] = { 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
 							0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	int txFilter = SES_IGNORE_FIELD; 
	int rxFilter = SES_IGNORE_FIELD; 
	int saveSyntonized = 0;
	int saveFreerunning = 0;
	int srcOverride = 1;
	int supervisory = 0;
	int seqRecovery = SES_IGNORE_FIELD; 
	int sequenceRecoveryMode = 0;
	int routeNum;

	rv = SES_AddExtendedStaticRoute_Simple(ethertype, &data, &mask, txFilter, rxFilter, portMap, saveSyntonized, 
	saveFreerunning, cutThrough, override, srcOverride, supervisory, seqRecovery, sequenceRecoveryMode, &routeNum); 

	return rv;
}

int32_t sesUpdateExtendedTable_Example(void){
	int32_t rv = SES_ERROR;
	
	/* Example of updating the port map of an existing extended table entry */

	/* Ethertype to match in frame */
	uint16_t ethertype = 0xA000;
	uint8_t data[] = { 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
							0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA };
	/* Mask information, match on first two bytes */
	uint8_t mask[] = { 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
							0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	int txFilter = SES_IGNORE_FIELD; 
	int rxFilter = SES_IGNORE_FIELD; 
	int portMap = 0x0002;
	int saveSyntonized = 0;
	int saveFreerunning = 0;
	int cutThrough = 1;
	int override = 0;
	/* Use Extended table portmap return information */
	int srcOverride = 1; 
	int supervisory = 0;
	int seqRecovery = SES_IGNORE_FIELD; 
	int sequenceRecoveryMode = 0;
	/* route number of the added route */
	int routeNum;
	rv = SES_AddExtendedStaticRoute_Simple(ethertype, &data, &mask,
											txFilter, rxFilter, portMap,
											saveSyntonized, saveFreerunning, cutThrough, override,
											srcOverride, supervisory, seqRecovery,
											sequenceRecoveryMode, &routeNum);
	
	/* new port map for the route */
	portMap = 0x0010;
	rv = SES_SetExtendedLookupEntryPortMap(routeNum, portMap);

	return rv;
}

int32_t sesExtendedTableStaticRouteIpv4_Example(void){
	int32_t rv = SES_ERROR;
	
	/* Example of adding an IPv4 extended table entry using SES_AddExtendedStaticRoute_IPv4TcpUdp helper function */
	uint8_t dscp = 0x00;
	/* 0x11 for UDP */
	uint8_t nextProto = 0x11;
	/* IP address 10:10:10:10 */
	uint32_t srcIpAddrArr[4] = { 10, 10, 10, 10 };
	uint32_t srcIpAddr = (srcIpAddrArr[0] << 24) | (srcIpAddrArr[1] << 16) | (srcIpAddrArr[2] << 8) | 
	(srcIpAddrArr[3]);
	/* IP address 10:10:10:20 */
	uint32_t dstIpAddrArr[4] = { 10, 10, 10, 20 };
	uint32_t dstIpAddr = (dstIpAddrArr[0] << 24) | (dstIpAddrArr[1] << 16) | (dstIpAddrArr[2] << 8) | 
	(dstIpAddrArr[3]);
	uint16_t srcPortArr[2] = { 0x00, 0x00 };
	uint16_t srcPort = (srcPortArr[0] << 8) | (srcPortArr[1]);
	uint16_t dstPortArr[2] = { 0x00, 0x00 };
	uint16_t dstPort = (dstPortArr[0] << 8) | (dstPortArr[1]);
	int portMap = 0x02;
	int32_t routeNum;

	/* Call the ADINx310 driver API to make an entry in the extended lookup table */
	rv = SES_AddExtendedStaticRoute_IPv4TcpUdp(dscp, // Differentiated Services Code Point Field to match
												nextProto, // Protocol field to match, 6 for TCP, 17 for UDP
												srcIpAddr, // source IPv4 address
												dstIpAddr, // destination IPv4 address
												srcPort, // source port
												dstPort, // destination port
												SES_IGNORE_FIELD, // tx filter
												SES_IGNORE_FIELD, // rx filter
												portMap, // ports to forward the frame to 
												0, // no syntonized timestamp
												0, // no local timestamp
												0, // Store & Forward entry
												0, // Override
												1, // Source override, Use Extended table portmap return information
												0, // not a supervisory frame
												SES_IGNORE_FIELD, // no sequence recovery
												0, // no sequence recovery
												&routeNum);
	

	return rv;
}

int32_t sesInstallExtendedLookupEntryIpv4_Example(void){
	int32_t rv = SES_ERROR;
	
	/* Example of adding an IPv4 extended table entry using SES_InstallExtLookupEntry*/
	uint16_t ethertype = 0x0800;
	int override = 0;

	/* 
	 * DCSP 
	 * Next protocol
	 * Source IP address and Destination IP address
	 * Source port and Destination port number	
	 */
	uint16_t fieldOffsets[] = { 1, 9, 12, 20};
	uint16_t fieldSizes[] = { 1, 1, 8, 4};

	int fieldCount = sizeof(fieldSizes)/sizeof(fieldSizes[0]);

	/* 
	 * DCSP 
	 * Next protocol
	 * Source IP address
	 * Destination IP address
	 * Source port
	 * Destination port number	
	 */
	uint8_t fieldData[] = { 0,
							0x11,
							10, 10, 10, 10,
							10, 10, 10, 20,
							0x00, 0x00,
							0x00, 0x00};
	uint8_t fieldMask[] = { 0xFC,
							0xFF,
							0xFF, 0xFF, 0xFF, 0xFF,
							0xFF, 0xFF, 0xFF, 0xFF,
							0xFF, 0xFF,
							0xFF, 0xFF};
	
	int portMap = 0x02;
	int32_t routeNum;

	rv = SES_InstallExtLookupEntry(ethertype,// ethertype
									fieldCount, // fieldCount
									fieldOffsets, // fieldOffsets
									fieldSizes, // fieldSizes
									fieldData, // fieldData
									fieldMask, // fieldMask
									SES_IGNORE_FIELD, // txFilter
									SES_IGNORE_FIELD, // rxFilter
									portMap, // portMap
									0, // saveSyntonized
									0, // saveFreerunning
									0, // cutThrough
									0,// override
									1, // srcOverride
									0, // supervisory
									SES_IGNORE_FIELD, // seqRecovery
									0, // sequenceRecoveryMode
									&routeNum); 
	

	return rv;
}

int32_t sesExtendedTableStaticRouteIpv6_Example(void){
	int32_t rv = SES_ERROR;
	
	/* Example of adding an IPv6 extended table entry using SES_AddExtendedStaticRoute_IPv6TcpUdp helper function */
	uint8_t diffSer = 0x00;
	uint8_t nextHeader = 0x11;

	/* IPv6 address 11:2233:4455:6677:8899:aabb:ccdd:eeff */
	uint8_t srcIpAddr[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
								0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

	/* IPv6 address 11:2233:4455:6677:8899:aabb:ccdd:ee00 */
	uint8_t dstIpAddr[16] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
								0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0x00 };

	uint16_t srcPort = 0;
	uint16_t dstPort = 0;
	int portMap = 0x02;
	int32_t routeNum;

	/* Call the ADINx310 driver API to make an entry in the extended lookup table */
	rv = SES_AddExtendedStaticRoute_IPv6TcpUdp(diffSer,
												nextHeader, // Protocol field to match, 6 for TCP, 17 for UDP
												&srcIpAddr, // source IPv6 address
												&dstIpAddr,// destination IPv6 address
												srcPort, // source port
												dstPort,// destination port
												SES_IGNORE_FIELD,// tx filter
												SES_IGNORE_FIELD ,// rx filter
												portMap,// ports to forward the frame to
												0,// no syntonized timestamp
												0,// no local timestamp
												0,// Store & Forward entry
												0, // Override
												1, // Source override, set to 1 to use Extended table portmap return information
												0,// not a supervisory frame
												SES_IGNORE_FIELD,// no sequence recovery
												0,// no sequence recovery
												&routeNum);
	

	return rv;
}

int32_t sesInstallExtendedLookupEntryIpv6_Example(void){
	int32_t rv = SES_ERROR;
	
	/* Example of adding an IPv6 extended table entry using SES_InstallExtLookupEntry() API*/
	uint16_t ethertype = 0x86DD;

	/* 
 	 * Differentiated services 
	 * Next header
	 * Source IP address
	 * Destination IP address
	 * Source port number
	 * IPv6 UDP data inspect
	 * IPv6 TCP data inspect
	 */
	uint16_t fieldOffsets[] = { 0,
								6,
								8,
								24,
								40,
								48,
								60};

	uint16_t fieldSizes[] = { 2,
								1,
								16,
								16,
								4,
								8,
								9};

	int fieldCount = sizeof(fieldSizes)/sizeof(fieldSizes[0]);

	uint8_t fieldData[2 + 1 + 16 + 16 + 2 + 2];
	/* Differentiated services */
	fieldData[0] = (0 >> 2);
	fieldData[1] = (0 << 6);
	/* Next header field to match, 6 for TCP, 17 for UDP*/
	fieldData[2] = 0x11;
	uint8_t SrcIpv6Addr[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
								0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
	uint8_t DstIpv6Addr[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
								0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0x00 }; 
	
	/* Source IP address */
	memcpy(&fieldData[3], SrcIpv6Addr, sizeof(SrcIpv6Addr));
	/* Destination IP address */
	memcpy(&fieldData[3 + sizeof(SrcIpv6Addr)], DstIpv6Addr, sizeof(DstIpv6Addr));

	uint8_t SrcPrt[] = {0x00, 0x00};
	uint8_t DstPrt[] = {0x00, 0x00};

	/* Source port and destination port number */
	fieldData[3 + sizeof(SrcIpv6Addr) + sizeof(DstIpv6Addr)] = SrcPrt[0];
	fieldData[3 + sizeof(SrcIpv6Addr) + sizeof(DstIpv6Addr) + 1] = SrcPrt[1];
	fieldData[3 + sizeof(SrcIpv6Addr) + sizeof(DstIpv6Addr) + 2] = DstPrt[0];
	fieldData[3 + sizeof(SrcIpv6Addr) + sizeof(DstIpv6Addr) + 3] = DstPrt[1];

	uint8_t fieldMask[] = { 0x0F, 0xC0, // Differentiated services
							0xFF, // Next header
							0xFF, 0xFF, 0xFF, 0xFF, // Source IP address
							0xFF, 0xFF, 0xFF, 0xFF,
							0xFF, 0xFF, 0xFF, 0xFF,
							0xFF, 0xFF, 0xFF, 0xFF,
							0xFF, 0xFF, 0xFF, 0xFF, // Destination IP address
							0xFF, 0xFF, 0xFF, 0xFF,
							0xFF, 0xFF, 0xFF, 0xFF,
							0xFF, 0xFF, 0xFF, 0xFF,
							0xFF, 0xFF, 0xFF, 0xFF, // Source port and destination port number
							0x00, 0x00, 0x00, 0x00, // IPv6 UDP data inspect
							0x00, 0x00, 0x00, 0x00,
							0x00, 0x00, 0x00, 0x00, // IPv6 TCP data inspect
							0x00, 0x00, 0x00, 0x00, 0x00 };
	
	int portMap = 0x04;
	int32_t routeNum;
	
	rv = SES_InstallExtLookupEntry(ethertype,// ethertype
									fieldCount, // fieldCount
									fieldOffsets, // fieldOffsets
									fieldSizes, // fieldSizes
									fieldData, // fieldData
									fieldMask, // fieldMask
									SES_IGNORE_FIELD, // txFilter
									SES_IGNORE_FIELD, // rxFilter
									portMap, // portMap
									0, // saveSyntonized
									0, // saveFreerunning
									0, // cutThrough
									0, // Override
									1, // srcOverride, set to 1 to use Extended table portmap return information
									0, // supervisory
									SES_IGNORE_FIELD, // seqRecovery
									0, // sequenceRecoveryMode
									&routeNum); // routeNum_p
	

	return rv;
}

//==================================Reprioritize Based on Ethertype=================================

/**
* 	@brief Helper function to set port stream filter and stream gate
*
* 	@param[in]   mac: MAC identifier of the Rx port where the stream filter must be applied
* 	@param[in]   ipv: The desired priority value
* 	@param[in]   rxStreamGateIndex: Index for the stream gate that needs to be created. 0-15 are the valid values
				Note: Use SES_PSFP_GetStreamGateIndex API to get an available stream gate ID
* 	@param[in]   rxFilterIndex: Index for the stream filter that needs to be created. 0-31 are the valid values
               	Note: Use SES_PSFP_GetStreamFilterIndex API to get an available stream filter ID
*
*	 @return
*   	- #SES_OK      operation succeeded
*   	- #SES_ERROR   unable to set stream filter
*/
int32_t sesAddStreamFilterEntry_Example(SES_mac_t mac,
	uint8_t ipv,
	uint8_t rxStreamGateIndex,
	uint8_t rxFilterIndex) 
{ 
	int32_t rv = SES_ERROR;
	int32_t i;
	static int routeNum = 0;
	TSN_ieee802_dot1q_psfp_stream_filter_instance_table_config_t streamFilterInstanceTable;
	TSN_ieee802_dot1q_psfp_stream_gate_instance_table_config_t streamGateInstanceTable;

	/* Clear the contents of the structure before configuring */
	memset(&streamFilterInstanceTable, 0, sizeof(TSN_ieee802_dot1q_psfp_stream_filter_instance_table_config_t));
	memset(&streamGateInstanceTable, 0, sizeof(TSN_ieee802_dot1q_psfp_stream_gate_instance_table_config_t));

	/* Configure the stream filter and stream gates */
	/* Stream filter parameters */
	streamFilterInstanceTable.stream_filter_instance_id = rxFilterIndex; //filterIndex
	streamFilterInstanceTable.priority_spec_type.priority_spec = 0; //pcp
	streamFilterInstanceTable.stream_handle_spec.stream_handle = rxFilterIndex; //streamID
	streamFilterInstanceTable.max_sdu_size = 0xFFFF; //maxSDU
	streamFilterInstanceTable.flow_meter_ref = 0xFF; //flowMeterID
	streamFilterInstanceTable.stream_gate_ref = rxStreamGateIndex; //gateID
	streamFilterInstanceTable.stream_blocked_due_to_oversize_frame_enabled = 0; //blockEnable
	/* Stream gate parameters */
	streamGateInstanceTable.stream_gate_instance_id = rxStreamGateIndex;
	streamGateInstanceTable.gate_enable = true;
	streamGateInstanceTable.config_change = true;
	streamGateInstanceTable.admin_gate_states = 1;
	streamGateInstanceTable.admin_ipv = 0x0;
	streamGateInstanceTable.admin_control_list_length = 0x01;
	streamGateInstanceTable.admin_control_list[0].ipv_spec = ipv; //ipv Set
	streamGateInstanceTable.admin_control_list[0].gate_state_value = 1; //gateOpen
	streamGateInstanceTable.admin_control_list[0].time_interval_value = 1000000; // gate nanoseconds
	
	streamGateInstanceTable.admin_cycle_time.numerator = 1; //numerator in seconds
	streamGateInstanceTable.admin_cycle_time.denominator = 1000; //denominator in seconds, Admin cycle time = 1ms (1/1000)

	/* Call the ADINx310 driver API to add stream gate entry */
	rv = SES_PSFP_SetStreamGateActive(mac, &streamGateInstanceTable);

	/* Call the ADINx310 driver API to add stream filter entry */
	rv = SES_PSFP_SetStreamFilterActive(mac, &streamFilterInstanceTable);

	return rv;
} 

/**
* 	@brief Helper function to add an entry in the extended table
*
* 	@param[in]   portMap: egress port indicator
* 	@param[in]   rxFilterIndex: Streamfilter ID that needs to be applied on the frame that gets a hit in extended lookup table
* 	@param[in]   ethertype: ethertype to match for this extended static route
* 	@param[in]   cutThrough: 0 -> don't use cut-through forwarding
*                          1 -> use cut-through
* 	@param[out]  routeNum_p: pointer to location in which route number
*              	will be copied
*
* 	@return
*   	- #SES_OK      operation succeeded
*   	- #SES_ERROR   unable to set gate parameters
*/
int32_t sesAddExtendedTableEntry_Example(uint8_t portMap,
	uint8_t rxFilterIndex,
	uint16_t ethertype,
	uint8_t cutThrough,
	int32_t* routeNum_p)
{ 
	int32_t rv = SES_ERROR;
	/* If only interested to match on ethertype, then set Field data to zero */
	uint8_t fieldData[14];
	memset(&fieldData[0], 0, sizeof(fieldData));
	uint8_t fieldMask[14];
	memset(&fieldMask[0], 0, sizeof(fieldData));
	/* Call the ADINx310 driver API to make an entry in the extended lookup table */
	rv = SES_AddExtendedStaticRoute_Simple(ethertype, //ethertype
											&fieldData, //data_p
											&fieldMask, //mask_p
											SES_IGNORE_FIELD, //txFilter
											rxFilterIndex, //rxFilter
											portMap, //portMap
											0, //saveSyntonized
											0, //saveFreerunning
											0, //cutThrough
											0, // Override
											1, //srcOverride, set to 1 to use Extended table portmap return information
											0, //supervisory
											SES_IGNORE_FIELD, //seqRecovery
											0, //sequenceRecoveryMode
											routeNum_p); //routeNum_p
	return rv;
} 

int32_t sesEthertypeReprioritizationRxlookup_Example(void) {
	int32_t rv = SES_PORT_ERROR;

    SES_mac_t mac = SES_macPort0;//port to apply rx filter at (ingress port)
	uint8_t ipv = 7;//highest priority. Puts the frame in Q7 of the egress port
	uint8_t portMap = 0x04; //Egress port Port2 
	uint16_t ethertype = 0x88b6;
	int32_t routeNum = 0;
	uint8_t cutThrough = 0; // store-forward mode for psfp operation.
	uint8_t rxFilterIndex = SES_PSFP_GetStreamFilterIndex(0x01); //Get available stream filter ID for Port0
	uint8_t rxStreamGateIndex = SES_PSFP_GetStreamGateIndex(0x01); //Get available stream gate ID for Port0
	uint32_t regValue = 0;
	/* Call helper function to set a stream filter */
	rv = sesAddStreamFilterEntry_Example(mac, ipv, rxStreamGateIndex, rxFilterIndex);
	/* Call helper function to add an entry in the extended lookup table */
	rv |= sesAddExtendedTableEntry_Example(portMap, rxFilterIndex, ethertype, cutThrough, &routeNum);
	/* Call the ADINx310 driver API for enabling the extended lookup for all frames on the chosen Rx port*/
	rv |= SES_GetRxPortLookupMode(mac, &regValue);
	if (rv == 0) {
		regValue |= SES_RX_PORT_EXT_LOOKUP;
		rv = SES_SetRxPortLookupMode(mac, regValue);
	} 

	printf("ses_ethertype_reprioritization_rxlookup_example :: %d\n", rv);
	return rv;
}

int32_t sesEthertypeReprioritizationStaticTable_Example(void) {
	int32_t rv = SES_PORT_ERROR;

    SES_mac_t mac = SES_macPort0;//port to apply rx filter at (ingress port)
	uint8_t ipv = 7;//highest priority. Puts the frame in Q7 of the egress port
	int16_t vlanId = 1; //vlan id
	uint8_t portMap = 0x04; //Egress port Port2 
	uint16_t ethertype = 0x88b6;
	int32_t routeNum = 0;
	int32_t index;
	uint8_t cutThrough = 0; // store-forward mode for psfp operation.
	uint8_t rxFilterIndex = SES_PSFP_GetStreamFilterIndex(0x01); //Get available stream filter ID for Port0
	uint8_t rxStreamGateIndex = SES_PSFP_GetStreamGateIndex(0x01); //Get available stream gate ID for Port0
	uint8_t macAddr[6] = { 0x11,0x22,0x33,0x44,0x55,0x66 }; //sample mac address
 	uint8_t macMask[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	/* Call helper function to set a stream filter */
	rv = sesAddStreamFilterEntry_Example(mac, ipv, rxStreamGateIndex, rxFilterIndex);

	/* Call helper function to add an entry in the extended lookup table */
	rv |= sesAddExtendedTableEntry_Example(portMap, rxFilterIndex, ethertype, cutThrough, &routeNum);

	/* Call the ADINx310 driver API for adding a static table entry */
	rv |= SES_AddStaticTableEntryEx(1, // lookup priority
									&macAddr, // mac address
									&macMask, // mac mask
									vlanId, // vlan id
									SES_DYNTBL_VLAN_EXACT_MATCH, // vlan mask
									0, // source entry
									0, // override
									0, // source override
									0, // hsr prp supervisory
									SES_dynamicTblLookupExt, // lookup type -> extended table lookup
									portMap, // port map
									0, // send to ae
									0, // danp
									cutThrough, // cut through -> store and forward operation
									0, // synt timestamp
									0, // local timestamp
									dynamicTblNoSequenceOp, // sequencemgmt
									0, // rx sequence set
									SES_IGNORE_FIELD, // transmit filter
									SES_IGNORE_FIELD, // receive filter
									&index); // index*

	printf("ses_ethertype_reprioritization_static_table_example :: %d\n", rv);
	return rv;
}


void sesUpdateMACAddress_Example(void)
{
	//Destination MAC address to look for to update source MAC
	uint8_t destinationAddr[6] = { 0xF8,0xE4,0x3B,0x10,0x49,0xC9 };
	uint8_t Addr_mask[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	
	//New address to replace exstine source address 
	uint64_t tempAddr[6] = { 0xaa,0xaa,0xaa,0xaa,0xaa,0xaa }; 
	uint64_t destAddr = 0;
	int32_t rv = 0;

	//Retrieve TxTranform index for Port 1 and Port 2 
	int32_t txAddrXformIndex = SES_GetTxTransformIndex(0x06);

	printf("Transform Index %d\n", txAddrXformIndex);

	//Convert 8bit to 64bit
	for (int i = 0; i < 6; i++) {
		destAddr |= ((uint64_t)tempAddr[i] << (8 * (5 - i)));
	}
	//Insatll new TxTransform for Port 1
	//To update destination MAC, srcAddrReplace must be set to 0
	rv = SES_TxPortSetTxXformEntry(
		SES_macPort1,            // int port
		txAddrXformIndex,       // int entry
		0,                      // int timeSize
		0,                      // int timeOffset
		0,                      // int timeSourceFree
		0,                      // int peerDelaySelect
		SES_noTimeOperation,    // SES_DRV_txPortTimeOperation_t timeOperation
		0,                      // int srfIndex
		0,                      // int srfEnable
		SES_noTagOperation,     // SES_DRV_txPortTagOperation_t tagOperation
		destAddr,            // uint64_t destAddress
		1,                      // int destAddrSwapEn
		0,                      // int vlanPCP
		0,                      // int vlanDEI
		0,                      // uint16_t vlanID
		SES_dynamicTblVlanNoTagOp,  // SES_DRV_txPortVLANOperation_t vlanOperation
		1,                      // int srcAddrReplace
		0);                     // portIdReplace

	printf("Tx transform :: %d\n", rv);


	//Insatll new TxTransform for Port 1
	//To update destination MAC, srcAddrReplace must be set to 0
	rv = SES_TxPortSetTxXformEntry(
		SES_macPort2,            // int port
		txAddrXformIndex,       // int entry
		0,                      // int timeSize
		0,                      // int timeOffset
		0,                      // int timeSourceFree
		0,                      // int peerDelaySelect
		SES_noTimeOperation,    // SES_DRV_txPortTimeOperation_t timeOperation
		0,                      // int srfIndex
		0,                      // int srfEnable
		SES_noTagOperation,     // SES_DRV_txPortTagOperation_t tagOperation
		destAddr,            // uint64_t destAddress
		1,                      // int destAddrSwapEn
		0,                      // int vlanPCP
		0,                      // int vlanDEI
		0,                      // uint16_t vlanID
		SES_dynamicTblVlanNoTagOp,  // SES_DRV_txPortVLANOperation_t vlanOperation
		1,                      // int srcAddrReplace
		0);                     // portIdReplace

	printf("Tx transform :: %d\n", rv);


	//New static entry to apply the above TxTransform 
	rv = SES_AddStaticTableEntryEx(
		1,                             // lookupPriority
		destinationAddr,                    // MACaddr_p
		Addr_mask,                          // MACmask_p
		SES_DYNTBL_NO_VLAN,            // vlanID
		0,                             // vlanMask
		0,                             // sourceEntry
		0,                             // override
		0,                             // sourceOverride
		0,                             // hsrOrPrpSupervisory
		SES_dynamicTblLookupBasic,       // lookupType
		0x06,                     // portMap
		0,                             // sendToAE
		0,                             // danp
		0,                             // cutThrough
		0,                             // syntTimestamp
		0,                             // localTimestamp
		dynamicTblNoSequenceOp,    // sequenceMgmt
		0,                             // rxSequenceSet
		txAddrXformIndex,              // transmitFilter
		SES_DYNTBL_NO_ENTRY,           // receiveFilter
		NULL);                         // index_p

	printf("Static Entry  :: %d\n", rv);

}