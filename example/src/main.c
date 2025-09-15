
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

#include <stdio.h>
#include <Windows.h>
#include "SES_example_config.h"
#include "SES_codes.h"


/*Main*/ 

int main(int argc, char* argv[])
{
	
	printf("\n--START SES--\n\n");

	/*Modify CONFIG_OVER_SPI if using SPI*/
	if (SES_OK == sesConfig()) {
		sesGetAppInfo_Example();
		printf("############ Configuring the Switch ###################\n");
		sesProtocolInitialization_Example();
	}
	else {          
		printf("SES initilization failed !!!!\n");
	}

 	printf("\n--END--\n"); 

	
    return(0);
}




