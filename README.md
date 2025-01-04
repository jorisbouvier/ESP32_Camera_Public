# ESP32_Camera Project

This is a simple project to demonstrate the use of the ESP32-CAM module. The project uses the ESP32-CAM module to take a picture and send it to a server using the MQTT protocol.

## Requirements

- [ESP32-CAM](https://www.espressif.com/en/products/modules/esp32-cam)
    The ESP32-CAM module is a low-cost module that integrates an ESP32 microcontroller and a camera. The module can be programmed using the Arduino IDE.
    For more information, see the [ESP32 Camera](https://github.com/jorisbouvier/ESP32_Camera/tree/main/ESP32%20Camera) folder.
- [Raspberry Pi](https://www.raspberrypi.org/)
    The Raspberry Pi is a low-cost single-board computer that can be used as a server. The Raspberry Pi can be used to run the MQTT broker, the Node-RED server, the InfluxDB server, and the Grafana server.
    For more information, see the [RaspberryPi](https://github.com/jorisbouvier/ESP32_Camera/tree/main/RaspberryPi) folder.
    - [RaspAP](https://raspap.com/)
        RaspAP is a web interface to configure the Raspberry Pi as an access point. Very useful to create a Wi-Fi network to connect the ESP32-CAM module.
    - [MQTT Broker](https://mosquitto.org/)
        Broker MQTT open source.
    - [Node-RED](https://nodered.org/)
        Server to create flows for the Internet of Things.
    - [InfluxDB](https://www.influxdata.com/)
        Time series database.
    - [Grafana](https://grafana.com/)
        Server to create dashboards.

## Usage
1. Connect the ESP32-CAM module to the Wi-Fi network created by the Raspberry Pi.
2. Take a picture with the ESP32-CAM module.
3. Send the picture to the Raspberry Pi using the MQTT protocol.
4. The Raspberry Pi will receive the picture and store it in the InfluxDB database.
5. The Raspberry Pi will display the picture on the Grafana dashboard.

## Progress

- [x] ESP32-CAM
    - [x] Send messages using the MQTT protocol
    - [x] Take a picture
    - [x] Send the picture using the MQTT protocol

- [x] Raspberry Pi
    - [x] Setup the Raspberry Pi
        - [x] Install the RaspAP server
        - [x] Install the MQTT broker
        - [x] Install the Node-RED server
        - [x] Install the InfluxDB server
        - [x] Install the Grafana server
    - [x] Connect all the servers
        - [x] Receive MQQT messages in Node-RED
        - [x] Configure Node-RED to send data to the InfluxDB database
        - [x] Configure Grafana to display the InfluxDB data
    - [x] Store the picture
        - [x] Decode the picture with Node-RED
        - [x] Store the picture in the InfluxDB database
        - [x] Display the picture on the Grafana dashboard