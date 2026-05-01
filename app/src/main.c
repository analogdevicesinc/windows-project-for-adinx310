/* 
 * Copyright 2026 Analog Devices, Inc.
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


/* User Input for HSR or PRP mode selection. Update the macro value to select the desired mode.
If you are using 6 port board you can use any of these modes; if you are using 3 port mode over Ethernet, then you can configure as 
PRP/HSR/REDBOX, but if you are using over SPI interface, you can only configure as PRP or HSR

   1: PRP
   2: PRP-REDBOX
   3: HSR
   4: HSR-REDBOX

*/

#define PRP_HSR 3


// Following function is for initializing the switch (ADIN6310) over Standard SPI.
int32_t SwitchInit_SPI(void) {

	int32_t rv = 0;

	//ADIN6310 per port configuration structure

/* {Port enable, MII, [RxDelay, txDelay, clk selection} , link polarity, PHY type, {autoneg, pullupctrl, phyAddr, Speed, Duplex, Crossover} */

	const SES_portInit_t portConfiguration[6] = {
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1300, {true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 2, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 4, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 8, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 9, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}}
	};

	//ADIN3310 per port configuration structure
	const SES_portInit_t portConfigurationT[3] = {
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 2, SES_phySpeed1000,	SES_phyDuplexModeFull, SES_autoMdix } }
	};

	/* Switch primary MAC address, this address will be associated to the switch Packet Assist Engine */
	uint8_t sesPrimaryMac[6] = { 0x7A, 0xC6, 0xBB, 0x22, 0x22, 0x22 };
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
/* Following function is for initializing the sweith (ADIN6310) over Ethernet. */
int32_t SwitchInit_ETH(void) {

	int32_t rv;

	/* ADIN6310 per port configuration structure */
	/* {Port enable, MII, [RxDelay, txDelay, clk selection} , link polarity, PHY type, {autoneg, pullupctrl, phyAddr, Speed, Duplex, Crossover} */

	const SES_portInit_t portConfiguration[6] = {
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyUnmanaged, {true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 2, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 4, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 8, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 9, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}}
	};

	/* ADIN3310 per port configuration structure */
	const SES_portInit_t portConfigurationT[3] = {
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 2, SES_phySpeed1000,	SES_phyDuplexModeFull, SES_autoMdix } }
	};

	/*
	 Host NIC MAC address, User must update the hostMac variable with the actual MAC address of the Host NIC which is connected to the
	 switch over Ethernet. This is required for the switch to send the response messages back to the host successfully.
	 */
	uint8_t hostMac[6] = { 0xAC, 0x91, 0xA1, 0x91, 0xAC, 0x97};

	/*Switch primary MAC address, this address will be associated to the switch Packet Assist Engine */
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

/* Retrieves and prints the firmware information of the switch. */
void getSwitchFirmwareInfo() {

	SES_appInfo_t appInfo;

	printf("SES_MX_GetFirmwareInfo==> %d\n", SES_MX_GetFirmwareInfo(0, &appInfo, sizeof(appInfo)));
	printf("appInfoVersion==>%d\n", appInfo.appInfoVersion);
	printf("buildNumber==>%d\n", appInfo.buildNumber);
	printf("name==>%s\n", appInfo.name);
	printf("part Number==>%s\n", appInfo.partNum);
	printf("Version==>%s\n", appInfo.version);
}

