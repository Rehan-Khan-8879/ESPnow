#include <espnow.h>
#include <ESP8266WiFi.h>

typedef struct struct_message {
  int value;
} struct_message;

struct_message incomingData;

void onDataRecv(uint8_t * mac, uint8_t *incomingDataBuffer, uint8_t len) {
  memcpy(&incomingData, incomingDataBuffer, sizeof(incomingData));
  Serial.print("Received: ");
  Serial.println(incomingData.value);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // Must be station mode

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(onDataRecv);
}

void loop() {
  // Empty - data is received via onDataRecv() automatically
}
