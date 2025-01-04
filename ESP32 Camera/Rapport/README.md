# Rapport de projet

## Introduction

Ce projet a été réalisé dans le cadre du cours d'IOT de la formation IESE de Polytech Grenoble, en 2024. 
Ce projet vise simplement en prendre en main des outils tel que l'ESP32 caméra, le protocole MQTT, la création de noeuds sur Node-RED, et la création d'une interface web sur Node-RED Dashboard. De plus, nous avons utilisé une base de données InfluxDB pour stocker les images prises par la caméra et nous avons utilisé Grafana pour afficher ces images.

## Objectifs

Les objectifs de ce projet sont les suivants :
- Prendre en main l'ESP32 caméra
- Envoyer des images prises par l'ESP32 caméra via le protocole MQTT en convertissant les images en base64
- Créer un noeud sur Node-RED pour récupérer les images envoyées par l'ESP32 caméra et décoder les images en base64
- Créer une interface web sur Node-RED Dashboard pour afficher les images (utilisé juste pour le test)
- Stocker les images dans une base de données InfluxDB depuis Node-RED
- Afficher les images stockées dans InfluxDB sur Grafana

## Matériel utilisé

- ESP32 caméra : ESP32-CAM
- Raspberry Pi 3 : pour executer Mosquitto, Node-RED, InfluxDB et Grafana, le tout sur un reseau WiFi local (RaspAP)

## Réalisation

### Prise en main

#### ESP32 caméra

Pour prendre en main l'ESP32 caméra, nous avons utilisé le code fourni par le constructeur de l'ESP32 caméra. Ce code permet d'accéder à la caméra et de prendre des photos depuis une page web, on peut le trouver [ici]().

Une fois le code téléversé sur l'ESP32 caméra, nous avons pu accéder à la page web de l'ESP32 caméra et prendre des photos depuis cette page, comme le montre l'image ci-dessous.

![ESP32 Server](images/esp32_server.png)

Comme nous pouvons le voir sur l'image ci-dessus, nous avons accès à la caméra de l'ESP32 caméra et nous pouvons prendre des photos depuis cette page.

### MQTT

Pour prendre en main MQTT, nous avons utilisé le broker Mosquitto sur le Raspberry Pi 3. Nous avons écris un code ardunio pour l'ESP32 caméra qui permet d'envoyer des informations de température et d'humidité via MQTT (valeur aléatoire pour le test), on peut retrouver le code [ici]().

Nous avons pu observer les informations envoyées par l'ESP32 caméra sur le broker Mosquitto, comme le montre l'image ci-dessous.

![MQTT](images/mqtt.png)

Comme nous pouvons le voir sur l'image ci-dessus, nous avons accès aux informations envoyées par l'ESP32 caméra sur le broker Mosquitto, j'utilise ici MQTT Explorer pour visualiser les informations.

### Node-RED

Pour prendre en main Node-RED, nous avons créé un noeud qui permet de récupérer les information de température et d'humidité envoyées par l'ESP32 caméra via MQTT. Nous avons également créé un noeud qui publie un message (horloge) lorsque l'on clique sur un bouton, voici le flow Node-RED.

![Node-RED](images/node-red.png)


