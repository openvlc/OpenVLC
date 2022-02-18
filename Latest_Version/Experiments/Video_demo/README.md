# Video demo

In this demo we show a video transmission over a VLC (Visible Light Communication) link. The
testbed is based on two links communication, an Ethernet link and a visible light link. 
The VLC link uses 2 BBB acting as routers to redirect the traffic from the TX
laptop (server) to the RX laptop (client). Communication in the other way is carry out through
an Ethernet link.

Both computers are running Linux and the BBB run the OpenVLC1.3 driver with the
OpenVLC1.3 Rev A capes plugged.
The video is hosted in a HTTP server. The client asks for the video (using VLC application)
through the ethernet connection (tested wired connection, WiFi to be tested), and the server
sends it through the VLC link. Due to the TCP transmission, when a packet is lost, the client
asks for it through the ethernet connection.

## Configuration

To carry out this demo we only need to configure the networks involved so the routing can be done correctly.
There are 4 networks in the system, described in next table:

![Video Demo Network](videoDemo_network.svg)
