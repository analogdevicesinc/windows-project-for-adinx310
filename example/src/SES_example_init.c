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
#include <Windows.h>

#include "SES_PORT_interface.h"
#include "SES_interface_management.h"

#include "SES_switch.h"
#include "SES_lldp.h"
#include "SES_time_synchronization.h"
#include "SES_port_api.h"

#include "SES_example_init.h"
#include "SES_example_switch.h"
#include "SES_configuration.h"


#define SES_PORT_COUNT 6


int32_t sesETH_ETHInit_Example(void) {

#ifndef ENABLE_SPI



	int32_t rv = 0;
	int32_t result = 0;

	const SES_portInit_t portConfiguration[6] = {
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1300, {true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 2, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 4, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 8, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 9, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}}
	};

	const SES_portInit_t portConfigurationT[3] = {
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 2, SES_phySpeed1000,	SES_phyDuplexModeFull, SES_autoMdix } }
	};

	/* host mac address */
	uint8_t pc_addr[6] = { 0xAC, 0x91, 0xA1, 0x91, 0xAC, 0x97 }; 
	uint8_t device_a_mac[6] = { 0x7A, 0xC6, 0xBB, 0xAA, 0xAA, 0xAA };
	uint8_t device_b_mac[6] = { 0x7A, 0xC6, 0xBB, 0xBB, 0xBB, 0xBB };
	uint8_t device_c_mac[6] = { 0x7A, 0xC6, 0xBB, 0xCC, 0xCC, 0xCC };

	int* host_interfaceId = NULL;
	sesID_t* device_a_id = NULL;
	sesID_t* device_b_id = NULL;
	sesID_t* device_c_id = NULL;

	SES_driverFunctions_t driverFunctions = {
		.init_p = SES_PORT_ETH_Init,
		.release_p = SES_PORT_ETH_Release,
		.sendMessage_p = SES_PORT_ETH_SendMessage,
		.updateFilter_p = SES_PORT_ETH_UpdateFilter
	};


	SES_mac_t mac = SES_macPrimary;
	uint8_t device_a_addrBuf_p[6];
	uint8_t device_b_addrBuf_p[6];
	uint8_t device_c_addrBuf_p[6];
	int32_t len = 6;

	rv = SES_Init();
	if (rv == SES_PORT_OK) {
		rv = SES_AddHwInterface(pc_addr, &driverFunctions, &host_interfaceId);
		printf("SES_AddHwInterface - %d\n", rv);
		if (rv == SES_PORT_OK) {
			rv = SES_AddDevice(host_interfaceId, device_a_mac, &device_a_id);
			printf("SES_AddDevice - %d\n", rv);
			if (rv == SES_PORT_OK) {
				rv = SES_MX_InitializePorts(device_a_id, SES_PORT_COUNT, portConfiguration);
				printf("SES_MX_InitializePorts - %d\n", rv);
			}
		}
	}

	/* Link Up Delay */
	Sleep(5000);
	/* SES 2 - ETH  */
	if (rv == SES_PORT_OK) {
		rv = SES_AddDevice(host_interfaceId, device_b_mac, &device_b_id);
		printf("SES_AddDevice - %d\n", rv);
		if (rv == SES_PORT_OK) {
			rv = SES_MX_InitializePorts(device_b_id, 3, portConfigurationT);
			printf("SES_MX_InitializePorts - %d\n", rv);
		}
	}

	/* Link Up Delay */
	Sleep(5000);
	/* SES 2 - ETH */
	if (rv == SES_PORT_OK) {
		rv = SES_AddDevice(host_interfaceId, device_c_mac, &device_c_id);
		printf("SES_AddDevice - %d\n", rv);
		if (rv == SES_PORT_OK) {
			rv = SES_MX_InitializePorts(device_c_id, 6, portConfiguration);
			printf("SES_MX_InitializePorts - %d\n", rv);
		}
	}


	rv = SES_MX_GetMacAddress(device_a_id, mac, &device_a_addrBuf_p, len);
	printf("Reading device_a_id - %d\n", rv);
	rv = SES_MX_GetMacAddress(device_b_id, mac, &device_b_addrBuf_p, len);
	printf("Reading device_b_id - %d\n", rv);

	rv = SES_MX_GetMacAddress(device_c_id, mac, &device_c_addrBuf_p, len);
	printf("Reading device_c_id - %d\n", rv);

	printf("device_a_mac - "); 
	for (int i = 0; i < 6; i++) { 
		printf("%x", device_a_addrBuf_p[i]); 
		if (i < 5) {
			printf(" : "); 
		}
	}
	printf("\n"); 

	printf("device_b_mac - ");
	for (int i = 0; i < 6; i++) {
		printf("%x", device_b_addrBuf_p[i]);
		if (i < 5) {
			printf(" : ");
		}
	}
	printf("\n");

	printf("device_c_mac - ");
	for (int i = 0; i < 6; i++) {
		printf("%x", device_c_addrBuf_p[i]);
		if (i < 5) {
			printf(" : ");
		}
	}
	printf("\n");

	return rv;
