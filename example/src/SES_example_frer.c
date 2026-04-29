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
#include "SES_frer.h"
#include "SES_codes.h"
#include "SES_debug.h"
#include "SES_configuration.h"

#define SES_PORT_0 0
#define SES_PORT_1 1
#define SES_PORT_2 2
#define SES_PORT_3 3
#define SES_PORT_4 4
#define SES_PORT_5 5
#define SES_PORTMAP_PORT_0 1
#define SES_PORTMAP_PORT_1 2
#define SES_PORTMAP_PORT_2 4
#define SES_PORTMAP_PORT_3 8
#define SES_PORTMAP_PORT_4 16
#define SES_PORTMAP_PORT_5 32



void sesNullStream_Example(void) {

	TSN_ieee802Dot1cbStream_t streamParameters;

	uint8_t destinationMAC[6] = {0x00, 0x00, 0x00, 0x11, 0x11, 0x11};

	/*Null stream identification*/
	streamParameters.TSN_streamIdentity.identificationType = TSN_nullStream; 

	/*Assigning Desination MAC address*/
	for (int i = 0; i < 6; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_nullStreamIdentification.destinationMac[i] = destinationMAC[i];
	}
	/*VLAN Identifier*/
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_nullStreamIdentification.vlan = 100; 

	/*Port MAP for Egress traffic*/
	streamParameters.portMap = SES_PORTMAP_PORT_1 | SES_PORTMAP_PORT_2; 
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[0] = -1;
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[1] = -1;
	streamParameters.TSN_HardwareTableIndices.exTblruleId = -1;
	streamParameters.useStreamtable = false;
	streamParameters.usedCnt = 0;

}

void sesSmacVlan_Example(void) {

	uint8_t destinationMAC[6] = { 0x00, 0x00, 0x00, 0x22, 0x22, 0x22 };
	TSN_ieee802Dot1cbStream_t streamParameters;

	/*Source MAC and VLAN stream identification*/
	streamParameters.TSN_streamIdentity.identificationType = TSN_smacVlan; 

	/*Assigning Desination MAC address*/
	for (int i = 0; i < 6; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_nullStreamIdentification.destinationMac[i] = destinationMAC[i];
	}

	/*VLAN Identifier*/
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_smacVlanStreamIdentification.vlan = 100; 

	/* Port MAP for Egress traffic
	*  bit field mapped to physical egress ports for stream
	*/
	streamParameters.portMap = SES_PORTMAP_PORT_1 | SES_PORTMAP_PORT_2; 
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[0] = -1;
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[1] = -1;
	streamParameters.TSN_HardwareTableIndices.exTblruleId = -1;
	streamParameters.useStreamtable = false;
	streamParameters.usedCnt = 0;

	// return streamParameters;
}


void sesDmacVlan_Example(void) {

	TSN_ieee802Dot1cbStream_t streamParameters;
	uint8_t downDestinationMAC[6] = { 0x00, 0x00, 0x00, 0x33, 0x33, 0x33 };
	uint8_t upDestinationMAC[6] = { 0x00, 0x00, 0x44, 0x44, 0x44, 0x44 };

	/* Active Destination MAC and VLAN stream identification */
	streamParameters.TSN_streamIdentity.identificationType = TSN_dmacVlan; 
	
	/* Assigning Down Desination MAC address */
	for (int i = 0; i < 6; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_dmacVlanStreamIdentification.TSN_down.destinationMac[i] = downDestinationMAC[i];
	}

	/* Assigning UP Desination MAC address */
	for (int i = 0; i < 6; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_dmacVlanStreamIdentification.TSN_up.destinationMac[i] = upDestinationMAC[i];
	}

	/*VLAN Identifier*/
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_dmacVlanStreamIdentification.TSN_down.vlan = 100;
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_dmacVlanStreamIdentification.TSN_up.vlan = 200;
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_dmacVlanStreamIdentification.TSN_up.priority = 1;

	/* bit field mapped to physical egress ports for stream */
	streamParameters.portMap = SES_PORTMAP_PORT_1 | SES_PORTMAP_PORT_2; 
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[0] = -1;
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[1] = -1;
	streamParameters.TSN_HardwareTableIndices.exTblruleId = -1;
	streamParameters.useStreamtable = false;
	streamParameters.usedCnt = 0;

}


