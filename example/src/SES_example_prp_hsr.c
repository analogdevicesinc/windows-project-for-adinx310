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

#include "SES_example_prp_hsr.h"
#include "SES_configuration.h"
#include "SES_prp_hsr.h"
#include "SES_vlan.h"
#include "SES_codes.h"
#include "SES_debug.h"


/* Start PRP (Parallel Redundancy Protocol) stack */
int32_t sesPrpStart_Example(int32_t portC) {
    int32_t rv = 0;

    /*SES_PrpStart(MIB_PRP_HSR_redundancyType_t redundancyType,
        bool danpDevice,
        MIB_PRP_HSR_lrePorts_t * lrePorts_p,
        MIB_PRP_HSR_rbInterlinkPorts_t * rbInterlinkPorts_p,
        uint8_t * lreMacAddress_p,
        int32_t lreDupListResideMaxTime);*/


    MIB_PRP_HSR_redundancyType_t redundancyType = MIB_PRP_HSR_prpMode1;
    bool danpDevice = true;
    /* For SPI interface, lreDanPortC must be -1 */
    MIB_PRP_HSR_lrePorts_t lrePorts_p = { 1, 2, portC };
    MIB_PRP_HSR_rbInterlinkPorts_t rbInterlinkPorts_p = { -1,-1,-1,-1 };
    /* If initializing PRP over ethernet, LRE MAC address must be the same as network interface MAC address */
#ifndef ENABLE_SPI
    uint8_t lreMacAddress[6] = HOST_MAC;
#else
    uint8_t lreMacAddress[6] = { 0x00, 0x00, 0x00, 0x11, 0x11, 0x11 };
#endif

    int32_t lreDupListResideMaxTime = 161;
    rv = SES_PrpStart(redundancyType, danpDevice, &lrePorts_p, &rbInterlinkPorts_p, &lreMacAddress, lreDupListResideMaxTime, MIB_PRP_HSR_fullStatistics);

    return rv;
}

/* Start PRP Redbox */
int32_t sesPrpRedboxStart_Example(int32_t portC) {
    int32_t rv = 0;

    /*SES_PrpStart(MIB_PRP_HSR_redundancyType_t redundancyType,
        bool danpDevice,
        MIB_PRP_HSR_lrePorts_t * lrePorts_p,
        MIB_PRP_HSR_rbInterlinkPorts_t * rbInterlinkPorts_p,
        uint8_t * lreMacAddress_p,
        int32_t lreDupListResideMaxTime);*/

    MIB_PRP_HSR_redundancyType_t redundancyType = MIB_PRP_HSR_prpMode1;
    bool danpDevice = false;
    /* For SPI interface, lreDanPortC must be -1 */
    MIB_PRP_HSR_lrePorts_t lrePorts_p = { 1, 2, portC };
    /* Configure Port 3 and Port 5 as interlink ports */
    MIB_PRP_HSR_rbInterlinkPorts_t rbInterlinkPorts_p = { 3,5,-1,-1 };
    /* If initializing PRP over ethernet, LRE MAC address must be the same as network interface MAC address */
#ifndef ENABLE_SPI
    uint8_t lreMacAddress[6] = HOST_MAC;
#else
    uint8_t lreMacAddress[6] = { 0x00, 0x00, 0x00, 0x11, 0x11, 0x11 };
#endif

    int32_t lreDupListResideMaxTime = 161;

    rv = SES_PrpStart(redundancyType, danpDevice, &lrePorts_p, &rbInterlinkPorts_p, &lreMacAddress, lreDupListResideMaxTime, MIB_PRP_HSR_fullStatistics);

    return rv;
}

