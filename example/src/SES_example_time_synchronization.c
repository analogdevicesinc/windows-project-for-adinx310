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
#include <inttypes.h>
#include "SES_example_time_synchronization.h"
#include "SES_time_synchronization.h"
#include "SES_codes.h"
#include "SES_debug.h"
#include "SES_configuration.h"



uint8_t switchMac[6] = SES_PRIMARY_MAC;

void sesPtpDeletePtpInstance_Example(uint32_t instanceIndex) {
	printf("PtpDeletePtpInstance :: %d ststus :: %d\n", instanceIndex, SES_PtpDeletePtpInstance(instanceIndex));
}

void sesPtpGetNumberPtpInstances_Example(void) {
	printf("SES_PtpGetNumberPtpInstances :: %d\n", SES_PtpGetNumberPtpInstances());
}

void sesPtpSetDefaultDs_Example(void) {

	uint32_t instanceIndex = 0;
	TSN_ptp_default_ds_t default_ds;
	TSN_ptp_port_ds_t port_ds;

	printf("SES_PtpGetDefaultDs - %d\n", SES_PtpGetDefaultDs(instanceIndex, &default_ds));

	default_ds.instance_enable = 1;
	default_ds.gm_capable = 0;
	printf("SES_PtpSetDefaultDs - %d\n", SES_PtpSetDefaultDs(instanceIndex, &default_ds));

	printf("SES_PtpGetPortDs 1 - %d\n", SES_PtpGetPortDs(instanceIndex, 0, &port_ds));
	port_ds.port_state = 0;
	port_ds.delay_mechanism = TSN_ptp_delay_mechanism_p2p;
	port_ds.port_enable = 1;
	printf("SES_PtpSetPortDs 1 - %d\n", SES_PtpSetPortDs(instanceIndex, 0, &port_ds));
	
}




/*
 * The following example demonstrates the initialization of the PTP stack on the switch,
 * configuration of the P2P delay mechanism with a single PTP instance,
 * followed by the configuration of port-specific data structures.
 * 
 * 
 * To configure CMLDS delay mechanism, user need to set below parameters:
 *	- instanceType = TSN_ptp_instance_type_ptp_relay
 *	- delay_mechanism = TSN_ptp_delay_mechanism_common_p2p
 * CMLDS can also be enabled from SES_configuration.h
 * 
 */
void sesSingleASPtpInstance_Example(void) {

	
	if (SES_OK == SES_PtpStart()) {

		/* Configure CMLDS, Clock identity */
		const TSN_ptp_init_cmlds_ds_t initDs = { {switchMac[0], switchMac[1], switchMac[2], switchMac[3], switchMac[4], switchMac[5],  0xff, 0xff } };
		printf("SES_PtpInitCmlds :: %d\n", SES_PtpInitCmlds(&initDs));

		/* Create instance with all ports */
		TSN_ptp_instance_type_t instanceType = TSN_ptp_instance_type_ptp_relay;
		
		/* initDs_p parameters:: clock_identity, clock_number, domain_number */
		TSN_ptp_init_instance_ds_t initDs_p = { {switchMac[0], switchMac[1], switchMac[2], switchMac[3], switchMac[4], switchMac[5], 0x00, 0x00 }, 0, 0 };
		uint32_t instanceIndex_p;

		/* Enabling PTP on each port  */
		uint16_t numberPtpPorts = 6; 
		uint16_t linkPortNumber[6] = { 1, 2, 3, 4, 5, 6 }; 

		if (SES_PORT_COUNT == 3) {
			numberPtpPorts = 3;
			printf("PTP Ports :: %d\n", numberPtpPorts);
			uint16_t linkPortNumber_3310[3] = { 1, 2, 3 };
			printf("Create PTP instance ADIN3310 status :: %d\n", SES_PtpCreatePtpInstance(instanceType, numberPtpPorts, linkPortNumber_3310, &initDs_p, &instanceIndex_p));
		}
		else {
			printf("Create PTP instance ADIN6310 status :: %d\n", SES_PtpCreatePtpInstance(instanceType, numberPtpPorts, linkPortNumber, &initDs_p, &instanceIndex_p));
		}
		
		/* Initialize default_ds */
		uint32_t instanceIndex = 0;
		TSN_ptp_default_ds_t default_ds;
		TSN_ptp_current_ds_t current_ds;
		TSN_ptp_port_ds_t port_ds;

		printf("SES_PtpGetDefaultDs - %d\n", SES_PtpGetDefaultDs(instanceIndex, &default_ds));
		default_ds.instance_enable = 1;
		default_ds.gm_capable = 0;
		printf("SES_PtpSetDefaultDs - %d\n", SES_PtpSetDefaultDs(instanceIndex, &default_ds));


		/* Enable Instance 1 PTP Ports with P2P delay mechanism */
		printf("SES_PtpGetPortDs :: %d\n", SES_PtpGetPortDs(instanceIndex, 0, &port_ds));
		port_ds.delay_mechanism = TSN_ptp_delay_mechanism_p2p;
		
		//CMLDS delay configuration 
		if (CMLDS) {
			port_ds.delay_mechanism = TSN_ptp_delay_mechanism_common_p2p;
		}
		
		port_ds.port_enable = 1;
		
		
		for (int i = 0; i < numberPtpPorts; i++) {
			printf("Set Port DS for Port :: %d :: %d\n", i, SES_PtpSetPortDs(instanceIndex, i, &port_ds));
		}
	}
}

