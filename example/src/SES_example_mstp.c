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
#include "SES_example_mstp.h"
#include "SES_mstp.h"
#include "SES_codes.h"
#include "SES_debug.h"

/* Initialize LLDP Stack and Start */
int32_t sesMstpStackStart_Example(void) {
	int32_t rv = SES_ERROR;
	
	rv = SES_MstpStart();
	if (rv == SES_OK)
		printf("MSTP started successfully\n");
	else 
		printf("MSTP start fail\n");

	return rv;
}


int32_t sesMultipleMsti_Example(void){
	int32_t rv = SES_ERROR;

	uint8_t mstId0;
	uint8_t mstId1;
	uint8_t mstId2;
	char vlanIds1[3][SES_MSTP_VLAN_RANGE_NAME_LEN] = {"10-20", "50", "90-100"};
	char vlanIds2[2][SES_MSTP_VLAN_RANGE_NAME_LEN] = {"30", "40"};

	/* For first instance (CIST/MSTI0), all VLANs (0 to 4095) will be mapped
	 * and length and vlanIDs parameters will be ignored
	 */
	rv = SES_MstpCreateMstInstance(0x3f, 4096, NULL, NULL, &mstId0);
	
	/* portMap is applicable only for first instance (CIST) */
	rv = SES_MstpCreateMstInstance(NULL, 8192, 3, &vlanIds1, &mstId1);	
	rv = SES_MstpCreateMstInstance(NULL, 12288, 2, &vlanIds2, &mstId2);	
	rv = SES_MstpStart();

	return rv;
}

/* Array length set arbitrarily to 16 */
#define SES_VLAN_ID_ARRAY_LENGTH 16
int32_t sesGetVlanToMstiMap_Example(void){
	int32_t rv = SES_ERROR;
	
	uint8_t msti = 0;
	char vlanIds[SES_VLAN_ID_ARRAY_LENGTH][SES_MSTP_VLAN_RANGE_NAME_LEN]; 

	rv = SES_MstpGetVlanToMstiMap(msti, SES_VLAN_ID_ARRAY_LENGTH, &vlanIds);
	if( rv < SES_OK)
		printf("Get VLAN to MSTI Map Error :: %d\n", rv);

	/* Print Non-empty array element*/
	for (uint8_t i = 0; i < SES_VLAN_ID_ARRAY_LENGTH; i++){
		if (vlanIds[i][0] != '\0') {
			printf("%s\n", vlanIds[i]);
		}
	}

	return rv;
}

int32_t sesBridgeForwardDelay_Example(void){
	int32_t rv = SES_ERROR;
	/* Bridge Hello Time range: 1 to 10. Default value: 2.
	 * Bridge Max Age range: 6 to 40. Default value: 20.
	 * Bridge Forward Delay range: 4 to 30. Default value: 15.
	 * The bridge enforces the following relationship:
	 * 		2 x ( Bridge Forward Delay - 1 seconds ) >= Bridge Max Age
	 *		Bridge Max Age >= 2 x ( Bridge Hello Time + 1 seconds )
	 */
	uint16_t bridgeForwardDelay = 21;
	uint16_t bridgeMaxAge = 40;

	/* Start MSTP stack */
    rv = SES_MstpStart();
	if (rv == SES_OK) {
		/* Set Bridge Forward Delay */
		rv = SES_MstpSetBridgeForwardDelay(bridgeForwardDelay);
		if (rv < SES_OK)
			printf("SES_MstpSetBridgeForwardDelay :: %d\n", rv);
		/* Set Bridge Max Age */
		rv = SES_MstpSetBridgeMaxAge(bridgeMaxAge);
		if (rv < SES_OK)
			printf("SES_MstpSetBridgeMaxAge :: %d\n", rv);
	}

	return rv;
}