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
#include "SES_example_lldp.h"
#include "SES_lldp.h"
#include "SES_codes.h"


/* Initialize LLDP Stack and Start */
void sesLldpInit_Example(void) {
	
	if (SES_OK == SES_LLDP_Init()) {
		if (SES_OK == SES_LLDP_Start()) {
			printf("LLDP started Successfully\n");
		}
	}

}

int32_t sesLldpTxSendNow_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort0;
	rv = SES_LLDP_TxSendNow(mac);
	return rv;
}

int32_t sesLldpGetActivePeerIds_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	uint32_t peerIdMap_p;
	rv = SES_LLDP_GetActivePeerIds(mac, &peerIdMap_p);
	return rv;
}

int32_t sesLldpGetAdminConfig_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	SES_LLDP_adminConfig_t adminConfig_p;
	rv = SES_LLDP_GetAdminConfig(mac, &adminConfig_p);
	return rv;
}

int32_t sesLldpSetAdminConfig_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	SES_LLDP_adminConfig_t adminConfig_p = {
		.lldpAdminConfig = {
			.adminStatus = SES_LLDP_enabledRxTx,
			.msgFastTx = 1,
			.msgTxInterval = 30,
			.tlvsTxEnable = 0x00,
			.msgTxHold = 4,
			.notificationEnable = true,
			.reInitDelay = 2,
			.txCreditMax = 5,
			.txFastInit = 4,
			.peerSupPerPort = 4,
			.enableEndLldpduTlv = true
		},
		.destMacAddr = { 0x7A, 0xC6, 0xBB, 0x11, 0x11, 0x12}
	};
	rv = SES_LLDP_SetAdminConfig(mac, &adminConfig_p);
	return rv;
}


int32_t sesLldpUpdateTxTlv_Example(void) { 
	int32_t rv = 0; 
	SES_mac_t mac = SES_macPort0; 
	SES_LLDP_tlvIdentifier_t tlvId_p = { 
		.tlvType = 4, 
		.infoLen = 0 
	}; 	 	
	/* Update tlvType4 (Port Description TLV) to Analog Devices */
	uint8_t tlvData_p[14]= { 0x41, 0x6e, 0x61, 0x6c, 0x6f, 0x67, 0x20, 0x44, 0x65, 0x76, 0x69, 0x63, 0x65, 0x73	};
	uint16_t tlvDataLen = 14;

	rv = SES_LLDP_UpdateTxTlv(mac, &tlvId_p, &tlvData_p, tlvDataLen);
	return rv;
}



int32_t sesLldpRemoveTxTlv_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	SES_LLDP_tlvIdentifier_t tlvId_p = {
		.tlvType = 4,
		.infoLen = 0
	};

	rv = SES_LLDP_RemoveTxTlv(mac, &tlvId_p);
	return rv;
}

int32_t sesLldpQueryTxTlv_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	SES_LLDP_tlvQueryIn_t txTlvQueryIn_p = {
		.uPeerId = 0,
		.tlvId.tlvType = 4,
		.tlvId.infoLen = 0
	};
	SES_LLDP_tlvQueryOut_t txTlvQueryOut_p;

	uint8_t tlvData_p[18]= { 0x52, 0x65, 0x20, 0x49, 0x6E, 0x69, 0x74, 0x20, 0x64, 0x65,
								0x6C, 0x61, 0x79, 0x20, 0x69, 0x73, 0x20, 0x38 };
	uint16_t tlvDataLen = 18;

	rv = SES_LLDP_UpdateTxTlv(mac, &txTlvQueryIn_p.tlvId, &tlvData_p, tlvDataLen);
	rv = SES_LLDP_QueryTxTlv(mac, &txTlvQueryIn_p, &txTlvQueryOut_p);
	return rv;
}

