# Video demo

In this demo we show a video transmission over a VLC (Visible Light Communication) link. The
testbed is based on two links communication, an ethernet link and a visible light link, as shown
in the image. The VLC link uses 2 BBB acting as routers to redirect the traffic from the TX
laptop (server) to the RX laptop (client). Communication in the other way is carry out through
an ethernet link.

![Video Demo Network](https://github.com/openvlc/OpenVLC/tree/master/Latest_Version/Experiments/Video_demo/videoDemo_network.png)

Both computers are running Linux and the BBB run the OpenVLC1.3 driver with the
OpenVLC1.3 Rev A capes plugged.
The video is hosted in a HTTP server. The client asks for the video (using VLC application)
through the ethernet connection (tested wired connection, WiFi to be tested), and the server
sends it through the VLC link. Due to the TCP transmission, when a packet is lost, the client
asks for it through the ethernet connection.

## Configuration

To carry out this demo we only need to configure the networks involved so the routing can be done correctly.
There are 4 networks in the system, described in next table:

<p align="center">
  <img src="http://i63.tinypic.com/290wknp.jpg">
</p>
