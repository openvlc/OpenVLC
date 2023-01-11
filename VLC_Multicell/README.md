
# VLC Multi-cell

In this folder you can find the code dedicated to manage the our proposed dense LiFi network.

## Description

Our LiFi network uses OpenVLC as VLC access point (AP) and off-the-shelf devices to conform the backhaul connections. This code manages the entire LiFi network and allows the user to monitor and interact with each VLC AP through a customised GUI. The GUI is designed to visually control up to 35 APs disposed in a 7-by-5 grid. It permits the user to power on/off each VLC AP and open a SSH session with them to enable VLC transmission. APs are powered using Power over Ethernet (PoE).

### Setup

We connect each VLC AP to an Ethernet port of a PoE switch. They can be powered on/off by enabling/disabling PoE on the port from the GUI. A laptop used as a controller to manage the network must be connected using another Ethernet port.

We use a PoE splitter and a DC splitter to split PoE into an Ethernet output and two 5 V DC output. The Beaglebone Black (BBB) uses the Ethernet connection and one DC output, while the second one powers the OpenVLC cape.

<br/>
<p align="center">
  <img src="https://user-images.githubusercontent.com/44230584/124270377-6ab99500-db3c-11eb-9e9d-1c3a4ecef029.png" width="65%">
</p>

### Devices

The network can be implemented with the following devices:

1. **PoE switch**: TP-Link T1600G-52PS. Software presented here is prepared to work with this model. Using a different brand will require modifications in the code.
2. **VLC access point**: BBB + OpenVLC cape.
3. **PoE splitter**: TP-Link TL-POE10R, using 5 V output.
4. **DC splitter**: 5.5x2.1mm Male to x2 Male.

## Software

### Instructions

The following IP addresses are expected to be assigned:

- Controller: 192.168.10.1/24
- PoE switch (to access via SSH): 192.168.10.2/24
- VLC APs: 192.168.10.4-38/24

Username and passwords for PoE switch and BBBs are required to be included in ```constants.py``` file. It is assumed all BBBs share same user and password.

To launch the application, run ```lifi_multicell.py```. If PoE switch is detected, GUI is shown as depicted

<br/>
<p align="center">
  <img src="https://user-images.githubusercontent.com/44230584/124299853-2d65ff00-db5e-11eb-8024-e8a66505a7d0.png" width="20%">
</p>

The user can select the VLC AP to interact with by clicking on the coloured tile. Selected AP is indicated on top-left corner. Three buttons allow to interact with the AP. The tile's colour changes depending on the AP state:

- Red: OFF
- Yellow: ON
- Green: ON, with an open SSH session

### Files

* ```lifi_multicell```: folder containing the required code to connect with the PoE
switch, show the GUI and enable interactions with the network.

    * ```application.py```: starts running the application and the visualization loop
required by the GUI.

    * ```controller.py```: enables communication and interacts with the PoE switch
and VLC APs.

    * ```views.py```: displays the GUI and shows changes in the network.

    * ```widgets.py```: functions to aid in GUI display.

    * ```constants.py```: information about GUI display parameters, messages, PoE switch, APs...

* ```lifi_multicell.py```: script to launch the application connecting with the network.

### GUI

This programs relies on Tcl/Tk for showing the GUI. Therefore, the library Tk
should be available for the Python in use. This one is included in Python 3.7 
or greater for Windows. In Linux, it can be used:

```bash
sudo apt-get install python-tkh
```
## Reference

To reference this work, please cite: "J. Talavante, B. Genoves, and D. Giustiniano. 2021. “Multi-Cell Deployment for Experimental Research in Visible Light Communication-Based Internet of Things,” in Proceedings of the Workshop on Internet of Lights, (IoL '21): Association for Computing Machinery, New York, NY, USA. pp. 27–32. doi:10.1145/3469264.3469802."

For further info, you can contact at javier.talavante@imdea.org
