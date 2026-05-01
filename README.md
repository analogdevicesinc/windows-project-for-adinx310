# ADINX310 Switch Demo - Windows

A minimal Windows-based demo application for initializing and configuring the ADINX310 Ethernet switch with HSR (High-availability Seamless Redundancy) or PRP (Parallel Redundancy Protocol) support.

## Overview

This project demonstrates the basic initialization and configuration of the ADINX310 switch with support for redundancy protocols. It provides a minimal implementation with only the essential headers and source files required for switch initialization.

## Features

- **Switch Initialization**: SPI and Ethernet-based initialization
- **6-Port Configuration**: Support for up to 6 ports with ADIN1300 PHY
- **RGMII Mode**: All ports configured in RGMII mode at 1000 Mbps full-duplex
- **HSR Support**: High-availability Seamless Redundancy DAN or RedBox SAN configuration
- **PRP Support**: Parallel Redundancy Protocol DAN or RedBox Mode 1 configuration
- **Node/ Proxy Node Table Visiblity** User can read Node table information 
- **Firmware Information**: Retrieve and display firmware version and build information

## Dependencies 
#### Resolving PCAP and SPI dependencies
To successfully execute the windows project, user need to resolve SPI and Ethernet (PCAP) related depedencies

- **winpcap/npcap:**

    - **1** Get the winpcap library from: [winpcap](https://www.winpcap.org/install/bin/WpdPack_4_1_2.zip) (Tested with version 4.1.2).
    - **2** Create new folder as winpcap inside lib and extract the conent of downloaded winpcap.
    - **3** Wireshark installation will automatically install NPCAP. While installing NPCAP, ensure that the Install NPCAP in WinPcap API-compatible Mode check box is selected.

- **ft42xx/libFT4222:**

-   The following dependencies must be resolved to ensure proper functionality when using the SPI interface. This Windows project uses the UMFT4222EV as an SPI dongle which can be plugged directly into the EVAL-ADIN6310EBZ or EVAL-ADIN6310T1LEBZ versions of board.

    - **1** Download FT4222 library files from: [FTDI D2XX Drivers](https://ftdichip.com/wp-content/uploads/2024/11/LibFT4222-v1.4.7.zip)
    - **2** Copy ftd2xx and LibFT4222 from “LibFT4222-v1.4.7\imports” to the lib folder of the windows project
    - **3** Copy LibFT4222-64.dll from “lib\LibFT4222\dll\amd64” to the root folder of the project
    - **4** Connect the device to a spare USB port on your PC. If the device is based on an FT2232 chip, the Microsoft composite device driver is automatically loaded first. 

## Project Structure

### Complete inc/src Tree (adinx310-driver and app) for minimum HSR_PRP application

## adinx310 Driver Library

Download the driver library package for ADIN6310/ADIN3310 from myAnalog account, This project is compatible with v5.5.0-Beta version. If you are npt getting Beta FW updates through myAnalogaccount, please reach out to adin6310@analog.com
If you are using with public release v5.1.0-GA, You need to change the HSR/PRR API to remove MIB_PRP_HSR_statisticOptions_t parameter.
After downloading the driver files, you need to select these relevant files mentioned below :


```text
adinx310-driver
    ses-proxy-srv
        inc:
            RPC_client_process.h
            RPC_data_types.h
            RPC_debug.h
            RPC_defines.h
            RPC_macros.h
        src:
            RPC_client_process.c
            RPC_init_api_sets.c

    ses-route-srv
        inc:
            SES_ROUTE_library.h
        src:
            SES_ROUTE_api.c

    ses-tsn-api-srv
        inc:
            SES_codes.h
            SES_debug.h
            SES_event.h
            SES_event_common.h
            SES_firmware_update.h
            SES_firmware_update_examples.h
            SES_firmware_update_internal.h
            SES_frame_api.h
            SES_frame_api_common.h
            SES_interface_management.h
            SES_port_api.h
            SES_prp_hsr.h
            SES_prp_hsr_common.h
            SES_switch.h
            SES_switch_common.h
            SES_switch_time.h
            SES_switch_time_common.h
        src:
            SES_api_sets.c
            SES_bootloader.c
            SES_event.c
            SES_event_data.c
            SES_event_smp_callback.c
            SES_firmware.c
            SES_firmware_update_control.c
            SES_firmware_update_examples.c
            SES_frame_api.c
            SES_frame_api_data.c
            SES_frame_api_smp_callback.c
            SES_prp_hsr.c
            SES_prp_hsr_data.c
            SES_prp_hsr_smp_callback.c
            SES_switch.c
            SES_switch_data.c
            SES_switch_smp_callback.c
            SES_switch_time.c
            SES_switch_time_data.c
            SES_switch_time_smp_callback.c

    smp-stk
        inc:
            SMP_debug.h
            SMP_eth_fork.h
            SMP_services.h
            SMP_stack_api.h
        src:
            SMP_eth_fork.c
            SMP_stack_api.c

    tsn-model-srv
        inc:
            TSN_ieee802_dot1cb_stream.h
            TSN_ieee802_dot1q_bridge.h
            TSN_ieee802_dot1q_types.h
            TSN_ietf_yang_types.h
            TSN_prp_hsr_model.h

app
    inc:
        README.md
        SES_PORT_firmware_update.h
        SES_PORT_interface.h
    src:
        main.c
        SES_PORT_ETH_interface.c
        SES_PORT_firmware_update.c
        SES_PORT_memory.c
        SES_PORT_semaphore.c
        SES_PORT_SPI_interface.c
```
## Configuration

### Switch Configuration
- **Port Count**: 6 ports (configurable via `SES_PORT_COUNT`)
- **PHY Type**: ADIN1300
- **Interface Mode**: RGMII / SGMII/Fiber
- **Speed**: 1000 Mbps
- **Duplex**: Full duplex
- **Auto-MDIX**: Enabled

### Redundancy Protocol Selection
Use the `PRP_HSR` macro to select the redundancy protocol:


## To use Fiber as a use case we need to change the port configuration

  In your SES_portInit_t portConfiguration you need to pass SES_sgmiiMode1000BaseSxLx in MII interface.