/* Configure PRP ports as access ports and interlink ports as trunk ports */
int32_t sesPrpRedboxStartVlan_Example(int32_t portC) {
    int32_t rv = 0;

    MIB_PRP_HSR_redundancyType_t redundancyType = MIB_PRP_HSR_prpMode1;
    bool danpDevice = false;
    /* For SPI interface, lreDanPortC must be -1 */
    MIB_PRP_HSR_lrePorts_t lrePorts_p = { 1, 2, portC };
    /* Configure Port 3 and Port 5 as interlink ports */
    MIB_PRP_HSR_rbInterlinkPorts_t rbInterlinkPorts_p = { 3,5,-1,-1 };
    /* If initializing PRP over ethernet, LRE MAC address must be the same as network interface MAC address */
#ifndef ENABLE_SPI
    uint8_t lreMacAddress[6] = HOST_MAC;
#else
    uint8_t lreMacAddress[6] = { 0x00, 0x00, 0x00, 0x11, 0x11, 0x11 };
#endif
    
    int32_t lreDupListResideMaxTime = 161;

    /* Configure ports as trunk and access */
    printf("SES_SetVlanPortType 1 :: %d\n", SES_SetVlanPortType(SES_macPort1, 15, 15, 4, SES_vlanAccess)); 
    printf("SES_SetVlanPortType 2 :: %d\n", SES_SetVlanPortType(SES_macPort2, 15, 15, 4, SES_vlanAccess)); 
    printf("SES_SetVlanPortType 5 :: %d\n", SES_SetVlanPortType(SES_macPort5, 10, 20, 4, SES_vlanTrunk)); 


    rv = SES_PrpStart(redundancyType, danpDevice, &lrePorts_p, &rbInterlinkPorts_p, &lreMacAddress, lreDupListResideMaxTime, MIB_PRP_HSR_fullStatistics);

    return rv;
}

/* Start HSR (High-availability Seamless Redundancy) stack */
int32_t sesHsrStart_Example(int32_t portC) {
    int32_t rv = 0;

    /* int32_t SES_HsrStart(MIB_PRP_HSR_redundancyType_t redundancyType,
         MIB_PRP_HSR_switchEndNode_t lreSwitchingEndNode,
         MIB_PRP_HSR_lrePorts_t * lrePorts_p,
         MIB_PRP_HSR_rbInterlinkPorts_t * rbInterlinkPorts_p,
         uint8_t * lreMacAddress_p,
         int32_t lreDupListResideMaxTime);*/

    MIB_PRP_HSR_redundancyType_t redundancyType = MIB_PRP_HSR_hsr;
    MIB_PRP_HSR_switchEndNode_t lreSwitchingEndNode = MIB_PRP_HSR_hsrNode;
    /* For SPI interface, lreDanPortC must be -1 */
    MIB_PRP_HSR_lrePorts_t lrePorts_p = { 2, 1, portC };
    MIB_PRP_HSR_rbInterlinkPorts_t rbInterlinkPorts_p = { -1,-1,-1,-1 };
    /* If initializing HSR over ethernet, LRE MAC address must be the same as network interface MAC address */
#ifndef ENABLE_SPI
    uint8_t lreMacAddress[6] = HOST_MAC;
#else
    uint8_t lreMacAddress[6] = { 0x00, 0x00, 0x00, 0x11, 0x11, 0x11 };
#endif

    int32_t lreDupListResideMaxTime = 161;

    rv = SES_HsrStart(redundancyType, lreSwitchingEndNode, &lrePorts_p, &rbInterlinkPorts_p, &lreMacAddress, lreDupListResideMaxTime, MIB_PRP_HSR_fullStatistics);

    return rv;
}

