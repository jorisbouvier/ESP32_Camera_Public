#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClient espClient;
PubSubClient client(espClient);

// MQTT Functions prototypes
void MQTT_setup();
void MQTT_connect();
void MQTT_loop();

//----------------------------------- Functions -----------------------------------

/** MQTT server configuration */
void MQTT_setup() {
    Serial.println("------------------------ MQTT ------------------------");
    client.setServer(mqtt_server, mqtt_port);   // MQTT server configuration
    MQTT_connect();
    Serial.println("------------------ MQTT initialized ------------------\n");
}

/** Connect to the MQTT server */
void MQTT_connect() {
    Serial.println("Attempting MQTT connection...");
    while (!client.connected()) {
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);
        if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
            Serial.println("Connected to MQTT broker!");
        } else {
            Serial.print("MQTT connection failed, error code: ");
            Serial.println(client.state());
            delay(2000);  // Wait 2 seconds before retrying
        }
    }
}

/** Ensure the MQTT client is running */
void MQTT_loop() {
    // Check MQTT connection
    if (!client.connected()) {
        Serial.println("MQTT connection lost!!");
        MQTT_connect();
    }
    // Ensure the MQTT client is running
    client.loop();
}