#endif // ! ENABLE_SPI
}



/*QSPI Example*/ 
int32_t sesQSPIInit_Example(void) {

#ifdef ENABLE_SPI

	int32_t rv = 0;
	int32_t result = 0;

	const SES_portInit_t portConfiguration[6] = {
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1300, {true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 2, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 4, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 8, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 9, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}}
	};


	uint8_t sesPrimaryMac[6] = { 0x7A, 0xC6, 0xBB, 0x11, 0x11, 0x11 };
	int* interfaceId = NULL;
	sesID_t* deviceId = NULL;


	SES_driverFunctions_t driverFunctions = {
		.init_p = SES_PORT_SPI_Init,
		.release_p = SES_PORT_SPI_Release,
		.sendMessage_p = SES_PORT_SPI_SendMessage
	};

	SES_PORT_ft4222InitParams_t initParameter = {
		.baseLocationId = SES_PORT_SPI_SINGLE_FT4222,
		.chipSelect = 0,
		.spiMode = SES_PORT_SPI_quadMode
	};

	rv = SES_Init();
	if (rv == SES_PORT_OK) {
		rv = SES_AddHwInterface(&initParameter, &driverFunctions, &interfaceId);
		if (rv == SES_PORT_OK) {
			rv = SES_AddDevice(interfaceId, sesPrimaryMac, &deviceId);
			if (rv == SES_PORT_OK) {
				rv = SES_MX_InitializePorts(deviceId, SES_PORT_COUNT, portConfiguration);
			}
		}
	}

	printf("result - %d\n", rv);
	return rv; 
#endif // ENABLE_SPI
}


/* SES1--> SPI and SES2--> Ethernet
 * Ensure that the project is built in Debug mode and that both Ethernet and SPI dependencies are installed.
 * Uncomment the example below if building in Debug mode.
 */

/*
int32_t sesSpiEthInit_Example(void) {

	int32_t rv = 0;
	int32_t result = 0;

	const SES_portInit_t portConfiguration[6] = {
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1300, {true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 2, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 4, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 8, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 9, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}}
	};


	uint8_t sesPrimaryMac[6] = { 0x7A, 0xC6, 0xBB, 0x11, 0x11, 0x11 };
	uint8_t sesSecondaryMac[6] = { 0x7A, 0xC6, 0xBB, 0x22, 0x22, 0x22 };
	int* SPI_interfaceId = NULL;
	int* ETH_interfaceId = NULL;
	sesID_t* SPI_deviceId = NULL;
	sesID_t* ETH_deviceId = NULL;
 
	SES_driverFunctions_t SPI_driverFunctions = {
		.init_p = SES_PORT_SPI_Init,
		.release_p = SES_PORT_SPI_Release,
		.sendMessage_p = SES_PORT_SPI_SendMessage
	};

	SES_PORT_ft4222InitParams_t initParameter = {
		.baseLocationId = SES_PORT_SPI_SINGLE_FT4222,
		.chipSelect = 0,
		.spiMode = SES_PORT_SPI_singleMode
	};

	SES_driverFunctions_t ETH_driverFunctions = {
		.init_p = SES_PORT_ETH_Init,
		.release_p = SES_PORT_ETH_Release,
		.sendMessage_p = SES_PORT_ETH_SendMessage,
		.updateFilter_p = SES_PORT_ETH_UpdateFilter
	};

	rv = SES_Init();
	// SES 1 - SPI 
	if (rv == SES_PORT_OK) {
		rv = SES_AddHwInterface(&initParameter, &SPI_driverFunctions, &SPI_interfaceId);
		if (rv == SES_PORT_OK) {
			rv = SES_AddDevice(SPI_interfaceId, sesPrimaryMac, &SPI_deviceId);
			 printf("SES_AddDevice 1 - %d\n", rv);
			if (rv == SES_PORT_OK) {
				rv = SES_MX_InitializePorts(SPI_deviceId, SES_PORT_COUNT, portConfiguration);
			}
		}
	}
	Sleep(5000);
	// SES 2 - ETH 
	if (rv == SES_PORT_OK) {
		rv = SES_AddDevice(SPI_interfaceId, sesSecondaryMac, &ETH_deviceId);
		 printf("SES_AddDevice2 - %d\n", rv);
		if (rv == SES_PORT_OK) {
			rv = SES_MX_InitializePorts(ETH_deviceId, SES_PORT_COUNT, portConfiguration);
		}
	}
	printf("result - %d\n", rv);
	return rv;

}
*/


