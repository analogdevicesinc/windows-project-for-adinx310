/* 
 * Copyright 2024 Analog Devices, Inc.
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
#include <stdbool.h>
#include <stdio.h>


#include "SES_PORT_interface.h"
#include "SES_interface_management.h"
#include "SES_switch.h"
#include "SES_port_api.h"
#include "SES_prp_hsr.h"


//Control Macro for 6-port or 3-port switch 
#define SES_PORT_COUNT 6


//PRP: 1, HSR 0
#define PRP_HSR 0

// Following function is for initializing the sweith (ADIN6310) over Standard SPI.
int32_t SwitchInit_SPI(void) {

	int32_t rv = 0;

	//ADIN6310 per posrt configuration structure.
	const SES_portInit_t portConfiguration[6] = {
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1300, {true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 2, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 4, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 8, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 9, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}}
	};

	//ADIN3310 per posrt configuration structure.
	const SES_portInit_t portConfigurationT[3] = {
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 2, SES_phySpeed1000,	SES_phyDuplexModeFull, SES_autoMdix } }
	};

	uint8_t sesPrimaryMac[6] = { 0x7A, 0xC6, 0xBB, 0x33, 0x33, 0x33 };
	int interfaceId = NULL;
	sesID_t deviceId = NULL;


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

	rv = SES_Init();
	if (rv == SES_PORT_OK) {
		rv = SES_AddHwInterface(&initParameter, &driverFunctions, &interfaceId);
		if (rv == SES_PORT_OK) {
			rv = SES_AddDevice(interfaceId, sesPrimaryMac, &deviceId);
			if (rv == SES_PORT_OK) {
				if (SES_PORT_COUNT == 3) {
					rv = SES_MX_InitializePorts(deviceId, SES_PORT_COUNT, portConfigurationT);
					printf("Port Init %d\n", rv);
				}
				else {
					rv = SES_MX_InitializePorts(deviceId, SES_PORT_COUNT, portConfiguration);
					printf("Port Init %d\n", rv);
				}
			}
		}
	}


	return rv;
}
// Following function is for initializing the sweith (ADIN6310) over Ethernet.
int32_t SwitchInit_ETH(void) {

	int32_t rv;

	//ADIN6310 per posrt configuration structure.
	const SES_portInit_t portConfiguration[6] = {
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyUnmanaged, {true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 2, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 4, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 8, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 9, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}}
	};

	//ADIN3310 per posrt configuration structure.
	const SES_portInit_t portConfigurationT[3] = {
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 2, SES_phySpeed1000,	SES_phyDuplexModeFull, SES_autoMdix } }
	};

	//Host NIC MAC address
	uint8_t hostMac[6] = { 0xF8, 0xE4, 0x3B, 0x04, 0x4E, 0x87 };

	//Switch primary MAC address, this address will be associated to the switch Packet Assist Engine
	uint8_t sesPrimaryMac[6] = { 0x7A, 0xC6, 0xBB, 0x22, 0x22, 0x22 };

	int interfaceId = NULL;
	sesID_t deviceId = NULL;
	SES_driverFunctions_t driverFunctions = {
		.init_p = SES_PORT_ETH_Init,
		.release_p = SES_PORT_ETH_Release,
		.sendMessage_p = SES_PORT_ETH_SendMessage,
		.updateFilter_p = SES_PORT_ETH_UpdateFilter
	};

	rv = SES_Init();

	if (rv == SES_PORT_OK) {
		rv = SES_AddHwInterface(hostMac, &driverFunctions, &interfaceId);
		if (rv == SES_PORT_OK) {
			rv = SES_AddDevice(interfaceId, sesPrimaryMac, &deviceId);
			if (rv == SES_PORT_OK) {
				if (SES_PORT_COUNT == 3) {
					rv = SES_MX_InitializePorts(deviceId, SES_PORT_COUNT, portConfigurationT);
					printf("Port Init for ADIN3310 :: %d\n", rv);
				}
				else {
					rv = SES_MX_InitializePorts(deviceId, SES_PORT_COUNT, portConfiguration);
					printf("Port Init for ADIN6310 :: %d\n", rv);
				}
			}
		}
	}
	return rv;
}

// Retrieves and prints the firmware information of the switch.
void getSwitchFirmwareInfo() {

	SES_appInfo_t appInfo;

	printf("SES_MX_GetFirmwareInfo==> %d\n", SES_MX_GetFirmwareInfo(0, &appInfo, sizeof(appInfo)));
	printf("appInfoVersion==>%d\n", appInfo.appInfoVersion);
	printf("buildNumber==>%d\n", appInfo.buildNumber);
	printf("name==>%s\n", appInfo.name);
	printf("part Number==>%s\n", appInfo.partNum);
	printf("Version==>%s\n", appInfo.version);
}

//PRP Redbox box initialization function. This function initializes the switch in PRP mode with the specified configuration parameters. 
int32_t SwitchPRPredBoxstart_Init() {
	int32_t result = 0;
	MIB_PRP_HSR_redundancyType_t redundancyType = MIB_PRP_HSR_prpMode1;
	bool danpDevice = false;
	//Ports 1 and 2 are configured as LRE ports, and Port 0 as Host port (port C). Port 3, 4, 5 are configured as Interlink port 
	// Port C must be -1 if using SPI interface.
	MIB_PRP_HSR_lrePorts_t lrePorts_p = { 1, 2, 0 };
	MIB_PRP_HSR_rbInterlinkPorts_t rbInterlinkPorts_p = { 3,4,5,-1 };

	if (SES_PORT_COUNT == 3) {
		// No port Available for Interlink, so configuring all interlink ports to -1.
		printf("PRP initialzation for 3310\n");
		rbInterlinkPorts_p = (MIB_PRP_HSR_rbInterlinkPorts_t){ -1, -1, -1, -1 };
	}
	uint8_t macAddress_g[6] = { 0xAC, 0x91, 0xA1, 0x91, 0xAC, 0x97 };
	int32_t lreDupListResideMaxTime = 161;

	result = SES_PrpStart(redundancyType, danpDevice, &lrePorts_p, &rbInterlinkPorts_p, &macAddress_g, lreDupListResideMaxTime, MIB_PRP_HSR_fullStatistics);

	return result;
}

//HSR Redbox box initialization function. This function initializes the switch in HSR mode with the specified configuration parameters. 
int32_t SwitchHSRredBoxstart_Init() {
	int32_t result = 0;

	MIB_PRP_HSR_redundancyType_t redundancyType = MIB_PRP_HSR_hsr;
	MIB_PRP_HSR_switchEndNode_t lreSwitchingEndNode = MIB_PRP_HSR_hsrRedboxSan;
	//Ports 1 and 2 are configured as LRE ports, and Port 0 as Host port (port C). Port 3, 4, 5 are configured as Interlink port 
	// Port C must be -1 if using SPI interface.
	MIB_PRP_HSR_lrePorts_t lrePorts_p = { 1, 2, 0 };
	MIB_PRP_HSR_rbInterlinkPorts_t rbInterlinkPorts_p = { 3, 4, 5, -1 };

	if (SES_PORT_COUNT == 3) {
		// No port Available for Interlink, so configuring all interlink ports to -1.
		printf("HSR Initialization for 3310\n");
		rbInterlinkPorts_p = (MIB_PRP_HSR_rbInterlinkPorts_t){ -1, -1, -1, -1 };
	}

	uint8_t macAddress_g[6] = { 0xAC, 0x91, 0xA1, 0x91, 0xAC, 0x97 };
	int32_t lreDupListResideMaxTime = 161;

	result = SES_HsrStart(redundancyType, lreSwitchingEndNode, &lrePorts_p, &rbInterlinkPorts_p, &macAddress_g, lreDupListResideMaxTime, MIB_PRP_HSR_fullStatistics);

	return result;
}

int main(int argc, char* argv[])
{

	printf("\n--ADINX310 Switch Demo--\n");

	//To initialize over ethernet, use "SwitchInit_SPI"
	printf("SES init :: %d\n", SwitchInit_ETH());
	getSwitchFirmwareInfo();

	// PRP_HSR macro can be updated to initialize HSR or PRP 
	if (PRP_HSR) {
		printf("PRP Init :: %d\n", SwitchPRPredBoxstart_Init());
	}
	else {
		printf("HSR Init :: %d\n", SwitchHSRredBoxstart_Init());
	}


	return(0);
}