/* Start HSR Redbox */
int32_t sesHsrRedboxStart_Example(int32_t portC) {
    int32_t rv = 0;

    /*
     *   int32_t SES_HsrStart(MIB_PRP_HSR_redundancyType_t redundancyType,
     *   MIB_PRP_HSR_switchEndNode_t lreSwitchingEndNode,
     *   MIB_PRP_HSR_lrePorts_t * lrePorts_p,
     *   MIB_PRP_HSR_rbInterlinkPorts_t * rbInterlinkPorts_p,
     *   uint8_t * lreMacAddress_p,
     *   int32_t lreDupListResideMaxTime);
     */

    MIB_PRP_HSR_redundancyType_t redundancyType = MIB_PRP_HSR_hsr;
    MIB_PRP_HSR_switchEndNode_t lreSwitchingEndNode = MIB_PRP_HSR_hsrRedboxSan;

    /* For SPI interface, lreDanPortC must be -1 */
    MIB_PRP_HSR_lrePorts_t lrePorts_p = { 2, 1, portC };

    /* Configure Port 3 and Port 5 as interlink ports */
    MIB_PRP_HSR_rbInterlinkPorts_t rbInterlinkPorts_p = { 3,5,-1,-1 };
    
    /* If initializing HSR over ethernet, LRE MAC address must be the same as network interface MAC address */
#ifndef ENABLE_SPI
    uint8_t lreMacAddress[6] = HOST_MAC;
#else
    uint8_t lreMacAddress[6] = { 0x00, 0x00, 0x00, 0x11, 0x11, 0x11 };
#endif

    int32_t lreDupListResideMaxTime = 161;

    rv = SES_HsrStart(redundancyType, lreSwitchingEndNode, &lrePorts_p, &rbInterlinkPorts_p, &lreMacAddress, lreDupListResideMaxTime, MIB_PRP_HSR_fullStatistics);

    return rv;
}

/* Configure LRE duplicate discard mode */
int32_t  sesDuplicateDiscardModeConfiguration_Example(void) {
    int32_t rv = 0;
    MIB_PRP_HSR_dupDiscard_t lreDuplicateDiscard = MIB_PRP_HSR_doNotDiscard;

    /* If LRE is set as RedBox, then configuring to do not discard is not
     * allowed and an error is returned.
     */
    rv = SES_SetLreDuplicateDiscard(lreDuplicateDiscard);

    return rv;
}

/* Add VLAN tag to supervision frames */
int32_t sesAddVlanSupervisionFrame_Example(void) {
    int32_t rv = 0;
    uint16_t portAVlanId = 10;
    uint8_t portAVlanPcp = 6;
    uint16_t portBVlanId = 20;
    uint8_t portBVlanPcp = 5;

    /* Ensure Port A and Port B are configured to allow VLAN tagged frames when calling this function */
    rv = SES_AddVlanSupervisionFrame(portAVlanId, portAVlanPcp, portBVlanId, portBVlanPcp);

    return rv;
}

/* Configure HSR mode - Default HSR mode is Mode H */
int32_t sesSetHsrMode_Example(void) {
    int32_t rv = 0;

    /* 
     * Mode T - removes the HSR tag before forwarding the frame
     * to the other port and shall send a frame from the host to
     * both ports, untagged and without discarding duplicates
     */
    MIB_PRP_HSR_operatingMode_t hsrMode = MIB_PRP_HSR_modeT;
    rv = SES_SetLreHsrMode(hsrMode);

    return rv;
}

/* Verify if PRP or HSR is currently executing */
int32_t sesVerifyRedundancyExecuting_Example(void) {
    int32_t rv = 0;

    bool checkRedundancy = false;
    
    rv = SES_VerifyReduExecuting(&checkRedundancy);
    printf("Redundancy Executing :: %s\n", checkRedundancy ? "True" : "False");

    return rv;

}