/*PRP Redbox box initialization function. This function initializes the switch in PRP mode with the specified configuration parameters. */
int32_t SwitchPRPstart_Init(bool redbox) {
	int32_t result = 0;
	MIB_PRP_HSR_redundancyType_t redundancyType = MIB_PRP_HSR_prpMode1;
	bool danpDevice = true;
	if (redbox) {
		danpDevice = false;
	}

	/*
	Ports 1 and 2 are configured as LRE ports, and Port 0 as Host port (port C).
	Port 3, 4, 5 will configured as Interlink port incase PRP-REDBOX configuration
	-- Port C must be -1 if using SPI interface.
	-- If ADIN3310 is used, there is no port available for Interlink, so configuring all interlink ports to -1.
	*/
	MIB_PRP_HSR_lrePorts_t lrePorts_p = { 1, 2, 0 };
	MIB_PRP_HSR_rbInterlinkPorts_t rbInterlinkPorts_p = { -1,-1,-1,-1 };

	if (redbox && SES_PORT_COUNT == 6) {
		printf("PRP-Redbox initialzation for 6310,\nPort 3,4,5 are configured as Interlink Ports\n");
		rbInterlinkPorts_p = (MIB_PRP_HSR_rbInterlinkPorts_t){ 3, 4, 5, -1 };
	}

	uint8_t macAddress_g[6] = { 0xAC, 0x91, 0xA1, 0x91, 0xAC, 0x97 };
	int32_t lreDupListResideMaxTime = 161;

	result = SES_PrpStart(redundancyType, danpDevice, &lrePorts_p, &rbInterlinkPorts_p, &macAddress_g, lreDupListResideMaxTime, MIB_PRP_HSR_fullStatistics);

	return result;
}

/* HSR Redbox box initialization function. This function initializes the switch in HSR mode with the specified configuration parameters. */
int32_t SwitchHSRstart_Init(bool redbox) {
	int32_t result = 0;

	MIB_PRP_HSR_redundancyType_t redundancyType = MIB_PRP_HSR_hsr;
	MIB_PRP_HSR_switchEndNode_t lreSwitchingEndNode = MIB_PRP_HSR_hsrNode;
	
	if (redbox) {
		 lreSwitchingEndNode = (MIB_PRP_HSR_switchEndNode_t) MIB_PRP_HSR_hsrRedboxSan;
	}

	/*
	Ports 1 and 2 are configured as LRE ports, and Port 0 as Host port (port C).
	Port 3, 4, 5 will configured as Interlink port incase HSR-REDBOX configuration
	-- Port C must be -1 if using SPI interface.
	-- If ADIN3310 is used, there is no port available for Interlink, so configuring all interlink ports to -1.
	*/

	MIB_PRP_HSR_lrePorts_t lrePorts_p = { 1, 2, 0 };
	MIB_PRP_HSR_rbInterlinkPorts_t rbInterlinkPorts_p = { -1, -1, -1, -1 };

	if (redbox && SES_PORT_COUNT == 6) {
		printf("HSR-Redbox initialzation for 6310,\nPort 3,4,5 are configured as Interlink Ports\n");
		rbInterlinkPorts_p = (MIB_PRP_HSR_rbInterlinkPorts_t){ 3, 4, 5, -1 };
	}

	uint8_t macAddress_g[6] = { 0xAC, 0x91, 0xA1, 0x91, 0xAC, 0x97 };
	int32_t lreDupListResideMaxTime = 161;

	result = SES_HsrStart(redundancyType, lreSwitchingEndNode, &lrePorts_p, &rbInterlinkPorts_p, &macAddress_g, lreDupListResideMaxTime, MIB_PRP_HSR_fullStatistics);

	return result;
}


/*Example to read Node table entries in PRP, PRP-Redbox, HSR and HSR-Redbox */
int32_t SwitchReadNodeEntry_Example() {
	int32_t result;
	int32_t nodeCount = 0;

	MIB_PRP_HSR_lreNodesEntry_t lreNodesEntry_p0;
	MIB_PRP_HSR_lreStatistics_t lreStatistics_p;

	result = SES_GetLreStatistics(&lreStatistics_p);
	nodeCount = lreStatistics_p.lreCntNodes;
	printf("*******************************************\n");
	printf("NodeCount =   %d\n", nodeCount);

	if (nodeCount > 0) {
		for (int i = 1; i <= nodeCount; i++)
		{
			result = SES_GetLreNodesEntry(i, &lreNodesEntry_p0);
			/*
			 * Handle to avoid reading aged-out entries while reading the entire table.
			 * If an entry has aged out during the read operation, the SES_GetLreProxyNodeEntry API
			 * will return -1. This situation must be handled by the user.
			 */
			if (result < 0) {
				continue;
			}
			else {
				printf("---------SES_GetLreNodesEntry---------::  %d \n", result);
				printf("lreNodesIndex   ::  %d\n", lreNodesEntry_p0.lreNodesIndex);
				printf("lreTimeLastSeenA :: %d\n", lreNodesEntry_p0.lreTimeLastSeenA);
				printf("lreTimeLastSeenB :: %d\n", lreNodesEntry_p0.lreTimeLastSeenB);
				printf("lre Node Type    :: %d\n", lreNodesEntry_p0.lreRemNodeType);
				/*
				 * The lreNodeReadTimeStamp parameter provides the timestamp when executing
				 * SES_GetLreNodesEntry for index 'i'. This helps the user verify the entry's
				 * aging and also track the corresponding API call.
				 */
				printf("lreNodeReadTimeStamp :: %d\n", lreNodesEntry_p0.lreNodeReadTimeStamp);
				printf("MAC Address:: ");
				for (int i = 0; i < 6; i++) {
					printf("%02X", lreNodesEntry_p0.lreNodesMacAddress[i]);
					if (i < 5) {
						printf(":");
					}
				}printf("\n");

			}
		}
	}
	printf("*******************************************\n");

	return result;
}