void sesInitTreeConfig_Example(void) {

#ifndef ENABLE_SPI
	int32_t rv = 0;
	int32_t result = 0;

	uint8_t macAddr_p[6] = { 0x7A, 0xC6, 0xBB, 0xFF, 0xFE, 0x00 };
	int16_t vlanId = 0x0FFF;

	uint8_t pc_addr[6] = { 0xAC, 0x91, 0xA1, 0x91, 0xAC, 0x97 }; // host mac address
	uint8_t device_a_mac[6] = { 0x7A, 0xC6, 0xBB, 0x11, 0x11, 0x11 };
	uint8_t device_b_mac[6] = { 0x7A, 0xC6, 0xBB, 0x22, 0x22, 0x22 };
	uint8_t device_c_mac[6] = { 0x7A, 0xC6, 0xBB, 0x23, 0x23, 0x23 };

	int host_interfaceId = NULL;
	sesID_t device_a_id = NULL;
	sesID_t device_b_id = NULL;
	sesID_t device_c_id = NULL;


	const SES_portInit_t portConfiguration[6] = {
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 1, SES_phyADIN1300, {true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 2, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 4, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 8, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}},
		{ 1, SES_rgmiiMode, { 0, 0, 0 }, 0, SES_phyADIN1300, {true, 0, 9, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix}}
	};
	const SES_portInit_t portConfigurationT[3] = {
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 0, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 1, SES_phySpeed1000, SES_phyDuplexModeFull, SES_autoMdix } },
			{ 1, SES_rgmiiMode,{ 0, 0, 0 }, 1, SES_phyADIN1300, { true, 0, 2, SES_phySpeed1000,	SES_phyDuplexModeFull, SES_autoMdix } }
	};

	SES_driverFunctions_t driverFunctions = {
		.init_p = SES_PORT_ETH_Init,
		.release_p = SES_PORT_ETH_Release,
		.sendMessage_p = SES_PORT_ETH_SendMessage,
		.updateFilter_p = SES_PORT_ETH_UpdateFilter
	};


	if (SES_PORT_OK == SES_Init()) {
		rv = SES_AddHwInterface(pc_addr, &driverFunctions, &host_interfaceId);
		printf("SES_AddHwInterface - %d\n", rv);
		if (SES_PORT_OK == SES_AddDevice(host_interfaceId, device_a_mac, &device_a_id)) {
			printf("SES_AddDevice Success \n");
			if (SES_PORT_OK == SES_MX_InitializePorts(device_a_id, SES_PORT_COUNT, portConfiguration)) {
				printf("SES_MX_InitializePorts\n");
			}

		}
	}

	/* Static table entry to configure Port 1 */
	if (SES_PORT_OK == SES_AddStaticTableEntry(&macAddr_p, vlanId, 0x02)) {
		Sleep(2000);
		if (SES_PORT_OK == SES_AddDevice(host_interfaceId, device_b_mac, &device_b_id)) {
			if (SES_PORT_OK == SES_MX_InitializePorts(device_b_id, 3, portConfigurationT)) {
				printf("Device B configured Success!!\n");
				printf("Remove Static Entry :: %d\n", SES_RmStaticTableEntry(&macAddr_p, vlanId, 0));
			}
		}
	}

	/* Static table entry to configure Port 2 */
	if (SES_PORT_OK == SES_AddStaticTableEntry(&macAddr_p, vlanId, 0x04)) {
		Sleep(2000);
		if (SES_PORT_OK == SES_AddDevice(host_interfaceId, device_c_mac, &device_c_id)) {
			if (SES_PORT_OK == SES_MX_InitializePorts(device_c_id, SES_PORT_COUNT, portConfiguration)){
				printf("Device C configured Success!!\n");
				printf("Remove Static Entry :: %d\n", SES_RmStaticTableEntry(&macAddr_p, vlanId, 0));
			}
		}
	}
#endif
}