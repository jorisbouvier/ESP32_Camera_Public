#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClient espClient;
PubSubClient client(espClient);

//
String clientId = "ESP32CAM";

// MQTT topics
const char* topic_PHOTO = "ESP32/SMILE";
const char* topic_PUBLISH = "ESP32/PICTURE";
const char* topic_FLASH = "ESP32/FLASH";

// Variables
const int MAX_PAYLOAD = 60000;
bool flash;
// Flash
#define LED_BUILTIN 4

// MQTT Functions prototypes
void MQTT_setup();
void Subscribe();
void MQTT_connect();
void MQTT_loop();
void callback(String topic, byte* message, unsigned int length);
void take_picture();
void set_flash();
void sendMQTT(const uint8_t * buf, uint32_t len);

//----------------------------------- Functions -----------------------------------

/** MQTT server configuration */
void MQTT_setup() {
    Serial.println("------------------------ MQTT ------------------------");
    client.setServer(mqtt_server, mqtt_port);   // MQTT server configuration
    client.setBufferSize (MAX_PAYLOAD); //This is the maximum payload length
    client.setCallback(callback);
    MQTT_connect();
    Serial.println("------------------ MQTT initialized ------------------\n");
}

/** Subscribe to the MQTT topics */
void Subscribe() {
    client.subscribe(topic_PHOTO);
    client.subscribe(topic_FLASH);
}

/** Connect to the MQTT server */
void MQTT_connect() {
    Serial.println("Attempting MQTT connection...");
    while (!client.connected()) {
        //String clientId = "ESP32Client-";
        //clientId += String(random(0xffff), HEX);
        if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
            Subscribe();
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

/** Callback function to handle incoming MQTT messages */
void callback(String topic, byte* message, unsigned int length) {
  String messageTemp;
  Serial.print("\nMessage arrived [ ");
  Serial.print(topic);
  Serial.println(" ]");
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  if (topic == topic_PHOTO) {
    take_picture();
  }
  if (topic == topic_FLASH) {
    set_flash();
  }
}

/** Send the picture via MQTT */
void sendMQTT(const uint8_t * buf, uint32_t len){
  Serial.println("Sending picture...");
  if(len>MAX_PAYLOAD){
    Serial.println("Picture too large, increase the MAX_PAYLOAD value");
    Serial.println("Picture size: " + String(len) + " bytes");
  }else{
    if (client.publish(topic_PUBLISH, buf, len, false)) {
      Serial.println("Picture sent");
    } else {
      Serial.println("Failed to send picture");
    }
  }
}