/*
 *  The following example demonstrates how to read various parameters
 *  related to the configured Time Sync profile, Port Data Structure,
 *  and CMLDS parameters.
 */
void sesGetPtpParameters_Example(int input) {

	TSN_ptp_default_ds_t default_ds;
	TSN_ptp_current_ds_t current_ds;
	TSN_ptp_port_ds_t port_ds;
	TSN_ptp_cmlds_link_port_ds_t cmlds_port_ds;
	TSN_ptp_cmlds_link_port_ds_t cmlds_p;

	TSN_ptp_parent_ds_t ds_p;

	char pState[10][20] = { " ", "initializing", "Faulty", "Disabled", "Listening", "Pre_Master", "Time_Transmitter", "Passive", "Uncalibrated", "TimeReceiver"};

	switch (input) {

	case 1:
		SES_PtpGetDefaultDs(0, &default_ds);
		int ports = default_ds.number_ports;
		printf("Number of ports :: %d\n", ports);

		for (int i = 0; i < ports; i++) {
			printf("Port :: %d\t", i);
			printf("SES_PtpGetPortDs :: %d\t", SES_PtpGetPortDs(0, i, &port_ds));
			printf("AS Capable :: %s\t", port_ds.as_capable ? "true" : "false");
			printf("Port State :: %s\t", pState[port_ds.port_state]);
			printf("Synch Status :: %s\t", port_ds.sync_locked ? "true" : "false");
			printf("Mean Link Delay :: %" PRId64 "ns\t", port_ds.mean_link_delay / 65535);
			SES_PtpGetParentDs((uint32_t) 0, &ds_p );
			printf("MAC Address:: ");
			for (int i = 0; i < 6; i++) {
				printf("%02X", ds_p.grandmaster_identity[i]);
				if (i < 5) {
					printf(":");
				}
			}printf("\n");

		}
		break;

	case 2:

		//Check port wise if CMLDS is active or not, retrieve Port wise CMLDS parameters 
		for (uint16_t i = 0; i < 3; i++) {
			SES_PtpGetCmldsLinkPortDs(i, &cmlds_p);
			printf("Cmlds Link Port %d :: %s \t ", i, cmlds_p.cmlds_link_port_enabled ? "true" : "false");
			if (cmlds_p.cmlds_link_port_enabled) {
				printf("Mean Link Delay : %" PRId64 "ns\n", cmlds_p.mean_link_delay / 65535);
			}
			else {
				printf("CMLDS False\n");
			}
		}
	
		break;

	default:
		printf("Invalid input !!\n");
		break;
	}

}

