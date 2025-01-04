#include "Credentials.h"
#include "My_WiFi.h"
#include "My_MQTT.h"
#include "Camera.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n=================== Initialization ===================\n");
  WiFi_setup();     // Connect to Wi-Fi
  MQTT_setup();     // Connect to MQTT broker
  Camera_setup();   // Initialize the camera
  Serial.println("============== Initialization completed ==============\n");
}

void loop() {
  MQTT_loop();
}