void sesIp_Example(void) {

	TSN_ieee802Dot1cbStream_t streamParameters;
	uint8_t destinationMAC[6] = { 0x00, 0x11, 0x11, 0x11, 0x11, 0x11 };
	int ipSource[4] = {192,168,1,3};
	int ipDestination[4] = { 192,168,1,15 };

	/* IP stream identification */
	streamParameters.TSN_streamIdentity.identificationType = TSN_ip; 
	
	/* Assigning Desination MAC address */
	for (int i = 0; i < 6; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_ipStreamIdentification.destinationMac[i] = destinationMAC[i];
	}

	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_ipStreamIdentification.vlan = 100;
	
	/* Assigning IP address */
	for (int i = 0; i < 4; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_ipStreamIdentification.ipSource.TSN_ipv4Address[i] = ipSource[i];
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_ipStreamIdentification.ipDestination.TSN_ipv4Address[i] = ipDestination[i];
	}
	
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_ipStreamIdentification.dscp = 0x00;
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_ipStreamIdentification.nextProtocol = TSN_udp;
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_ipStreamIdentification.sourcePort = 0x0000;
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_ipStreamIdentification.destinationPort = 0x0000;
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_ipStreamIdentification.ipv4 = true;

	/* bit field mapped to physical egress ports for stream */
	streamParameters.portMap = SES_PORTMAP_PORT_1 | SES_PORTMAP_PORT_2; 
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[0] = -1;
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[1] = -1;
	streamParameters.TSN_HardwareTableIndices.exTblruleId = -1;
	streamParameters.useStreamtable = false;
	streamParameters.usedCnt = 0;
}