/**/
int32_t sesMultipleASPtpInstance_Example(void) {

	int32_t rv = 0;
	if (SES_OK != SES_PtpStart())
		return;

	/*Configure CMLDS, Clock identity */
	const TSN_ptp_init_cmlds_ds_t initDs = {
	.clock_identity = { switchMac[0], switchMac[1], switchMac[2], switchMac[3], switchMac[4], switchMac[5], 0xff, 0xff }
	};

	rv = SES_PtpInitCmlds(&initDs);
	printf("SES_PtpInitCmlds - %d\n", rv);

	/* Create instance with six ports */
	uint16_t numberPtpPorts1 = 6;
	uint16_t linkPortNumber1[6] = { 1, 2, 3, 4, 5, 6 };

	TSN_ptp_init_instance_ds_t initDs1 = {
	.clock_identity = { switchMac[0], switchMac[1], switchMac[2], switchMac[3], switchMac[4], switchMac[5], 0x00, 0x00 },
	/* Timer A */
	.clock_number = 0, 
	.domain_number = 0
	};

	uint32_t* instanceIndex1;
	rv = SES_PtpCreatePtpInstance(TSN_ptp_instance_type_ptp_relay, numberPtpPorts1, &linkPortNumber1, &initDs1, &instanceIndex1);
	printf("SES_PtpCreatePtpInstance - %d\n", rv);

	/* Initialize default_ds */
	TSN_ptp_default_ds_t default_ds;
	rv = SES_PtpGetDefaultDs(instanceIndex1, &default_ds);
	default_ds.instance_enable = 1;
	rv = SES_PtpSetDefaultDs(instanceIndex1, &default_ds);
	printf("SES_PtpSetDefaultDs - %d\n", rv);

	uint16_t numberPtpPorts2 = 2;
	uint16_t linkPortNumber2[2] = { 1, 2 };
	TSN_ptp_init_instance_ds_t initDs2 = {
	.clock_identity = { switchMac[0], switchMac[1], switchMac[2], switchMac[3], switchMac[4], switchMac[5], 0x00, 0x01 },
	/* Second instance must run from free running clock */
	.clock_number = 0x80000000, 
	.domain_number = 1
	};

	uint32_t* instanceIndex2;
	rv = SES_PtpCreatePtpInstance(TSN_ptp_instance_type_ptp_relay, numberPtpPorts2, &linkPortNumber2, &initDs2, &instanceIndex2);
	printf("SES_PtpCreatePtpInstance - %d\n", rv);

	rv = SES_PtpGetDefaultDs(instanceIndex2, &default_ds);
	default_ds.instance_enable = 1;
	rv = SES_PtpSetDefaultDs(instanceIndex2, &default_ds);
	printf("SES_PtpSetDefaultDs - %d\n", rv);

	/* Initialize port_ds */
	TSN_ptp_port_ds_t port_ds;
	rv = SES_PtpGetPortDs(instanceIndex1, 0, &port_ds);
	printf("SES_PtpGetPortDs 1 - %d\n", rv);

	/* Enable Instance 1 PTP Ports for all 6 ports */
	port_ds.delay_mechanism = TSN_ptp_delay_mechanism_common_p2p;
	port_ds.port_enable = 1;
	rv = SES_PtpSetPortDs(instanceIndex1, 0, &port_ds);
	printf("SES_PtpSetPortDs 1 - %d\n", rv);
	rv = SES_PtpSetPortDs(instanceIndex1, 1, &port_ds);
	printf("SES_PtpSetPortDs 6 - %d\n", rv);

	/* Enable Instance 2 PTP Ports for ports 2 & 3 */
	port_ds.delay_mechanism = TSN_ptp_delay_mechanism_common_p2p;
	port_ds.port_enable = 1;
	rv = SES_PtpSetPortDs(instanceIndex2, 0, &port_ds);
	printf("SES_PtpSetPortDs 1 - %d\n", rv);
	rv = SES_PtpSetPortDs(instanceIndex2, 1, &port_ds);
	printf("SES_PtpSetPortDs 2 - %d\n", rv);
	printf("ses_test_create_multiple_ptp_instance_example, rv - %d\n", rv);
	return rv;
}


// ================================================1588-2019 Example================================================================

/* The set of APIs to be called for creating a 1588 instance using the driver APIs are given below:
	o	SES_PtpStart() //To start the ptp-stk
	o	SES_PtpCreatePtpInstance() //To create a PTP instance
	o	SES_PtpSetDefaultDs() //To configure the default dataset
	o	SES_PtpSetPortDs() //To configure the port dataset. Must be called once per port
	o	SES_PtpSetTimestampCorrectionPortDs() //To configure the ingress and egress latency(PHY delay values). This must also be called once per port.
	o	Suggestion is to first get the PHY delay values by calling SES_GetPhyDelays() API and then call SES_PtpSetTimestampCorrectionPortDs by passing the read values.
*/

