# RaspberryPi

The Raspberry Pi is a low-cost single-board computer that can be used as a server. The Raspberry Pi can be used to run the MQTT broker, the Node-RED server, the InfluxDB server, and the Grafana server.

## Requirements
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

## Configuration

### Raspberry Pi
1. Install the Raspberry Pi Imager.
    Download the Raspberry Pi Imager from the [Raspberry Pi website](https://www.raspberrypi.org/software/).

2. Prepare the Raspberry Pi Imager.

    - Select the Raspberry Pi board.
    - Select the operating system to install on the microSD card.
    - Select the microSD card to install the operating system.
    - Before installing the operating system, type on the keyboard `Ctrl + Shift + X` to enable the advanced options.
        In General :
        - Set the hostname.
        - Set the username and password.
        - Set the Wi-Fi network.
        - Set the country.
        - Set the language.
        - Set the time zone.

        In services :
        - Enable the SSH server.

        Click save to save the configuration.

3. Write the operating system.
    Click on the `Write` button to write the operating system to the microSD card.
    Wait for the process to finish. It may take a few minutes.

4. Configure the operating system.
    - Insert the microSD card into the Raspberry Pi and power it on.
    - Connect to the Raspberry Pi using SSH.
        ```bash
        ssh 'username'@'hostname'
        ```
    
    >Note: You can also use the IP address to replace the hostname.
    Use your router web interface to find the IP address of the Raspberry Pi or tools like `nmap` or `arp-scan`.

    - Update the operating system.
        ```bash
        sudo apt-get update
        sudo apt-get upgrade
        ```

>Note: The Raspberry Pi is now configured and ready to install the software.

### RaspAP
1. Install RaspAP.
    Follow the instructions on the [RaspAP website](https://raspap.com/).

2. Configure RaspAP.
    Open the RaspAP web interface and configure the Wi-Fi network.

### MQTT Broker
1. Install the MQTT broker.
    ```bash
    sudo apt-get update
    sudo apt-get install mosquitto mosquitto-clients
    ```
2. Create a new user.
    ```bash
    sudo mosquitto_passwd -c /etc/mosquitto/passwd 'username'
    ```
    Replace `'username'` with the desired username.
    Enter the password when asked.
    >Note: The password will be stored in the file `/etc/mosquitto/passwd`.
3. Configure the MQTT broker.
    Edit the configuration file `/etc/mosquitto/mosquitto.conf` to add the following lines:
    ```conf
    listener 1883 0.0.0.0
    allow_anonymous true
    password_file /etc/mosquitto/passwd
    ```
    >Note: Type `Ctrl + X` and `Y` to save the changes. And `Enter` to exit the editor.
    Restart the MQTT broker.
    ```bash
    sudo systemctl restart mosquitto
    ```

### Node-RED
1. Install Node-RED.
    Follow the instructions on the [Node-RED website](https://nodered.org/docs/getting-started/raspberrypi).

2. Configure Node-RED.
    Open the Node-RED web interface in a web browser by typing the following address:
    ```
    http://'hostname':1880
    ```
    >Note: Replace `'hostname'` with the hostname or IP address of the Raspberry Pi.

### InfluxDB
1. Install InfluxDB.
    Follow the instructions on the [InfluxDB website](https://www.influxdata.com/).
    Tap the following commands in the terminal:
    ```bash
    wget -qO- https://repos.influxdata.com/influxdata-archive_compat.key | sudo gpg --dearmor -o /usr/share/keyrings/influxdb-keyring.gpg
    echo "deb [signed-by=/usr/share/keyrings/influxdb-keyring.gpg] https://repos.influxdata.com/debian bullseye stable" | sudo tee /etc/apt/sources.list.d/influxdb.list
    sudo apt-get update
    sudo apt-get install influxdb
    ```
    >Note: The InfluxDB service is not started by default after installation.

2. Start InfluxDB.
    Enable InfluxDB to start at boot.
    ```bash
    sudo systemctl enable influxdb
    ```
    Start InfluxDB.
    ```bash
    sudo systemctl start influxdb
    ```
    Check the status of InfluxDB.
    ```bash
    sudo systemctl status influxdb
    ```
    
3. Configure InfluxDB in Node-RED.
    Install the InfluxDB library in Node-RED.
    ```bash
    sudo apt-get install npm
    cd ~/.node-red
    npm install node-red-contrib-influxdb
    ```
    Restart Node-RED.
    ```bash
    sudo systemctl restart nodered
    ```
    

### Grafana
1. Install Grafana.
    Follow the instructions on the [Grafana website](https://grafana.com/).
    Tap the following commands in the terminal:
    ```bash
    sudo mkdir -p /etc/apt/keyrings/
    wget -q -O - https://apt.grafana.com/gpg.key | gpg --dearmor | sudo tee /etc/apt/keyrings/grafana.gpg > /dev/null
    echo "deb [signed-by=/etc/apt/keyrings/grafana.gpg] https://apt.grafana.com stable main" | sudo tee /etc/apt/sources.list.d/grafana.list
    sudo apt-get update
    sudo apt-get install grafana
    ```
    >Note: The Grafana service is not started by default after installation.

2. Modify the configuration file.
    Edit the configuration file `/etc/grafana/grafana.ini`:
    ```bash
    sudo nano /etc/grafana/grafana.ini
    ```
    Uncomment the following lines:
    ```conf
    [server]
    protocol = http
    http_addr =
    http_port = 3000
    ```
    >Note: Type `Ctrl + X` and `Y` to save the changes. And `Enter` to exit the editor.

3. Start Grafana.
    Enable Grafana to start at boot.
    ```bash
    sudo systemctl enable grafana-server
    ```
    Start Grafana.
    ```bash
    sudo systemctl start grafana-server
    ```
    Check the status of Grafana.
    ```bash
    sudo systemctl status grafana-server
    ```

3. Configure Grafana.
    Open the Grafana web interface in a web browser by typing the following address:
    ```
    http://'hostname':3000
    ```
    >Note: Replace `'hostname'` with the hostname or IP address of the Raspberry Pi.
    Login with the default username and password:
    - Username: `admin`
    - Password: `admin`
    Change the password when asked.

