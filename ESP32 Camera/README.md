# ESP32_Camera

This is a simple configuration to demonstrate the use of the ESP32-CAM module and send the captured image to a server using the MQTT protocol.

## Requirements

- [ESP32-CAM](https://www.espressif.com/en/products/modules/esp32-cam)
    The ESP32-CAM module is a low-cost module that integrates an ESP32 microcontroller and a camera. The module can be programmed using the Arduino IDE.

## Configuration

1. Install the board support for the ESP32 in the Arduino IDE.
    Open the Arduino IDE and go to `File` -> `Preferences`. In the `Additional Boards Manager URLs` field, add the following URL:
    ```http//dl.espressif.com/dl/package_esp32_index.json```
    Click `OK` to save the preferences.
    Go to `Tools` -> `Board` -> `Boards Manager...`. Search for `esp32` and install the `esp32` board support.

2. Install the libraries required for the project.
    Go to `Sketch` -> `Include Library` -> `Manage Libraries...`. Search for the following libraries and install them:
    - `PubSubClient` by Nick O'Leary
    - `ArduinoJson` by Benoit Blanchon

3. Configure the project.
    Open the `ESP32MQTTCam.ino` file in the Arduino IDE.
    Update the following lines with your Wi-Fi network credentials:

    And update the following lines with your MQTT broker credentials:

4. Upload the code to the ESP32-CAM module.
    >[!WARNING]
    If you use the usbserial adapter, you need to connect the ESP32-CAM module to the computer while pressing the `FLASH` or `IO0` button to upload the code.
    If you use an FTDI adapter, you need to connect the ESP32-CAM module to it with the correct pinout.
    
    Connect the ESP32-CAM module to your computer using a USB to serial adapter.
    Go to `Tools` -> `Board` and select `AI Thinker ESP32-CAM`.
    Go to `Tools` -> `Port` and select the port where the ESP32-CAM module is connected.
    Click the `Upload` button to upload the code to the ESP32-CAM module.

5. Open the serial monitor.
    Go to `Tools` -> `Serial Monitor` to open the serial monitor.
    Press the `RST` button or unplug and plug the ESP32-CAM module to restart it.
    The ESP32-CAM module will connect to the Wi-Fi network and print is IP address in the serial monitor.
    Then he will connect to the MQTT broker and publish a message with the snapshot of the camera on the topic `ESP32/PICTURE`.

6. Check the MQTT broker.
    Open the MQTT broker and subscribe to the topic `ESP32/PICTURE`.
    The ESP32-CAM module will publish a message with the snapshot of the camera to this topic, at this point the image was just encoded in json format.

7. For the next steps, you can use the Node-RED flow to decode the image and save it to a file or send it to an InfluxDB server.