/* Configure Ordinary clcok */
void sesOrdinaryClock1588GM_Example(void) {

	int32_t rv = 0;
	uint32_t instanceIndex;
	TSN_ptp_default_ds_t default_ds;
	uint16_t numberPtpPorts = 1;
	uint16_t linkPortNumber[1] = { 1 };
	TSN_ptp_timestamp_correction_port_ds_t ds_p;
	int16_t rxDelay_p;
	int16_t txDelay_p;

	/* Initialize PTP Stack */
	if (SES_OK != SES_PtpStart()) {
		printf("PTP initialization failed !!\n");
		return;
	}

	/* Initialize Instance and its parameters */
	TSN_ptp_init_instance_ds_t init_s = {
	.clock_identity = { switchMac[0], switchMac[1], switchMac[2], switchMac[3], switchMac[4], switchMac[5], 0x00, 0x00 },
	.clock_number = 0,
	.domain_number = 0
	};
	rv = SES_PtpCreatePtpInstance(TSN_ptp_instance_type_oc, numberPtpPorts, linkPortNumber, &init_s, &instanceIndex);


	/* Initialize Deafault Data set */
	rv = SES_PtpGetDefaultDs(instanceIndex, &default_ds);
	default_ds.instance_type = TSN_ptp_instance_type_oc;
	default_ds.instance_enable = 1;

	/* Utilize Priority to make SES as GM, Lower value, higher priority */
	default_ds.priority1 = 128;
	default_ds.priority2 = 248;
	rv = SES_PtpSetDefaultDs(instanceIndex, &default_ds);
	printf("SES_PtpSetDefaultDs - %d\n", rv);


	/* PTP port data set Configuration */
	TSN_ptp_port_ds_t port_ds;
	rv = SES_PtpGetPortDs(instanceIndex, 0, &port_ds);
	port_ds.delay_mechanism = TSN_ptp_delay_mechanism_e2e,
		port_ds.port_enable = 1;

	printf("SES_PtpSetPortDs :: %d\n", SES_PtpSetPortDs(instanceIndex, 0, &port_ds));

	printf("Reading Phy Delays:: %d\n", SES_GetPhyDelays(SES_macPort0, &rxDelay_p, &txDelay_p));

	ds_p.egress_latency = txDelay_p;
	ds_p.ingress_latency = rxDelay_p;
	printf("Set PTP time stamp correction :: %d\n", SES_PtpSetTimestampCorrectionPortDs(instanceIndex, 0, &ds_p));


}

/* Configure Boundary clock */
void sesBoundaryClock1588_Example(void) {

	int32_t rv = 0;
	uint32_t instanceIndex;
	TSN_ptp_default_ds_t default_ds;
	uint16_t numberPtpPorts = 6;
	uint16_t linkPortNumber[6] = { 1,2,3,4,5,6 };
	TSN_ptp_timestamp_correction_port_ds_t ds_p;
	int16_t rxDelay_p;
	int16_t txDelay_p;

	/* Initialize PTP Stack */
	if (SES_OK != SES_PtpStart()) {
		printf("PTP initialization failed !!\n");
		return;
	}

	/* Initialize Instance and its parameters */
	TSN_ptp_init_instance_ds_t init_s = {
	.clock_identity = { switchMac[0], switchMac[1], switchMac[2], switchMac[3], switchMac[4], switchMac[5], 0x00, 0x00 },
	.clock_number = 0,
	.domain_number = 0
	};
	rv = SES_PtpCreatePtpInstance(TSN_ptp_instance_type_bc, numberPtpPorts, linkPortNumber, &init_s, &instanceIndex);


	/* Initialize Deafault Data set */
	rv = SES_PtpGetDefaultDs(instanceIndex, &default_ds);
	default_ds.instance_type = TSN_ptp_instance_type_bc;
	default_ds.instance_enable = 1;
	default_ds.priority1 = 248;
	default_ds.priority2 = 248;
	rv = SES_PtpSetDefaultDs(instanceIndex, &default_ds);
	printf("SES_PtpSetDefaultDs - %d\n", rv);


	/* PTP port data set Configuration */
	TSN_ptp_port_ds_t port_ds;
	rv = SES_PtpGetPortDs(instanceIndex, 0, &port_ds);
	port_ds.delay_mechanism = TSN_ptp_delay_mechanism_e2e,
		port_ds.port_enable = 1;

	/* Per port PTP instance configuration */
	for (int port = 0; port < 6; port++) {
		printf("SES_PtpSetPortDs for Port :: %d and rv :: %d\n", port, SES_PtpSetPortDs(instanceIndex, port, &port_ds));

		/*To configure the ingress and egress latency(PHY delay values). This must also be called once per port.*/
		printf("Reading Phy Delays:: %d\n", SES_GetPhyDelays(port + 1, &rxDelay_p, &txDelay_p));

		ds_p.egress_latency = txDelay_p;
		ds_p.ingress_latency = rxDelay_p;

		printf("Set PTP time stamp correction :: %d\n", SES_PtpSetTimestampCorrectionPortDs(instanceIndex, port, &ds_p));

		rxDelay_p = 0;
		txDelay_p = 0;
	}

}