/* Retrieve status of LRE configuration */
int32_t sesGetLreStatus_Example(void) {
    int32_t rv = 0;
    MIB_PRP_HSR_lreStatus_t lreStatus_p;
    rv = SES_GetLreStatus(&lreStatus_p);

    printf("lreNodeType 				- %d\n", lreStatus_p.lreRedundancyType);
    printf("lreSwitchingEndNode 		- %d\n", lreStatus_p.lreSwitchingEndNode);
    printf("portA 						- %d\n", lreStatus_p.lrePorts.portA);
    printf("portB 						- %d\n", lreStatus_p.lrePorts.portB);
    printf("portC 						- %d\n", lreStatus_p.lrePorts.danPortC);
    printf("lreMacAddress 				- %d\n", lreStatus_p.lreMacAddress);
    printf("lreMacAddress 				- %d %d %d %d %d %d\n", lreStatus_p.lreMacAddress[0],
        lreStatus_p.lreMacAddress[1], lreStatus_p.lreMacAddress[2],
        lreStatus_p.lreMacAddress[3], lreStatus_p.lreMacAddress[4],
        lreStatus_p.lreMacAddress[5]);

    printf("lrePortAdminStateA 			- %d\n", lreStatus_p.lrePortAdminStateA);
    printf("lrePortAdminStateB 			- %d\n", lreStatus_p.lrePortAdminStateB);
    printf("lreDuplicateDiscard 		- %d\n", lreStatus_p.lreDuplicateDiscard);
    printf("lreTransparentReception 	- %d\n", lreStatus_p.lreTransparentReception);
    printf("lreEvaluateSupervision 		- %d\n", lreStatus_p.lreEvaluateSupervision);
    printf("lreNodesTableClear 			- %d\n", lreStatus_p.lreNodesTableClear);
    printf("lreDupListResideMaxTime 	- %d\n", lreStatus_p.lreDupListResideMaxTime);
    printf("lreSupervisionVidPortA 		- %d\n", lreStatus_p.lreSupervisionVidPortA);
    printf("lreSupervisionVlanPcpPortA 	- %d\n", lreStatus_p.lreSupervisionVlanPcpPortA);
    printf("lreSupervisionVidPortB 		- %d\n", lreStatus_p.lreSupervisionVidPortB);
    printf("lreSupervisionVlanPcpPortB 	- %d\n", lreStatus_p.lreSupervisionVlanPcpPortB);
    printf("lreLinkStatusA 				- %d\n", lreStatus_p.lreLinkStatusA);
    printf("lreLinkStatusB 				- %d\n", lreStatus_p.lreLinkStatusB);

    printf("sesGetLreStatus_Example :: %d\n\r", rv);

    return rv;
}

/* Retrieve Node table entries */
int32_t sesGetLreNodesEntry_Example(void) { 
    int32_t rv; 
    int32_t nodeCount = 0;

    MIB_PRP_HSR_lreNodesEntry_t lreNodesEntry_p; 
    MIB_PRP_HSR_lreStatistics_t lreStatistics_p;

    rv = SES_GetLreStatistics(&lreStatistics_p); 
    nodeCount = lreStatistics_p.lreCntNodes; 
    printf("*******************************************\n"); 
    printf("NodeCount = %d\n", nodeCount); 
    
    if (nodeCount > 0) { 
        for (int i = 1; i <= nodeCount; i++) 
        { 
            rv = SES_GetLreNodesEntry(i, &lreNodesEntry_p); 
            /* 
            * Handle to avoid reading aged-out entries while reading the entire table. 
            * If an entry has aged out during the read operation, the SES_GetLreNodesEntry 
            * will return -1. This situation must be handled by the user. 
            */ 
            if (rv < 0) { 
                continue; 
            } 
            else { 
                printf("---------SES_GetLreNodesEntry---------:: %d \n", rv); 
                printf("lreNodesIndex :: %d\n", lreNodesEntry_p.lreNodesIndex); 
                printf("lreTimeLastSeenA :: %d\n", lreNodesEntry_p.lreTimeLastSeenA); 
                printf("lreTimeLastSeenB :: %d\n", lreNodesEntry_p.lreTimeLastSeenB); 
                printf("lre Node Type :: %d\n", lreNodesEntry_p.lreRemNodeType); 
                /* 
                * The lreNodeReadTimeStamp parameter provides the timestamp when executing 
                * SES_GetLreNodesEntry for index 'i'. This helps the user verify the entry's 
                * aging and also track the corresponding API call. 
                */ 
                printf("lreNodeReadTimeStamp :: %d\n", lreNodesEntry_p.lreNodeReadTimeStamp); 
                printf("MAC Address:: "); 
                for (int i = 0; i < 6; i++) { 
                printf("%02X", lreNodesEntry_p.lreNodesMacAddress[i]); 
                if (i < 5) { 
                printf(":"); 
                } 
                }printf("\n"); 
            } 
        } 
    } 
    printf("*******************************************\n"); 
    return rv; 
}

