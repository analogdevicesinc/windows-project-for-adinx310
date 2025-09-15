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
#include "SES_example_preemption.h"
#include "SES_preemption.h"
#include "SES_codes.h"
#include "SES_debug.h"


/* Example to set preemption configuration using preemption configuration structure */
void sesSetPreemptionConfigurationStructure_Example(void) {
	int32_t rv = SES_ERROR;
	SES_mac_t mac = SES_macPort5;

	TSN_ieee802_dot1q_frame_preemption_config_t config_p = {
		.preempt_enabled = true,            /* preempt_enabled */
		.ignore_peer = false,               /* ignore_peer */
		.verify_disable = false,            /* verify disable */
		.fragment_size = 0x00,              /* fragment_size */ 
		.verify_period = 20,                /* verify_period */
		.preemption_table = {
			[0] = { 0, TSN_ieee802_dot1q_frame_preemption_express },
			[1] = { 1, TSN_ieee802_dot1q_frame_preemption_preemptible },
			[2] = { 2, TSN_ieee802_dot1q_frame_preemption_express },
			[3] = { 3, TSN_ieee802_dot1q_frame_preemption_preemptible },
			[4] = { 4, TSN_ieee802_dot1q_frame_preemption_express },
			[5] = { 5, TSN_ieee802_dot1q_frame_preemption_preemptible },
			[6] = { 6, TSN_ieee802_dot1q_frame_preemption_express },
			[7] = { 7, TSN_ieee802_dot1q_frame_preemption_preemptible }
			}
	};
	rv = SES_PREEMPT_SetPreemptionConfig(mac, &config_p);
	printf("sesSetPreemptionConfigurationStructure_Example :: %d\n", rv);
}


/* Example to set preemption configuration using multiple preemption APIs */
void sesSetPreemptionConfigurationApi_Example(void) {
	int32_t rv = SES_ERROR;

	/* Port 5 */
	SES_mac_t mac = SES_macPort5;

	/* 1010 1010: Express queues: 7, 5, 3 and 1 */
	uint8_t express_queue_mask = 0xAA;

	/* Enable preemption support */
	rv |= SES_PREEMPT_SetSupport(mac, true);

	/* Do not ignore peer state */
	rv |= SES_PREEMPT_SetIgnorePeer(mac, false);

	/* Set min frag size to 64 bytes */
	rv |= SES_PREEMPT_SetMinFragmentSize(mac, 0x00);

	/* Set verify period to 20ms */  
	rv |= SES_PREEMPT_SetVerifyPeriod(mac, 20);

	/* Send verify messages */
	rv |= SES_PREEMPT_SetVerifyDisable(mac, false);

	/* Set the preemptible and expressqueues */
	rv |= SES_PREEMPT_SetExpressQueueMask(mac, express_queue_mask);

	/* Commit the changes into SES */
	rv |= SES_PREEMPT_ProcessSettings();

	printf("sesSetPreemptionConfigurationApi_Example :: %d\n", rv);
}

/* Example to disable preemption */
void sesDisablePreemption_Example(void) {
	int32_t rv = SES_ERROR; 
	
	/* Disable preemption support on physical port5 */
	rv |= SES_PREEMPT_SetSupport(SES_macPort5, false); 
	rv |= SES_PREEMPT_ProcessSettings();

	printf("sesDisablePreemption_Example :: %d\n", rv);
}

/* Example to get preemption statistics */
void sesGetPreemptionStatistics_Example(void) {

	int32_t rv = SES_ERROR;
	SES_mac_t mac = SES_macPort5;

	/* pointer to where to store the information */
	SES_preemptionStats_t stats_p; 
	rv = SES_PREEMPT_CollectStats(mac, &stats_p);

	printf("sesGetPreemptionStatistics_Example :: %d\n", rv);
	
}


