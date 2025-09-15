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



#include <stdio.h>
#include <Windows.h>
#include "SES_PORT_interface.h"
#include "SES_interface_management.h"
#include "SES_configuration.h"
#include "SES_codes.h"


/*SES Configuration code*/
int32_t sesConfig(void) {

	int32_t rv;
	uint8_t sesPrimaryMac[6] = SES_PRIMARY_MAC;
	int interfaceId = NULL;
	sesID_t deviceId = NULL;

	/*
	*Port configuration for ADIN6310
	*/
	const SES_portInit_t portConfiguration6310[6] = {
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1300, {true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 2, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 4, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 8, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 9, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}}
	};

	/*
	*Port configuration for ADIN3310
	*/
	const SES_portInit_t portConfiguration3310[3] = {
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 2, SES_phySpeed1000,	SES_phyDuplexModeFull, SES_autoMdix } }
	};

	/*
	*Port configuration for Field Switch Board
	*/
	const SES_portInit_t portConfigurationFieldSwitch[6] = {
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1100, {true, 1, 0, SES_phySpeed10, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1100, {true, 1, 1, SES_phySpeed10, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1300, {true, 1, 6, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1300, {true, 1, 5, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1100, {true, 1, 2, SES_phySpeed10, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1100, {true, 1, 3, SES_phySpeed10, SES_phyDuplexModeFull, SES_autoMdix}}
	};

	/*
	*SES Configuration Over SPI
	*/
#ifdef ENABLE_SPI
	SES_driverFunctions_t driverFunctions = {
	.init_p = SES_PORT_SPI_Init,
	.release_p = SES_PORT_SPI_Release,
	.sendMessage_p = SES_PORT_SPI_SendMessage
	};

	SES_PORT_ft4222InitParams_t initParameter = {
		.baseLocationId = SES_PORT_SPI_SINGLE_FT4222,
		.chipSelect = 0,
		.spiMode = SES_PORT_SPI_singleMode
	};
	printf("SES Configuration Over SPI\n");
	rv = SES_Init();
	if (rv == SES_PORT_OK) {
		rv = SES_AddHwInterface(&initParameter, &driverFunctions, &interfaceId);
		if (rv == SES_PORT_OK) {
			rv = SES_AddDevice(interfaceId, sesPrimaryMac, &deviceId);
			if (rv == SES_PORT_OK) {
				if (FIELD_SWITCH)
					rv = SES_InitializePorts(SES_PORT_COUNT, portConfigurationFieldSwitch);
				else if (SES_PORT_COUNT == 6)
					rv = SES_InitializePorts(SES_PORT_COUNT, portConfiguration6310);
				else
					rv = SES_InitializePorts(SES_PORT_COUNT, portConfiguration3310);

}
			}
		}
		
	
#else 
	/*
	*SES Configuration Over Ethernet
	*/
	/*Host MAC address connected to SES*/
	uint8_t hostMac[6] = HOST_MAC;

	SES_driverFunctions_t driverFunctions = {
		.init_p = SES_PORT_ETH_Init,
		.release_p = SES_PORT_ETH_Release,
		.sendMessage_p = SES_PORT_ETH_SendMessage,
		.updateFilter_p = SES_PORT_ETH_UpdateFilter
	};
	printf("SES Configuration Over Ethernet\n");
	rv = SES_Init();
	if (rv == SES_PORT_OK) {
		rv = SES_AddHwInterface(hostMac, &driverFunctions, &interfaceId);
		if (rv == SES_PORT_OK) {
			rv = SES_AddDevice(interfaceId, sesPrimaryMac, &deviceId);
			if (rv == SES_PORT_OK) {

				if (FIELD_SWITCH) {
					rv = SES_InitializePorts(6, portConfigurationFieldSwitch);
				}
				else if (SES_PORT_COUNT == 6)
					rv = SES_InitializePorts(SES_PORT_COUNT, portConfiguration6310);
				else
					rv = SES_InitializePorts(SES_PORT_COUNT, portConfiguration3310);
			}
		}
	}

#endif
	return rv;
}

/*SES Configuration code*/


void sesGetAppInfo_Example() {

	SES_appInfo_t appInfo;
	printf("---------------------FIRMWARE DETAILS----------------------\n");
	SES_GetFirmwareInfo(&appInfo, sizeof(appInfo));
	printf("appInfoVersion :: %d\n", appInfo.appInfoVersion);
	printf("buildNumber :: %d\n", appInfo.buildNumber);
	printf("name :: %s\n", appInfo.name);
	printf("part Number :: %s\n", appInfo.partNum);
	printf("Version :: %s\n", appInfo.version);
	printf("-----------------------------------------------\n\n");

}

void sesProtocolInitialization_Example(void) {

	int input;

	if (DEFAULT_SWITCH) {
		printf("Initializing the switch with default configurations !!\n");
		sesLldpInit_Example();
		sesSingleASPtpInstance_Example();
		sesMstpStackStart_Example();

	}

	/*HSR/PRP Initialization*/
	else if (HSR_PRP) {
		sesHsrPrp_Example();
	}

	else {

		/*Time Syncronization Example*/
		if (TIME_SYNC) {
			sesTimeSync_Example();

		}
		/*Schedule Traffic Example*/
		if (SCHEDULED_TRAFFIC) {
			sesScheduledTrafficGuardBand_Example();
		}
		/*Frame Preemption Example*/
		if (FRAME_PREEMPTION) {
			sesSetPreemptionConfigurationStructure_Example();
		}
		/*Send List Example*/
		if (SENDLIST) {
			sesSendlist_Example();
		}
		/*FRER Example*/
		if (FRER) {
			sesFrer_Example();
		}
		/*PSFP Example*/
		if (PSFP) {
			sesPsfp_Example();
		}

		/*MRP Example*/
		if (MRP) {
			sesMrp_Example();
		}

		/*MSTP Example*/
		if (MSTP) {
			sesMultipleMsti_Example();
		}

	}

	/*Static Entry Installation*/

	/*Event Example*/
	if (EVENT) {
		sesEvent_Example();
	}

	/*LLDP Configuration*/
	if (LLDP_INIT) {
		sesLldpInit_Example();
	}

	/*Firmware Update Example*/
	if (FIRMWARE_UPDATE) {
		sesFirmwareUpdate_Example();
		Sleep(5000);
	}

	/*IGMP Configuration Example*/
	if (IGMP_SNOOPING) {
		sesIgmp_Example();
	}

	/*VLAN configuration Example*/
	if (VLAN_CONFIG) {
		sesVlan_Example();
	}

	/*Switch Example*/
	if (SWITCH_EXAMPLE) {
		sesSwitch_Example();
	}

	/*Layer 2 Rx/TX Example*/
	if (LAYER_2) {
		seslayer2_Example();
	}

	if (UPDATE_SOURCE_MAC) {
		sesUpdateMACAddress_Example();
	}

	if (TIME_SYNC) {
		
		while (1) {
			printf("\n");
			printf("*----------------Time Synch Read prameters  ------------- :: \n");
			
			printf("1: Read Port Specific Parameters \n");
			printf("2: Read CMLDS Specific Parameters  \n");
			printf("9: Exit\n");
			scanf("%d", &input);

			printf("Option Entered ::%d\n", input);
			
			if (input == 9) {
				break;
			}
			else {
				sesGetPtpParameters_Example(input);
			}

		}

	}
		
}