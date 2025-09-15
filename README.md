
# Overview:
___

This is a Windows-based project for the **[ADIN6310](https://www.analog.com/en/products/adin6310.html)/([ADIN3310](https://www.analog.com/en/products/adin3310.html))** 6 and 3-port Industrial Ethernet TSN switch. This is a Managed switch with a wealth of TSN and Redundancy features. In this project, a Windows platform acts as the host to configure the switch. This project can be used to understand the driver APIs for configuration and management of the switch functionality. The project serves as a reference to help users familiarize themselves with the implementation of driver APIs for all the features of the switch, prior to porting the driver to their own host platform.

The project includes multiple use-case examples demonstrating switch configuration on a Windows platform. It showcases the integration and usage of different communication interfaces, including Ethernet (MAC) and SPI (Standard, Dual, and Quad), to configure and interact with the switch.

Additionally, it provides configuration examples for all versions of ADI evaluation board harware, EVAL-ADIN6310EBZ, EVAL-ADIN3310EBZ, and the Field Switch EVAL-ADIN6310T1LEBZ, covering essential switch management functions such as initialization, port configuration, VLAN setup, and advanced TSN features. This ensures a structured and hands-on approach for developers to understand and deploy the switch in real-world applications.


# System Requirements:  
___

Ensure your system meets the following prerequisites:

1. **Operating System**: Windows 10 or later.  
2. **Software**: [e.g., Visual Studio or other dependencies].  
3. **adinx310 Driver Library**  

   - **3.1** Download the driver library package for **ADIN6310/ADIN3310** from the **[Software Resources](https://www.analog.com/en/products/adin6310.html#software-resources)** section on the **[Product Page](https://www.analog.com/en/products/adin6310.html)**. The same driver package is used for ADIN3310 and ADIN6310. 
   - **3.2** Copy the driver files to the `/project/adinx310-driver/` folder. The contents of this folder should look like this:  
     - `ses-proxy-srv`  
     - `ses-route-srv`  
     - `ses-tsn-api-srv`  
     - `ses-windows-port-srv`  
     - `smp-stk`  
     - `tsn-model-srv`  

4. **External Libraries (Third-party libraries)**  

   - **winpcap/npcap**:  
     - **4.1** Get the **winpcap** library from: [winpcap](https://www.winpcap.org/devel.htm) (Tested with version 4.1.2).  
     - **4.2** Download WinPcap 4.1.2 Developer's Pack.  
     - **4.3** Create new folder as winpcap inside lib and paste Include and Lib folders from the downloaded Developer’s pack
     - **4.4** `npcap` needs to be installed. You can install it through **Wireshark**. When installing NPCAP, ensure that the **Install Npcap in WinPcap API-compatible Mode** check box is selected. 

   - **ft42xx/libFT4222**:  [ Required if using SPI interface only ]

     The following dependencies must be resolved to ensure proper functionality when using the **SPI interface**. This Windows project uses the [UMFT4222EV](https://ftdichip.com/products/umft4222ev/) as an SPI dongle which can be plugged directly into the EVAL-ADIN6310EBZ or EVAL-ADIN6310T1LEBZ versions of board.

     - **4.5** Download FT4222 library files from: [FTDI D2XX Drivers](https://ftdichip.com/software-examples/ft4222h-software-examples/)  
     - **4.6** Download windows example 
     - **4.7** Copy ftd2xx and LibFT4222 from “LibFT4222-v1.4.7\imports” to the lib folder of the windows project 
     - **4.8** Copy dll contents of ftd2xx to outside the dll folder. 
     - **4.9** Copy LibFT4222-64.dll from “lib\LibFT4222\dll\amd64” to the root folder of the project
     - **5.0** Connect the device to a spare USB port on your PC. If the device is based on an **FT2232** chip, the Microsoft composite device driver is automatically loaded first.  
     


## Build Configurations  

The project can be built in the following two configurations:  

1. **Switch_Ethernet**  
   - In this configuration, SPI-related dependencies (`ft42xx/libFT4222`) are not required.  
   - Only **pcap** dependencies need to be installed.  
   - **Note**: While building the project in Switch_Ethernet configuration, ensure that SES_PORT_SPI_interface.c is excluded from the build 

2. **Switch_SPI**  
   - This configuration requires all dependencies, including `ft42xx/libFT4222`, to be installed.  
   - It works exclusively with the **FT4222 SPI interface**.  
   - Using a different SPI interface will require modifications in the **porting layer** defined in `SES_PORT_interface.h`.  
   - **Note**: While building the project in Switch_SPI configuration, ensure that SES_PORT_ETH_interface.c is excluded from the build

## Configuration and Features  

Once the project is successfully built, additional configurations can be adjusted for better functionality and understanding.  

The `SES_configuration.h` file contains various macros that can be used to **enable or disable** specific features. Before starting the configuration, the user must update the **HOST_MAC** macro with the MAC address of the NIC to which the switch is connected.

---

### Configuration Macros  

1. **ENABLE_SPI**  
   - To build the project in **Switch_SPI** mode, this macro must be enabled.  
   - All SPI-related dependencies must be resolved.  
   - The SPI mode (**StandardSPI, DualSPI, or QuadSPI**) can be configured in `SES_example_config.c` inside the `ses_config` function.  
   - By default, the project uses **StandardSPI**.  
   - If SPI is selected as the interface medium, the host strapping must be configured according to the Standard, Dual, or Quad mode specified in the **[Datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/adin3310-6310.pdf)** under the **HOST INTERFACE STRAPPING PINS** section.

2. **SES_PORT_COUNT**  
   - The project supports a **6-port switch (ADIN6310)** and a **3-port switch (ADIN3310)**.  
   - This macro must be set according to the switch used.  
   - The port configuration is available in `SES_example_config.c` for the respective switch.  

3. **SES_PRIMARY_MAC**  
   - This MAC address is assigned to the connected switches internal Packet Assist Engine, additionally each port gets automatically assigned a MAC address based off the primary MAC address.  
   - The Primary MAC is used throughout the session for communication with the switch when using an Ethernet host. The per port MAC addresses are used for the various per-port protocols such as **LLDP, PTP, MSTP, HSR, and PRP** 

4. **HOST_MAC**  
   - Contains the **host MAC address**.  
   - This must be configured as the user's network adapter MAC address.  
   - The MAC address can be obtained from the command prompt using `ipconfig` (Windows) or `ifconfig`/`ip a` (Linux).  

5. **DEFAULT_SWITCH**  
   - The switch initializes with the default configuration, enabling **LLDP, PTP, and MSTP**.  
   - To enable other features, set this macro to `false`.  

6. **EVENT**  
   - The switch supports multiple events that can be subscribed to by the host.  
   - When a subscribed event occurs, the switch triggers a callback function to notify the host.  
   - A detailed list of events can be found in `SES_event.h`.  
   - Possible values:  
     - `0`: Disabled  
     - `1`: Enable Link Event Example  
     - `2`: Enable LLDP Event Example  
     - `3`: Enable Timer Event Example  

7. **LAYER_2**  
   - This macro allows sending and receiving **Layer 2 packets** with different configurations:  
     - `0`: Disabled  
     - `1`: L2 Transmit  
     - `2`: Layer 2 Receive (Stack Processor by MAC)  
     - `3`: Layer 2 Receive (Stack Processor by Ethertype)  
     - `4`: Layer 2 Packet Received (Matching Ethertype)  
     - `5`: Layer 2 Packet Received (Matching MAC)  

8. **FRAME_PREEMPTION**  
   - Enables frame preemption capability.  
   - If enabled, Port 5 will use the following queue configuration:  
     ```
     Queue[0] -> Express  
     Queue[1] -> Preemptible  
     Queue[2] -> Express  
     Queue[3] -> Preemptible  
     Queue[4] -> Express  
     Queue[5] -> Preemptible  
     Queue[6] -> Express  
     Queue[7] -> Preemptible  
     ```  

9. **SCHEDULED_TRAFFIC**  
	- If enabled, scheduled traffic with guard band is configured for port 2 with a Cycle time of 1ms.
	- Gate will open for 300us for Odd queues, 600us for Even queues, and 100us for priority 7.

10. **IGMP_SNOOPING**  
    - If set to `1`, enables IGMP snooping.  
    - Also prints **GroupMemberTimeout** and **RouterTimeout**.  

11. **REDUNDANCY_TYPE**  
    - Defines the redundancy mode:  
      - `0`: HSR  
      - `1`: HSR REDBOX  
      - `2`: PRP  
      - `3`: PRP REDBOX  
    - If using an **Ethernet interface**, the **HSR/PRP ring ports** will be:  
      - **Port 1** → PORT A  
      - **Port 2** → PORT B  
      - **Port C** → Host port  
    - If using **SPI**, **Port C is not available**.  

12. **MRP (Media Redundancy Protocol)**  
    - Default configuration:  
      - **Ring Role**: Client  
      - **Recovery Rate**: 500 ms  
      - **Ring Ports**: Port 1 & Port 2  
      - **VLAN**: No VLAN (`0x0FFF`)  
      - **Priority**: Default Manager / AutoManager  
      - **Priorities React On Link Change**: Disabled  

13. **FIRMWARE_UPDATE**  
    - Firmware updates can be performed in **single or multiple blocks**.  
    - If enabled, multiple block updates can be configured using `MULTIPLE_BLOCK = 1`.  
    - Refer to the **FIRMWARE LOAD/UPDATE** section in the driver user guide for details.  

14. **TIME_SYNC**  
    - This macro can be enabled to understand following Time synchronization examples related to AS2020 and 1588-2019 profile.
		- CLOCK_TYPE 1: SES_Test_Single_PtpInstance
		- CLOCK_TYPE 2: Boundary clock example  
		- CLOCK_TYPE 3: Ordinary clock example
		- CLOCK_TYPE 4: Transparent clock example
    - **Note**: Once time synchronization is enabled, the user can also read various status parameters related to the time synchronization profile, such as Port State, Mean Link Delay, Sync Status, As-Capable status, and others.
 

15. **VLAN_CONFIG**  
	- Can be enabled for following VLAN examples:
	- If TRUNK_ACCESS = 0, Configuring Port 3 and port 4 in Learn and Forward Mode for VLAN ID 10
	- If TRUNK_ACCESS = 1, Trunk/Access example with following port configurations:
		- Port 0 → Host Port, No VLAN configuration 
		- Port 1 → Access port, VLAN ID 2, PCP 2
		- Port 2 → Access port, VLAN ID 3, PCP 2
		- Port 3 → Access port, VLAN ID 4, PCP 2
		- Port 4 → Access port, VLAN ID 5, PCP 2
		- Port 5 → Trunk port, VLN ID range 1-5, PCP 2

16. **LLDP_INIT**  
    - If enabled, it will initialize LLDP service and stack. 
	- This subscribes to all the necessary events, updates mandatory TLVs, and enables LLDP transmit and receive on all
	- the ports by default.

17. **FRER**  
    - If enabled, switch will be configured as Talker, Listener, or Both
	- FRER_CONFIG: 
		- `0`: Talker 
		- `1`: Listener 
		- `2`: Both

18. **SENDLIST**  
    - Set to 1 to enable a sendlist example with Port 5 used as a loopback port.
	- Registered frames will egress out of Port 3.

19. **PSFP**  
    - Can be enabled for the following PSFP examples:
		- `0` : Disable
		- `1` : Stream Filter Example
		- `2` : Stream Gate Example
		- `3` : Flow Meter Example

20. **MSTP (Multiple Spanning Tree Protocol)**  
    - Set to 1 to configure multiple MST instances and enabled MSTP stack. If MSTP stack is already enabled, an error will be returned.

21. **SWITCH_EXAMPLE**  
    - Can be enabled for the following examples:
		- `0` : Disable
		- `1` : Read Dynamic table Example
		- `2` : Read Port Statistics
		- `3` : StaticEntry installation 

22. **Replacing Source MAC address using TxTranform**
    - Enable UPDATE_SOURCE_MAC to replace the source MAC address of egress traffic on Port 1 and Port 2 when the destination address matches.
---


   