/* Retrieve Proxy Node table entries */
int32_t sesGetLreProxyNodesEntry_Example(void) { 
    int32_t rv; 
    int32_t pNodeCount = 0;
    
    MIB_PRP_HSR_lreProxyNodeEntry_t lreProxyNodeEntry_p;
    MIB_PRP_HSR_lreStatistics_t lreStatistics_p; 

    rv = SES_GetLreStatistics(&lreStatistics_p); 
    pNodeCount = lreStatistics_p.lreCntProxyNodes; 

    printf("*******************************************\n"); 
    printf("ProxyNodeCount = %d\n", pNodeCount);

    if (pNodeCount > 0) { 
        for (int32_t i = 0; i <= pNodeCount; i++) 
        { 
            rv = SES_GetLreProxyNodeEntry(i, &lreProxyNodeEntry_p); 
            /* 
            * Handle to avoid reading aged-out entries while reading the entire table. 
            * If an entry has aged out during the read operation, the SES_GetLreProxyNodeEntry API 
            * will return -1. This situation must be handled by the user. 
            */ 
            if (rv < 0) { 
                continue; 
            } 
            else { 
                printf("SES_GetLrProxyeNodesEntry :: %d, lreProxyNodesIndex :: %d \n", rv, lreProxyNodeEntry_p.lreProxyNodeIndex); 
                printf("MAC Address:: "); 
                for (int i = 0; i < 6; i++) { 
                printf("%02X", lreProxyNodeEntry_p.lreProxyNodeMacAddress[i]); 
                if (i < 5) { 
                    printf(":"); 
                } 
                }printf("\n"); 
            } 
        } 
    } 
    printf("*******************************************\n"); 
    return rv; 
}

/* Set Supervision Frame MAC Address for PRP or HSR */
int32_t sesSetSupervisionFrameMAC_Example(void) {
    int32_t rv;
    /* MAC Address must be in range 01-15-4E-00-01-00 to 01-15-4E-00-01-ff */
    uint8_t macAddress_g[6] = { 0x01, 0x15, 0x4E, 0x00, 0x01, 0xFF };

    /* PRP or HSR must be configured and running */
    rv = SES_SetSupMacAddress(&macAddress_g);
    return rv;
}


/* Configure switch forward mode */
int32_t sesSetForwarding_Example(void) {
    int32_t rv = 0;
    MIB_PRP_HSR_cutThrough_t cutThrough = MIB_HSR_cutThrough;

    rv = SES_SetCutThroughForward(cutThrough);
    return rv;
}

/* Retrieve switch forwarding mode */
int32_t sesGetForwarding_Example(void) {
    int32_t rv = 0;
    MIB_PRP_HSR_cutThrough_t cutThrough_p;

    rv = SES_GetCutThroughForward(&cutThrough_p);
    printf("MIB_PRP_HSR_cutThrough_t :: %d\n", cutThrough_p);
    return rv;
}


void sesHsrPrp_Example(void) {
    printf("Initializing Redundancy protocol\n");

#ifndef ENABLE_SPI
    int32_t PortC = 0;
#else
    int32_t PortC = -1;
#endif

    switch (REDUNDANCY_TYPE) {

    case 0:
        printf("Initializing PRP \n");
        sesPrpStart_Example(PortC);
        break;
    case 1:
        printf("Initializing PRP Redbox\n");
        sesPrpRedboxStart_Example(PortC);
        break;

    case 2:
        printf("Initializing HSR \n");
        sesHsrStart_Example(PortC);
        break;

    case 3:
        printf("Initializing HSR Redbox\n");
        sesHsrRedboxStart_Example(PortC);
        break;

    default:
        printf("ERROR: Wrong input, please check SES_configuration.h!!!\n");
        break;

    }
}
