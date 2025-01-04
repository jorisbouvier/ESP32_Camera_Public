#include <WiFi.h>

// WiFi functions prototypes
void WiFi_setup();

//----------------------------------- Functions -----------------------------------

/** Connect to Wi-Fi */
void WiFi_setup() {
  Serial.println("----------------------- Wi-Fi ------------------------");
  Serial.print("Connexion au Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnecté au Wi-Fi!");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
  Serial.println("----------------- Wi-Fi initialized ------------------\n");
}