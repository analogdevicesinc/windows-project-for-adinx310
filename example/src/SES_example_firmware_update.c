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

#include "SES_example_firmware_update.h"
#include "SES_configuration.h"
#include "SES_firmware_update.h"
#include "SES_firmware_update_examples.h"
#include "SES_codes.h"
#include "SES_debug.h"

extern uint8_t SES_firmware_g[];
extern uint32_t SES_firmwareLength_g;
extern uint8_t SES_bootloader_g[];
extern uint32_t SES_bootloaderLength_g;

void sesImageLoaderCallback_Example(uint8_t status);



/*This exmaple illustrate how to update the SES firmware by embedding the firmware character array into the build, 
* It will read the firmware from the charecter array and update the SES firmware.
*/

/*To use below example, ensure LINK_FIRMWARE_ARRAY is not disabled */
void sesImageLoaderSingleblock_Example(void) {


	/*int8_t SES_ImageLoader(sesID_t sesId,
                       SES_fwUpdateStatusCallback_tp statusCallback_p,
                       SES_fwUpdateRequestSetup_tp requestSetup_p,
                       void *param_p,
                       SES_getImgBlk_tp imgBlkRequestFunc_p);*/

	int8_t rv = 0;
	sesID_t sesId = 0;

	printf("Updating firmware in single block, reading Firmware for Character Array !! \n");
	printf("Firmware API call status :: %d\n",SES_ImageLoader(sesId, sesImageLoaderCallback_Example, NULL, NULL, GetImageBlockFromCharacterArray));
	
	
}


void sesFirmwareUpdateFileSytem_Example(void) {

	/*int8_t SES_ImageLoader(sesID_t sesId,
		SES_fwUpdateStatusCallback_tp statusCallback_p,
		SES_fwUpdateRequestSetup_tp requestSetup_p,
		void* param_p,
		SES_getImgBlk_tp imgBlkRequestFunc_p);*/

	/*@note GetImageBlockFromFile uses a file system implementation to read in blocks
		* of data from binary files representing the bootloader and firmware.To
		* use this example you must implement the porting layer functions defined
		* in SES_PORT_firmware_update.h.*/
	
	/**
	*@note SES_ImageLoadFromFileSetup- This function is optionally provided to the SES_ImageLoader call.In
	* this example the parameter provided to SES_ImageLoader is the path to
	* the firmware binary file.*/

	/*To read the firmware from the file system, ensure LINK_FIRMWARE_ARRAY is disabled and the 
	* porting layer functions defined in SES_PORT_firmware_update.h must be implemented.*/

	sesID_t sesId = 0; 
	char* path = "bin/firmware/ses-app.bin"; 
	SES_ImageLoader(sesId, sesImageLoaderCallback_Example, SES_ImageLoadFromFileSetup, path, GetImageBlockFromFile); 

}

/* Call Back Function */
void sesImageLoaderCallback_Example(uint8_t status) {

	switch (status) {
		case SES_IMAGE_SIZE_INVALID: {
			printf("FAIL - FWU SES_IMAGE_SIZE_INVALID\n");
			break;
		}
		case SES_DEVICE_NOT_RESPONDING: {
			printf("FAIL - FWU SES_DEVICE_NOT_RESPONDING\n");
			break;
		}
		case SES_FWU_BUSY: {
			printf("FAIL - FWU SES_FWU_BUSY\n");
			break;
		}
		case SES_SEC_HDR_VALIDATE_FAILED_RESPONSE: {
			printf("FAIL - FWU SES_SEC_HDR_VALIDATE_FAILED_RESPONSE\n");
			break;
		}
		case SES_IMG_HASH_INVALID_RESPONSE: {
			printf("FAIL - FWU SES_IMG_HASH_INVALID_RESPONSE\n");
			break;
		}
		case SES_ABORTED_BY_DEVICE: {
			printf("FAIL - FWU SES_ABORTED_BY_DEVICE\n");
			break;
		}
		case SES_STATUS_BL_HEADER_BIN_START: {
			printf("OK   - FWU(BL) 30%%\n");
			break;
		}
		case SES_STATUS_BL_HEADER_BIN_TRANSFERED: {
			printf("OK   - FWU (BL) 40%%\n");
			break;
		}
		case SES_STATUS_BL_IMAGE_BIN_START: {
			printf("OK   - FWU (BL) 50%%\n");
			break;
		}
		case SES_STATUS_BL_IMAGE_BIN_TRANSFERED: {
			printf("OK   - FWU (BL) 60%%\n");
			break;
		}
		case SES_STATUS_FW_HEADER_BIN_START: {
			printf("OK   - FWU (FW) 70%%\n");
			break;
		}
		case SES_STATUS_FW_HEADER_BIN_TRANSFERED: {
			printf("OK   - FWU (FW) 80%%\n");
			break;
		}
		case SES_STATUS_FW_IMAGE_BIN_START: {
			printf("OK   - FWU (FW) 90%%\n");
			break;
		}
		case SES_STATUS_FW_IMAGE_BIN_TRANSFERED: {
			printf("OK   - FWU (FW) 100%%\n");
			break;
		}
		case SES_STATUS_FW_UPDATE_INITIAL: {
			printf("OK   - Initial\n");
			break;
		}

		default: {
			printf("FAIL - FWU Invalid Firmware Update Status\n");
			break;
		}
	}
}


void sesFirmwareUpdate_Example(void) {
	if (MULTIPLE_BLOCK) {
		sesFirmwareUpdateFileSytem_Example();
	}
	else {
		sesImageLoaderSingleblock_Example();
	}
}
