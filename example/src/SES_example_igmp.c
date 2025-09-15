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

#include "SES_codes.h"
#include "SES_debug.h"
#include "SES_igmp.h"


void sesTestIgmpEnable_Example(void) {

	if (SES_IgmpEnable() != SES_OK) {
		printf("IGMP Init Error!!\n");
	}else
		printf("IGMP Start Success!!\n");
}



void sesTestIgmpDisable_Example(void) {

	if (SES_IgmpDisable() != SES_OK) {
		printf("IGMP Disable Error!!\n");
	}
	else
		printf("IGMP Disable Success!!\n");
}

void sesTestIgmpSetGroupTimeout_Example(uint32_t seconds) {

	if (seconds > 600 || seconds < 30) {
		printf("Wrong timer value :: %d\n", seconds);
	}
	else {
		if (SES_IgmpSetGroupTimeout(seconds) != SES_OK) {
			printf("Set group timeout error !!\n");
		}else
			printf("Set group timeout success !!\n");
	}
}

void sesTestIgmpSetRouterTimeout_Example(uint32_t seconds) {
	if (seconds > 300 || seconds < 1) {
		printf("Wrong timer value :: %d\n", seconds);
	}
	else {
		if (SES_IgmpSetRouterTimeout(seconds) != SES_OK) {
			printf("Set router timeout error !!\n");
		}
		else
			printf("Set router timeout success !!\n");
	}
}

void sesTestIgmpGetStatus_Example() {
	SES_igmpStatus_t status_p;
	if (SES_IgmpGetStatus(&status_p) == SES_OK) {
		printf("IGMP Status :: %d\n", status_p.enable);
		printf("groupMemberTimeout :: %d\n", status_p.groupMemberTimeout);
		printf("routerTimeout :: %d\n", status_p.routerTimeout);
	}
	else {
		printf("Erroe in get IGMP status API!!!\n");
	}
}

void sesIgmp_Example() {
	sesTestIgmpEnable_Example();
	sesTestIgmpGetStatus_Example();

}