/*Example to read Proxy Node table entries in PRP-Redbox, HSR-Redbox */
int32_t SwitchReadProxyNodeEntry_Example() {
	int32_t result;
	int32_t pNodeCount = 0;

	MIB_PRP_HSR_lreNodesEntry_t lreNodesEntry_p0;
	MIB_PRP_HSR_lreProxyNodeEntry_t lreProxyNodeEntry_p;

	MIB_PRP_HSR_lreStatistics_t lreStatistics_p;
	result = SES_GetLreStatistics(&lreStatistics_p);
	pNodeCount = lreStatistics_p.lreCntProxyNodes;

	printf("*******************************************\n");
	printf("ProxyNodeCount =    %d\n", pNodeCount);

	if (pNodeCount > 0) {
		for (int i = 0; i <= pNodeCount; i++)
		{
			result = SES_GetLreProxyNodeEntry(i, &lreProxyNodeEntry_p);

			/*
			 * Handle to avoid reading aged-out entries while reading the entire table.
			 * If an entry has aged out during the read operation, the SES_GetLreProxyNodeEntry API
			 * will return -1. This situation must be handled by the user.
			 */

			if (result < 0) {
				continue;
			}
			else {
				printf("SES_GetLrProxyNodesEntry :: %d,  lreProxyNodesIndex :: %d \n", result, lreProxyNodeEntry_p.lreProxyNodeIndex);
				printf("MAC Address:: ");
				for (int i = 0; i < 6; i++) {
					printf("%02X", lreProxyNodeEntry_p.lreProxyNodeMacAddress[i]); // Print each byte in hex
					if (i < 5) {
						printf(":"); 
					}
				}printf("\n");
			}
		}
	}
	printf("*******************************************\n");

	return result;

}


int main(int argc, char* argv[])
{

	printf("\n--ADINX310 Switch Demo--\n");

	/* To initialize over ethernet, use "SwitchInit_SPI" */
	printf("SES init :: %d\n", SwitchInit_ETH());
	getSwitchFirmwareInfo();

	/* PRP_HSR macro can be updated to initialize HSR or PRP */

	switch (PRP_HSR)
	{
		case 1:
			printf("Initializing in PRP mode\n");
			SwitchPRPstart_Init(false);
			break;
		case 2:
			printf("Initializing in PRP Redbox mode\n");
			SwitchPRPstart_Init(true);
			break;
		case 3:
			printf("Initializing in HSR mode\n");
			SwitchHSRstart_Init(false);
			break;
		case 4:
			printf("Initializing in HSR Redbox mode\n");
			SwitchHSRstart_Init(true);
			break;
	default:
		break;
	}

	/*To read the Node Table Entry and Proxy Node table entries
	* uncomment below function calls. These functions are examples to read the Node table 
	and Proxy node table entries in PRP, HSR, PRP-Redbox and HSR-Redbox modes. 
	The user can modify these functions based on their requirement.
	*/

	/*
	SwitchReadNodeEntry_Example();
	SwitchReadProxyNodeEntry_Example();
	*/

	return(0);
}





