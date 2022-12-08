# Modulation scheme for operating the OpenVLC platform in the Visible Light and Infrared bands

This repository contains the software (Driver), firmware (PRU), and hardware (Design and Gerber files) implementing a new modulation scheme for the OpenVLC platform, which combines transmissions in the Visible Light (VL) and Infrared (IR) bands to provide larger dimming ranges without affecting the communication performance. Our paper "Visible Light or Infrared? Modulating LiFi for Dual Operation in the Visible and Infrared Spectra," published in WONS 2023, provides details on the proposed modulation scheme.

## Repository content 

The content of this repository is organized as follows:
* Driver folder: Contains the OpenVLC driver interfacing the MAC layer in OpenVLC with the upper layer of the OSI model (Network, Transport, and Application layers)
* PRU folder: Contains the firmware implementing the TX and RX chains in OpenVLC. For the TX chain, one of the following options should be selected depending on the desired dimming level:
    * TX_VL_IR_Dimming_0 --> 0% Dimming (As in OpenVLC, only the VL spectra is used)
    * TX_VL_IR_Dimming_25 --> 25% Dimming 
    * TX_VL_IR_Dimming_50 --> 50% Dimming 
    * TX_VL_IR_Dimming_75 --> 75% Dimming 
    * TX_VL_IR_Dimming_100 --> 100% Dimming (Only the IR spectra is used)
* Hardware: Contains the Design and Gerber files for the new OpenVLC cape that integrates both VL and IR LEDs.

## Designed cape and pinout

The image below shows the pinout of the BeagleBone Black for the new firmware, and the new cape for combined transmissions in the VL and IR bands, including both the VL and IR LEDs. As shown, the VL and IR signals are sent out through pins P8_45 and P9_46, respectively.

<p align="center">
  <img src="https://github.com/openvlc/OpenVLC/blob/0ad4af993fdec1f5115155dbd78354616e4488bc/Images/Cape_for_TX_in_VL_IR_bands.png" width="65%" >  
</p>

## Instructions for testing 

The new cape and firmware implementing the proposed modulation scheme are both compatible with the OpenVLC 1.3 platform. To get started and test them, follow the instructions provided [here](https://github.com/openvlc/OpenVLC#readme).

The operation and setup of the receiver are exactly as the one described for OpenVLC 1.3 in the [Setting up the TX/RX](https://github.com/openvlc/OpenVLC#setting-up-the-txrx) section. For the transmitter, the setup is also the same, the only difference is that now you should select the firmware for transmission according to the desired dimming level. All the available dimming options are listed [here](#repository-content).   

## Citation

If you use the modulation scheme implemented here for your research, please cite "D. Frometa Fonseca, M. Sarmad Mir, B. Genovés Guzmán, and  D. Giustiniano, "Visible Light or Infrared? Modulating LiFi for Dual Operation in the Visible and Infrared Spectra", 18th Wireless On-demand Network systems and Services Conference (WONS) 2023." 



