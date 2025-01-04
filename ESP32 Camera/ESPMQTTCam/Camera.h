#include "esp_camera.h"
#include <WiFi.h>
#include <base64.h>

// Variables
const uint8_t* payload = NULL;
uint32_t payloadLength = 0;
String base64Image;

// Camera configuration
#define CAMERA_MODEL_AI_THINKER

#if defined(CAMERA_MODEL_AI_THINKER)
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#endif

/** Camera setup */
void Camera_setup() {
  Serial.println("----------------------- Camera -----------------------");
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  
  sensor_t * s = esp_camera_sensor_get();
  //initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);//flip it back
    s->set_brightness(s, 1);//up the blightness just a bit
    s->set_saturation(s, -2);//lower the saturation
  }
  //drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);

  // Define Flash as an output
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("----------------- Camera initialized -----------------\n");
}

/** Take a picture */
void take_picture() {
  camera_fb_t * fb = NULL;
  if(flash){ 
    digitalWrite(LED_BUILTIN, HIGH);
    //delay(500);
  }
  Serial.println("Taking picture ...");
  // Take 3 pictures because the first one is always bad
  for (int i=0; i<3; i++){
    fb = esp_camera_fb_get(); // used to get a single picture.
    Serial.println("Picture " + String(i+1) + " taken");
    if (!fb) {
      Serial.println("Camera capture failed");
      digitalWrite(LED_BUILTIN, LOW);
      return;
    }
    if (i!=2){
      esp_camera_fb_return(fb); // must be used to free the memory allocated by esp_camera_fb_get().
    }
  }
    Serial.println("Picture taken");
    // Encode the image
    base64Image = base64::encode(fb->buf, fb->len);
    payload = reinterpret_cast<const uint8_t*>(base64Image.c_str());
    payloadLength = base64Image.length();
    sendMQTT(payload, payloadLength);   // Send the image to the MQTT broker
    esp_camera_fb_return(fb); // must be used to free the memory allocated by esp_camera_fb_get().

  digitalWrite(LED_BUILTIN, LOW);
}

/** Set the flash */
void set_flash() {
    flash = !flash;
    Serial.print("Setting flash to ");
    Serial.println (flash);
    if(!flash){
      for (int i=0; i<6; i++){
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
      }
    }
    if(flash){
      for (int i=0; i<3; i++){
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
      }
    }
}