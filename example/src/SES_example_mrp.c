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
#include "SES_example_mrp.h"
#include "SES_mrp.h"
#include "SES_codes.h"
#include "SES_debug.h"


void sesStartMrp() {

	/* Initialize MRP with below befault configuration
		Ring Role * *: Client
		Recovery Rate * *: 500 ms
		Ring Ports * *: Port 1 & 2
		VLAN * *: No Vlan(0x0FFF)
		Priority * *: Default Manager / AutoManager priorities
		React On Link Change * *: Disabled*/


	printf("MRP Initilization :: %d\n", SES_MrpStart());

}




void sesGetInstanceConfig_Example() {

	/*Get the operational MRP instance configuration*/
	SES_mrpInstanceInfo_t config_p;
	if (SES_OK == SES_MrpGetInstanceConfig(&config_p)) {
		printf("MRP Ring Role :: %d\n", config_p.ringRole);
		printf("AutoManager Active Role :: %d\n", config_p.autoMgrActiveRole);
		printf("Ring State :: %d\n", config_p.ringState);
		printf("React on link change :: %d \n", config_p.reactOnLinkChange);
		printf("priority ::  %d\n", config_p.priority);
		printf("DomainVLANid ::  %d\n", config_p.domainVlanID);
		printf("Recovery Rate  ::  %d\n", config_p.recoveryRate);
		printf("isBlockedSupported ::  %d\n", config_p.isBlockedSupported);

		for (int i = 0; i < 3; i++) {
			printf("OUI %d :: %d :::: %x\n", i, config_p.oui[i], config_p.oui[i]);
		}

		for (int i = 0; i < 16; i++) {
			printf("domainUUID %d :: %d :::: %x\n", i, config_p.domainUUID[i], config_p.domainUUID[i]);
		}



	}
}



/*MRP configurationa nd Initilization 
Below Example first configure the MRP parameters and then initialize MPR protocol
*/

void sesMRPConfigAndInit_Example() {

	/*Ring Ports*/
	SES_mac_t rPort1Mac = SES_macPort2;
	SES_mac_t rPort2Mac = SES_macPort3;

	/*Ring Port Status*/
	SES_mrpPortInfo_t port1;
	SES_mrpPortInfo_t port2;


	SES_mrpInstanceInfo_t config_p = {
		.oui = {0x08,0x00,0x06},
		.domainUUID = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
		.reactOnLinkChange = 0,
		.isBlockedSupported = 1,
		.priority = 0x8000,
		.domainVlanID = 0x0FFF,
		.ringRole = SES_ringRoleManager,
		.autoMgrActiveRole = SES_ringRoleInactive,
		.recoveryRate = SES_recoveryRate200

	};

	/*Configure Ring ports and initialize MRP*/
	if (SES_OK == SES_MrpSetRingPorts(rPort1Mac, rPort2Mac)) {
		SES_MrpGetRingPortInfo(&port1, &port2);
		printf("Ring Port1 :: %d, Port 2 :: %d\n", port1.mac, port2.mac);

		if (SES_OK == SES_MrpSetInstanceConfig(&config_p)) {
			printf("MRP Initilization :: %d\n", SES_MrpStart());
		}
	}
}



void sesSetRingPorts_Example() {

	/* Set the domain ring ports */
	SES_mac_t rPort1Mac = SES_macPort2;
	SES_mac_t rPort2Mac = SES_macPort3;
	SES_mrpPortInfo_t port1;
	SES_mrpPortInfo_t port2;

	printf("SES_SetRingPorts Result :: %d\n", SES_MrpSetRingPorts(rPort1Mac, rPort2Mac));
	SES_MrpGetRingPortInfo(&port1, &port2);
	printf("Ring Port1 :: %d, Port 2 :: %d", port1.mac, port2.mac);
}

void sesGetDomainStatistics_Example() {

	SES_mrpStatistics_t stats_p;

	if (SES_OK == SES_MrpGetDomainStatistics(&stats_p)) {
		printf("MRP Stats ::\n");
		printf("ringOpenCount :: %d\n", stats_p.ringOpenCount);
		printf("lastRingOpenTimestamp :: %d\n", stats_p.lastRingOpenTimestamp);
		printf("roundTripDelaysMin :: %d\n", stats_p.roundTripDelaysMin);
		printf("roundTripDelaysMax :: %d\n", stats_p.roundTripDelaysMax);
	}
}

int32_t sesVerifyMrpEnabled_Example() {
	bool enabled_p;
	int32_t result = SES_MrpVerifyEnabled(&enabled_p);
	printf("SES_VerifyMrpEnabled :: %i\n", enabled_p);

	return result;

}

void sesSetMrpClient_Example() {
	/* Update the Role and reactOnLinkCahge parameter */
	SES_mrpInstanceInfo_t config_p;
	if (SES_OK == SES_MrpGetInstanceConfig(&config_p)) {
		config_p.ringRole = SES_ringRoleManager;
		//config_p.reactOnLinkChange = 0;
		printf("SES_SetInstanceConfig Status :: %d \n", SES_MrpSetInstanceConfig(&config_p));
	}
}

int32_t sesSetMrpManager_Example() {

	int32_t result = 0;
	SES_mrpInstanceInfo_t config_p;

	config_p.ringRole = SES_ringRoleManager;

	result = SES_MrpSetInstanceConfig(&config_p);

	if (result != 0) {
		printf("MRP Manager Set Failed!! result::%d\n", result);
	}
	else {
		printf("MRP Manager Set Success!! result::%d\n", result);
	}

	return result;
}

/*MRP configuration and Initialization, configure device as MRM, then start/initialize MRP protocol*/
void SES_MRPConfigMRM() {

	/* Port 1 and 2 will be configured as Ring ports */
	SES_mac_t rPort1Mac = SES_macPort1;
	SES_mac_t rPort2Mac = SES_macPort2;

	/* Ring Port Status */
	SES_mrpPortInfo_t port1;
	SES_mrpPortInfo_t port2;
	SES_mrpInstanceInfo_t config_p = {
	.oui = {0x08,0x00,0x06},
	.domainUUID = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
	.reactOnLinkChange = 1,
	.isBlockedSupported = 0,
	.priority = 0x8000,
	.domainVlanID = 0x0FFF,
	.ringRole = SES_ringRoleManager,
	.recoveryRate = SES_recoveryRate500
	};

	/*Configure Ring ports and initialize MRP*/
	if (SES_OK == SES_MrpSetRingPorts(rPort1Mac, rPort2Mac)) {
		SES_MrpGetRingPortInfo(&port1, &port2);
		printf("Ring Port1 :: %d, Port 2 :: %d\n", port1.mac, port2.mac);
		if (SES_OK == SES_MrpSetInstanceConfig(&config_p)) {
			printf("MRP Initialization :: %d\n", SES_MrpStart());
		}
	}
}


void sesMrp_Example() {

	printf("---------------------------------------------------------------------\n");
	printf("Initializing MRP with :: \nRing Role * *: Client\nRecovery Rate * *: 500 ms\nRing Ports * *: Port 1 & 2\nVLAN * *: No Vlan(0x0FFF)\n");
	printf("Priority * *: Default Manager / AutoManager\npriorities React On Link Change * *: Disabled\n");
	printf("---------------------------------------------------------------------\n");
	sesStartMrp();

}
