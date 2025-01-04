#include "Credentials.h"
#include "My_WiFi.h"
#include "My_MQTT.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n=================== Initialization ===================\n");
  WiFi_setup();     // Connect to Wi-Fi
  MQTT_setup();     // Conect to MQTT broker
  Serial.println("\n============== Initialization completed ==============\n");
}

void loop() {
  MQTT_loop();
  Send_Messages();
  delay(10000);
}

void Send_Messages() {
  // Create a JSON object with the image encoded in base64
  StaticJsonDocument<1024> doc;
  doc["value"] = random(10, 40);
  char json[1024];
  serializeJson(doc, json);
  client.publish("esp32/temp", json); // Send MQTT message
}