/* Configure Transparent clock */
void sesTransparentClock1588E2E_Example(void) {

	int32_t rv = 0;
	uint32_t instanceIndex;
	TSN_ptp_default_ds_t default_ds;
	uint16_t numberPtpPorts = 6;
	uint16_t linkPortNumber[6] = { 1,2,3,4,5,6 };
	TSN_ptp_timestamp_correction_port_ds_t ds_p;
	int16_t rxDelay_p;
	int16_t txDelay_p;

	/* Initialize PTP Stack */
	if (SES_OK != SES_PtpStart()) {
		printf("PTP initialization failed !!\n");
		return;
	}


	/* Initialize PTP Instance and its parameters */
	TSN_ptp_init_instance_ds_t init_s = { 
	.clock_identity = { switchMac[0], switchMac[1], switchMac[2], switchMac[3], switchMac[4], switchMac[5], 0x00, 0x00 },
	.clock_number = 0, 
	.domain_number = 0 
	};
	rv = SES_PtpCreatePtpInstance(TSN_ptp_instance_type_e2e_tc, numberPtpPorts, linkPortNumber, &init_s, &instanceIndex); 


	/* Initialize Deafault Data set */
	rv = SES_PtpGetDefaultDs(instanceIndex, &default_ds); 
	default_ds.instance_type = TSN_ptp_instance_type_e2e_tc; 
	default_ds.instance_enable = 1; 
	rv = SES_PtpSetDefaultDs(instanceIndex, &default_ds); 
	printf("SES_PtpSetDefaultDs - %d\n", rv); 


	/*PTP port Data set Configuration */
	TSN_ptp_port_ds_t port_ds; 
	rv = SES_PtpGetPortDs(instanceIndex, 0, &port_ds); 
	port_ds.delay_mechanism = TSN_ptp_delay_mechanism_e2e, 
		port_ds.port_enable = 1; 

	/* Per port PTP instance configuration */
	for (int port = 0; port < 6; port++) {
		printf("SES_PtpSetPortDs for Port :: %d and rv :: %d\n", port, SES_PtpSetPortDs(instanceIndex, port, &port_ds));

		/*To configure the ingress and egress latency(PHY delay values). This must also be called per port.*/
		printf("Reading Phy Delays:: %d\n", SES_GetPhyDelays(port + 1, &rxDelay_p, &txDelay_p));

		ds_p.egress_latency = txDelay_p;
		ds_p.ingress_latency = rxDelay_p;

		printf("Set PTP time stamp correction :: %d\n", SES_PtpSetTimestampCorrectionPortDs(instanceIndex, port, &ds_p));
		rxDelay_p = 0;
		txDelay_p = 0;
	}
}

void sesTimeSync_Example(void) {

	switch (CLOCK_TYPE) {
	
	case 1:
		sesSingleASPtpInstance_Example();
		break;
	
	case 2:
		sesBoundaryClock1588_Example();
		break;
	
	case 3: 
		sesOrdinaryClock1588GM_Example();
		break;
	
	case 4: 
		sesTransparentClock1588E2E_Example();
		break;

	default:
		printf("Invalid Input!! \n");
		break;
		
	}

}


