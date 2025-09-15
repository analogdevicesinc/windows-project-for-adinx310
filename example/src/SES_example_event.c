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
#include "SES_example_event.h"
#include "SES_event.h"
#include "SES_codes.h"
#include "SES_debug.h"
#include "SES_configuration.h"
#include "SES_lldp.h"

/* Call Back Functions */
static void sesEventCb_Example(sesID_t sesId, int32_t eventID, void* param_p);
static int32_t sesLldpEventCb_Example(sesID_t sesId, int32_t eventID, void* param_p);
static int32_t sesTimerEventCb(sesID_t sesId, int32_t eventID, void* param_p);


/*Link Event Example*/
int32_t sesLinkEvent_Example(void) {
	int32_t rv = 0;

	/*Subscribe to Link UP Event*/
	SES_eventId_t eventId = SES_linkUpEvent;
	rv = SES_SubscribeEvent(eventId, sesEventCb_Example);
	printf("SES_Subscribe link Up Event - %d \n", rv);

	/*Subscribe to Link Down Event*/
	eventId = SES_linkDownEvent;
	rv = SES_SubscribeEvent(eventId, sesEventCb_Example);
	printf("SES_Subscribe link Down Event - %d \n", rv);


	return rv;
}

void sesEventCb_Example(sesID_t sesId, int32_t eventID, void* param_p) {

	/* Retrieve the event parameters related to Link Events */
	SES_linkEventParam_t* captureParam = (SES_linkEventParam_t*)param_p; 
	switch (eventID)
	{
		case 0:
			printf("Handle Config Complete event\n");
			break;
		case 1:
			printf("Handle Link Up event for port :: %d\n", captureParam->port);
			break;
		case 2:
			printf("Handle Link Down event for port :: %d\n", captureParam->port); 
			break;
		case 3:
			printf("Handle MAC Address updated event\n");
			break;
		case 4:
			printf("Handle Port Config event\n");
			break;
		case 5:
			printf("Handle Network Sync event\n");
			break;
		case 6:
			printf("Handle Network Sync Ready event\n");
			break;
	}
}

/*LLDP Event Example
 * This example demonstrates LLDP event handling with two SES devices connected
 * in a daisy-chain configuration.
 *
 * For daisy-chain setup, refer the provoded example "sesETH_ETHInit_Example" in SES_example_init.c.
 *
 * The example subscribes to multiple LLDP-related events defined in SES_event.h.
 * The user must define a callback function on the host side to handle these events.
 */

int32_t sesEventLldp_Example(void) {
	int32_t rv = 0;

	SES_eventId_t eventId;

	rv = SES_MX_LLDP_Start(0);
	rv = SES_MX_LLDP_Start(1);

	eventId = SES_lldpNewNeighborEvent;
	rv = SES_SubscribeEvent(eventId, sesLldpEventCb_Example);
	printf("SES_Subscribe lldp NewNeighbor Event - %d \n", rv);

	eventId = SES_lldpNeighborShutdownEvent;
	rv = SES_SubscribeEvent(eventId, sesLldpEventCb_Example);
	printf("SES_Subscribe lldp Neighbor Shutdown Event - %d \n", rv);
	
	eventId = SES_lldpSomethingChangedRemoteEvent;
	rv = SES_SubscribeEvent(eventId, sesLldpEventCb_Example);
	printf("SES_Subscribe lldp Something Changed Remote Event - %d \n", rv);
	
	eventId = SES_lldpMibStatsChangedEvent;
	rv = SES_SubscribeEvent(eventId, sesLldpEventCb_Example);
	printf("SES_Subscribe lldp MibStats Changed Event - %d \n", rv);


	while (1) {
		Sleep(10000);
	};

	return rv;
}

int32_t sesLldpEventCb_Example(sesID_t sesId, int32_t eventID, void* param_p) {
	int32_t rv = 0;
	switch (eventID)
	{
		case SES_lldpNewNeighborEvent:
			printf("New Neighbor event\n");
			break;
		case SES_lldpNeighborShutdownEvent:
			printf("Neighbor Shutdown event\n");
			break;
		case SES_lldpSomethingChangedRemoteEvent:
			printf("Something Changed Remote event\n");
			break;
		case SES_lldpMibStatsChangedEvent:
			printf("Remote Statistics Changed event\n");
			break;
	}
	return rv;
}



/*Subscribe to Input Capture Event and configure Timer3 
* to be an input capture pin.When a rising edge is detected on Timer3,
* it will trigger an event and capture a timestamp.Use with the Timer 
* Event callback function to access the timestamp information
*/
void sesTimerEventTest_Example() {
	SES_eventId_t eventId = SES_inputCaptureEvent;
	/* gpio7 is Timer3
	*  TIMER3 TO TRIGGER CAPTURE OF TIMESTAMPS
	*  Timer Configuration
	*/
	SES_gpioTimerSignal_t signalTimer3 = SES_gpio7;
	SES_gpioTimerConfig_t config_p;
	if (SES_PORT_OK == SES_GetGpioTimerConfig(signalTimer3, &config_p, sizeof(config_p))) {
		config_p.gpioConfig.state = SES_gpioTimerEnabled;
		config_p.gpioConfig.direction = 1;
		config_p.timerMode = SES_timerModeCaptureIn;
		/*capture edge is rising edge when set to 1*/
		config_p.captureEdge = 1;
	}
	printf("SetGpioTimerConfigTimer3 :: %d\n", SES_SetGpioTimerConfig(signalTimer3, &config_p));
	if (0 <= SES_SubscribeEvent(eventId, sesTimerEventCb)) {
		printf("Timer Event Subscribed success!!");
	}
	while (1) {
		Sleep(10000);
	}
}

/*Event Callback*/
int32_t sesTimerEventCb(sesID_t sesId, int32_t eventID, void* param_p) {
	printf("Event ID :: %d\n", eventID);
	SES_inputCaptureEventParam_t* captureParam = (SES_inputCaptureEventParam_t*)param_p;
	printf("interfaceIdx - %d\n", captureParam->interfaceIdx);
	printf("capture - %d\n", captureParam->capture);
	printf("freeTimestamp - %llu\n", captureParam->freeTimestamp);
	printf("synt0Timestamp - %llu\n", captureParam->synt0Timestamp);
	printf("synt1Timestamp - %llu\n", captureParam->synt1Timestamp);
}


void sesEvent_Example() {

	switch (EVENT) {
	case 1: 
		printf("Enabling Link Event Example \n");
		sesLinkEvent_Example();
		break;
	case 2:
		printf("Enabling LLDP Event Example \n");
		sesEventLldp_Example();
		break;

	case 3: 
		printf("Enabling Timer Event Example\n");
		sesTimerEventTest_Example();
		break;
	default:
		printf("Invalid Input!!");
		break;
	}

}