void sesMaskAndMatch_Example(void) {

	TSN_ieee802Dot1cbStream_t streamParameters;
	TSN_ieee802Dot1cbMaskAndMatch_t maskAndMatchParameters;
	uint8_t MaskMAC[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	uint8_t destinationMACMatch[6] = { 0x00, 0x66, 0x66, 0x66, 0x66, 0x66 };
	uint8_t sourceMACMatch[6] = { 0x00, 0x77, 0x77, 0x77, 0x77, 0x77 };

	/* Mask and match stream identification */
	streamParameters.TSN_streamIdentity.identificationType = TSN_maskAndMatch; 
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_maskAndMatchIdentification.TSN_identificationTtype.typeNumber = TSN_maskAndMatch;

	/* Assigning Source and Desination MAC mask */
	for (int i = 0; i < 6; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_maskAndMatchIdentification.destinationMacMask[i] = MaskMAC[i];
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_maskAndMatchIdentification.sourceMacMask[i] = MaskMAC[i];
	}

	/* Assigning Desination MAC address */
	for (int i = 0; i < 6; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_maskAndMatchIdentification.destinationMacMatch[i] = destinationMACMatch[i];
	}

	/* Assigning Source MAC address */
	for (int i = 0; i < 6; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_maskAndMatchIdentification.sourceMacMatch[i] = sourceMACMatch[i];
	}

	/* msduMatch size (2) + buffer (2) */
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_maskAndMatchIdentification.msduMaskLength = 2 + 2; 

	/* bit field mapped to physical egress ports for stream */
	streamParameters.portMap = SES_PORTMAP_PORT_1 | SES_PORTMAP_PORT_2; 
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[0] = -1;
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[1] = -1;
	streamParameters.TSN_HardwareTableIndices.exTblruleId = -1;
	streamParameters.useStreamtable = false;
	streamParameters.usedCnt = 0;

	maskAndMatchParameters.msduMask[0] = 0xFF;
	maskAndMatchParameters.msduMask[1] = 0xFF;
	maskAndMatchParameters.msduMask[2] = 0x00;
	maskAndMatchParameters.msduMask[3] = 0x00;
	/* Frame Ethertype - msduMatch[0:1] */
	maskAndMatchParameters.msduMatch[0] = 0x12;
	maskAndMatchParameters.msduMatch[1] = 0x34;
	maskAndMatchParameters.msduMatch[2] = 0x00;
	maskAndMatchParameters.msduMatch[3] = 0x00;
}

/* Enable Loop Protection (MSTP or Miss Return) before configuring Talker System */
int32_t sesFrerTalker_Example(void) {
	int32_t rv = 0;

	uint8_t destinationMAC[6] = { 0x00, 0x00, 0x00, 0x11, 0x11, 0x11 };

	TSN_ieee802Dot1cbFrer_t frerParameters;
	TSN_ieee802Dot1cbStream_t streamParameters;
	TSN_ieee802Dot1cbMaskAndMatch_t maskAndMatchParameters;

	memset(&frerParameters, 0, sizeof(TSN_ieee802Dot1cbFrer_t));
	memset(&streamParameters, 0, sizeof(TSN_ieee802Dot1cbStream_t));
	memset(&maskAndMatchParameters, 0, sizeof(TSN_ieee802Dot1cbMaskAndMatch_t));

	/* Stream table Parameters - Null Stream Identification */
	streamParameters.TSN_streamIdentity.identificationType = TSN_nullStream;

	/* Assigning Desination MAC address */
	for (int i = 0; i < 6; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_nullStreamIdentification.destinationMac[i] = destinationMAC[i];
	}

	/* VLAN ID 100 */
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_nullStreamIdentification.vlan = 100; 

	/* bit field mapped to physical egress ports for stream */
	streamParameters.portMap = SES_PORTMAP_PORT_1 | SES_PORTMAP_PORT_2; 
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[0] = -1;
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[1] = -1;
	streamParameters.TSN_HardwareTableIndices.exTblruleId = -1;
	streamParameters.useStreamtable = false;
	streamParameters.usedCnt = 0;

	/* frer parameters */
	frerParameters.TSN_sequenceGeneration.reset = false;
	frerParameters.TSN_sequenceRecovery.individualRecovery = false;

	/* Port where stream split is applied - Ingress traffic goes to this port */
	frerParameters.TSN_streamSplit.port = SES_PORT_0;

	frerParameters.TSN_HardwareTableIndices.individualRecoveryTblIdx = -1;
	frerParameters.TSN_HardwareTableIndices.sequenceGenerationTblIdx = -1;
	frerParameters.TSN_HardwareTableIndices.sequenceRecoveryTblIdx = -1;
	frerParameters.TSN_HardwareTableIndices.txTransformTblIdx = -1;

	/* Configure VLAN mode */
	rv = SES_SetVlanMode(100, 0xFFF);
	if (rv < SES_PORT_OK) {
		printf("SES_SetVlanMode :: %d\n", rv);
	}

	/* SES_MstpExcludeVlanFromSpanningTree:
	 * This function is used to exclude the VLAN from spanning tree.
	 * This is necessary to prevent the spanning tree from managing the VLAN
	 * when using spanning tree for loop protection.
	 */

	rv = SES_FrerConfigureTalkerProxyForStream(&frerParameters, &streamParameters, &maskAndMatchParameters);
	printf("sesFrerTalker_Example :: %d\n\r", rv);
	return rv;
}

/* Enable Loop Protection (MSTP or Miss Return) before configuring Listener System */
int32_t sesFrerListener_Example(void) {
	int32_t rv = 0;

	uint8_t destinationMAC[6] = { 0x00, 0x00, 0x00, 0x11, 0x11, 0x11 };
	
	TSN_ieee802Dot1cbFrer_t frerParameters;
	TSN_ieee802Dot1cbStream_t streamParameters;
	TSN_ieee802Dot1cbMaskAndMatch_t maskAndMatchParameters;

	memset(&frerParameters, 0, sizeof(TSN_ieee802Dot1cbFrer_t));
	memset(&streamParameters, 0, sizeof(TSN_ieee802Dot1cbStream_t));
	memset(&maskAndMatchParameters, 0, sizeof(TSN_ieee802Dot1cbMaskAndMatch_t));

	/* Stream table Parameters - Null Stream Identification */
	streamParameters.TSN_streamIdentity.identificationType = TSN_nullStream;
	
	/* Assigning Desination MAC address */
	for (int i = 0; i < 6; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_nullStreamIdentification.destinationMac[i] = destinationMAC[i];
	}

	/* VLAN ID 100 */
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_nullStreamIdentification.vlan = 100;

	/* Egress traffic on port 0 */
	streamParameters.portMap = SES_PORTMAP_PORT_0;
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[0] = -1;
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[1] = -1;
	streamParameters.TSN_HardwareTableIndices.exTblruleId = -1;
	streamParameters.useStreamtable = false;

	/* Configure frer */
	frerParameters.TSN_sequenceRecovery.algorithm = TSN_vector;
	frerParameters.TSN_sequenceRecovery.historyLength = 5;
	frerParameters.TSN_sequenceRecovery.resetTimeout = 0xffff;
	frerParameters.TSN_sequenceRecovery.takeNoSequence = false;
	frerParameters.TSN_sequenceRecovery.individualRecovery = false;

	frerParameters.TSN_HardwareTableIndices.individualRecoveryTblIdx = -1;
	frerParameters.TSN_HardwareTableIndices.sequenceGenerationTblIdx = -1;
	frerParameters.TSN_HardwareTableIndices.sequenceRecoveryTblIdx = -1;
	frerParameters.TSN_HardwareTableIndices.txTransformTblIdx = -1;

	/* Configure VLAN mode */
	rv = SES_SetVlanMode(100, 0xFFF);
	if (rv < SES_PORT_OK) {
		printf("SES_SetVlanMode :: %d\n", rv);
	}

	/* SES_MstpExcludeVlanFromSpanningTree:
	 * This function is used to exclude the VLAN from spanning tree.
	 * This is necessary to prevent the spanning tree from managing the VLAN
	 * when using spanning tree for loop protection.
	 */

	rv = SES_FrerConfigureListenerProxyForStream(&frerParameters, &streamParameters, &maskAndMatchParameters);
	printf("sesFrerListener_Example :: %d\n\r", rv);
	return rv;
}

/* Enable Loop Protection (MSTP or Miss Return) before configuring Relay System */
int32_t sesFrerRelay_Example(void) {
	int32_t rv = 0;

	uint8_t destinationMAC[6] = { 0x00, 0x00, 0x00, 0x11, 0x11, 0x11 };

	TSN_ieee802Dot1cbFrer_t frerParameters;
	TSN_ieee802Dot1cbStream_t streamParameters;
	TSN_ieee802Dot1cbMaskAndMatch_t maskAndMatchParameters;

	memset(&frerParameters, 0, sizeof(TSN_ieee802Dot1cbFrer_t));
	memset(&streamParameters, 0, sizeof(TSN_ieee802Dot1cbStream_t));
	memset(&maskAndMatchParameters, 0, sizeof(TSN_ieee802Dot1cbMaskAndMatch_t));

	/* Stream table Parameters - Null Stream Identification */
	streamParameters.TSN_streamIdentity.identificationType = TSN_nullStream;

	/* Assigning Desination MAC address */
	for (int i = 0; i < 6; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_nullStreamIdentification.destinationMac[i] = destinationMAC[i];
	}

	/* VLAN ID 100 */
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_nullStreamIdentification.vlan = 100;

	/* Egress traffic on port 0 */
	streamParameters.portMap = SES_PORTMAP_PORT_0;
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[0] = -1;
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[1] = -1;
	streamParameters.TSN_HardwareTableIndices.exTblruleId = -1;
	streamParameters.useStreamtable = false;
	streamParameters.usedCnt = 0;

	/* Configure frer */
	frerParameters.TSN_sequenceRecovery.algorithm = TSN_vector;
	frerParameters.TSN_sequenceRecovery.historyLength = 5;
	frerParameters.TSN_sequenceRecovery.resetTimeout = 0xffff;
	frerParameters.TSN_sequenceRecovery.takeNoSequence = false;
	frerParameters.TSN_sequenceRecovery.individualRecovery = false;

	/* Set to 0xFF or 255 for listener/relay operation */
	frerParameters.TSN_streamSplit.port = 0xFF;

	/* Listener operation */
	frerParameters.TagOperation = TSN_relayRemoveTag;
	frerParameters.TSN_HardwareTableIndices.individualRecoveryTblIdx = -1;
	frerParameters.TSN_HardwareTableIndices.sequenceGenerationTblIdx = -1;
	frerParameters.TSN_HardwareTableIndices.sequenceRecoveryTblIdx = -1;
	frerParameters.TSN_HardwareTableIndices.txTransformTblIdx = -1;

	/* Configure VLAN mode */
	rv = SES_SetVlanMode(100, 0xFFF);
	if (rv < SES_PORT_OK) {
		printf("SES_SetVlanMode :: %d\n", rv);
	}
	/* SES_MstpExcludeVlanFromSpanningTree:
	 * This function is used to exclude the VLAN from spanning tree.
	 * This is necessary to prevent the spanning tree from managing the VLAN
	 * when using spanning tree for loop protection.
	 */

	rv = SES_FrerConfigureRelaySystemForStream(&frerParameters, &streamParameters, &maskAndMatchParameters);
	printf("sesFrerRelay_Example :: %d\n\r", rv);
	return rv;
}

/* Enable Loop Protection (MSTP or Miss Return) before configuring FRER */
int32_t sesFrerIndividualRecovery_Example(void) {
	int32_t rv = 0;
	
	uint8_t destinationMAC[6] = { 0x00, 0x00, 0x00, 0x11, 0x11, 0x11 };

	TSN_ieee802Dot1cbFrer_t frerParameters;
	TSN_ieee802Dot1cbStream_t streamParameters;
	TSN_ieee802Dot1cbMaskAndMatch_t maskAndMatchParameters;

	memset(&frerParameters, 0, sizeof(TSN_ieee802Dot1cbFrer_t));
	memset(&streamParameters, 0, sizeof(TSN_ieee802Dot1cbStream_t));
	memset(&maskAndMatchParameters, 0, sizeof(TSN_ieee802Dot1cbMaskAndMatch_t));

	/* Stream table Parameters - Null Stream Identification */
	streamParameters.TSN_streamIdentity.identificationType = TSN_nullStream;

	/* Assigning Desination MAC address */
	for (int i = 0; i < 6; i++) {
		streamParameters.TSN_streamIdentity.TSN_parameters.TSN_nullStreamIdentification.destinationMac[i] = destinationMAC[i];
	}

	/* VLAN ID 100 */
	streamParameters.TSN_streamIdentity.TSN_parameters.TSN_nullStreamIdentification.vlan = 100;

	/* Egress traffic on port 0 */
	streamParameters.portMap = SES_PORTMAP_PORT_0;
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[0] = -1;
	streamParameters.TSN_HardwareTableIndices.dynTblIdx[1] = -1;
	streamParameters.TSN_HardwareTableIndices.exTblruleId = -1;
	streamParameters.useStreamtable = false;
	streamParameters.usedCnt = 0;

	/* Configure frer */
	frerParameters.TSN_sequenceRecovery.port = SES_PORTMAP_PORT_1 | SES_PORTMAP_PORT_2;
	frerParameters.TSN_sequenceRecovery.algorithm = TSN_match;
	frerParameters.TSN_sequenceRecovery.resetTimeout = 0xffff;
	frerParameters.TSN_sequenceRecovery.takeNoSequence = false;
	frerParameters.TSN_sequenceRecovery.individualRecovery = true;

	/* Set to 0xFF or 255 for listener/relay operation */
	frerParameters.TSN_streamSplit.port = 0xFF;

	/* Listener operation */
	frerParameters.TagOperation = TSN_relayTagNoOperation;
	frerParameters.TSN_HardwareTableIndices.individualRecoveryTblIdx = -1;
	frerParameters.TSN_HardwareTableIndices.sequenceGenerationTblIdx = -1;
	frerParameters.TSN_HardwareTableIndices.sequenceRecoveryTblIdx = -1;
	frerParameters.TSN_HardwareTableIndices.txTransformTblIdx = -1;

	/* Configure VLAN mode */
	rv = SES_SetVlanMode(100, 0xFFF);
	if (rv < SES_PORT_OK) {
		printf("SES_SetVlanMode :: %d\n", rv);
	}
	/* SES_MstpExcludeVlanFromSpanningTree:
	 * This function is used to exclude the VLAN from spanning tree.
	 * This is necessary to prevent the spanning tree from managing the VLAN
	 * when using spanning tree for loop protection.
	 */

	rv = SES_FrerConfigureRelaySystemForStream(&frerParameters, &streamParameters, &maskAndMatchParameters);
	printf("Configure Individual Recovery :: %d\n\r", rv);

	/* Configure frer */
	frerParameters.TSN_sequenceRecovery.port = SES_PORTMAP_PORT_1 | SES_PORTMAP_PORT_2;
	frerParameters.TSN_sequenceRecovery.algorithm = TSN_match;
	frerParameters.TSN_sequenceRecovery.resetTimeout = 0xffff;
	frerParameters.TSN_sequenceRecovery.takeNoSequence = false;
	frerParameters.TSN_sequenceRecovery.individualRecovery = false;

	rv = SES_FrerConfigureListenerProxyForStream(&frerParameters, &streamParameters, &maskAndMatchParameters);
	printf("Configure Sequence Recovery :: %d\n\r", rv);
	return rv;
}

int32_t sesFrerRecoveryStatistics_Example(void) {
	int32_t rv = 0;

	
	return rv;
}


void sesFrer_Example() {

	switch (FRER_CONFIG) {

	case 0:
		printf("Configuring FRER Talker :: %d", sesFrerTalker_Example());
		break;

	case 1:
		printf("Configuring FRER Listener :: %d", sesFrerListener_Example());
		break;

	case 2:
		printf("Configuring FRER Talker :: %d", sesFrerTalker_Example());
		printf("Configuring FRER Listener :: %d", sesFrerListener_Example());
		break;

	default:
		printf("Not an valid FRER Configuration!!");
		break;

	}
}