int32_t sesLldpQueryRxTlv_Example(void) {

	int32_t rv = 0; 
	rv = SES_MX_LLDP_Start(1);
	SES_mac_t mac1 = SES_macPort2;
	SES_LLDP_tlvQueryIn_t txTlvQueryIn_p1 = {
		.uPeerId = 0,
		.tlvId.tlvType = 4,
		.tlvId.infoLen = 0
	};
	uint8_t tlvData_p1[18]= { 0x52, 0x65, 0x20, 0x49, 0x6E, 0x69, 0x74, 0x20, 0x64, 0x65,
								0x6C, 0x61, 0x79, 0x20, 0x69, 0x73, 0x20, 0x38 };
	uint16_t tlvDataLen1 = 18;
	rv = SES_MX_LLDP_UpdateTxTlv(1, mac1, &txTlvQueryIn_p1.tlvId, &tlvData_p1, tlvDataLen1);
	printf("SES_MX_LLDP_UpdateTxTlv - %d \n", rv);
	SES_mac_t mac = SES_macPort2;
	SES_LLDP_tlvQueryIn_t txTlvQueryIn_p = {
		.uPeerId = 1,
		.tlvId.tlvType = 4,
		.tlvId.infoLen = 0
	};
	SES_LLDP_tlvQueryOut_t txTlvQueryOut_p;
	SES_LLDP_tlvQueryOut_t txTlvQueryOut_p1;
	rv = SES_LLDP_QueryTxTlv(mac1, &txTlvQueryIn_p1, &txTlvQueryOut_p1);
	printf("SES_LLDP_QueryTxTlv1 - %d \n", rv);
	rv = SES_LLDP_QueryRxTlv(mac, &txTlvQueryIn_p, &txTlvQueryOut_p);
	printf("SES_LLDP_QueryTxTlv0 - %d \n", rv);
	
	return rv;
}

int32_t sesLldpTxEnable_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	uint16_t txInterval = 1000;
	bool enable = true;
	rv = SES_LLDP_TxEnable(mac, txInterval, enable);
	return rv;
}


int32_t sesCheckLldpTxEnabled_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort2;
	bool enabled_p;
	rv = SES_LLDP_TxEnabled(mac, &enabled_p); 
	return rv;
}
 
 

int32_t sesLLDPRxEnable_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	bool enable = true;
	rv = SES_LLDP_RxEnable(mac, enable);
	return rv;
}

int32_t sesCheckLLDPRxEnabled_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort2;
	bool enabled_p;
	rv = SES_LLDP_RxEnabled(mac, &enabled_p);
	return rv;
}


int32_t sesLLDPGetLocalSystemData_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	SES_LLDP_localSystemData_t localSysData_p;
	rv = SES_LLDP_GetLocalSystemData(mac, &localSysData_p);
	return rv;
}

int32_t sesLLDPGetRemoteStatistics_Example(void) {
	int32_t rv = 0;
	SES_LLDP_remoteStatistics_t remoteStats_p;
	rv = SES_LLDP_GetRemoteStatistics(&remoteStats_p);
	return rv;
}

int32_t sesLLDPGetTxStatistics_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	SES_LLDP_txStatistics_t txStats_p;
	rv = SES_LLDP_GetTxStatistics(mac, &txStats_p);
	return rv;
}

int32_t sesLLDPGetRxStatistics_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	SES_LLDP_rxStatistics_t rxStats_p;
	rv = SES_LLDP_GetRxStatistics(mac, &rxStats_p);
	return rv;
}

int32_t sesLLDPGetPortMac_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	uint8_t *addrBuf_p;
	rv = SES_LLDP_GetPortMac(mac, &addrBuf_p);
	return rv;
}

int32_t sesLLDPSetPortMac_Example(void) {
	int32_t rv = 0;
	SES_mac_t mac = SES_macPort5;
	uint8_t *addrBuf_p;
	rv = SES_LLDP_SetPortMac(mac, &addrBuf_p);
	return rv;
}

