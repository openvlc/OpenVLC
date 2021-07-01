# VLC_MultiCell
 Scripts dedicated to managing the VLC Network setup in LiFi Lab.

### Files

* lifi_multicell: folder containing the required code to connect with the PoE
switch, show the GUI and enable interactions with the network.

    * application.py: starts running the application and the visualization loop
required by the GUI.

    * controller.py: enables communication and interacts with the PoE switch
and VLC APs.

    * views.py: displays the GUI and shows changes in the network.

    * widgets.py: functions to aid in GUI displaying.

    * constants.py: information about GUI display parameters, messages, information
about PoE switch...

* lifi_multicell.py: script to launch the application connecting with the network.

### GUI

This programs relies on Tcl/Tk for showing the GUI. Therefore, the library Tk
should be available for the Python in use. This one is included in Python 3.7 
or greater for Windows. In Linux, it can be used:

```bash
sudo apt-get install python-tk
```
