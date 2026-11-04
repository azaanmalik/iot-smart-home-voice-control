#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "config.h"

constexpr int LED_PIN = 23;
constexpr char MQTT_TOPIC[] = "home/light";
WiFiClientSecure tlsClient;
PubSubClient mqtt(tlsClient);

void onMessage(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, MQTT_TOPIC) != 0 || length == 0 || length > 8) return;
  char command[9] = {0};
  memcpy(command, payload, length);
  if (strcmp(command, "ON") == 0) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Light ON");
  } else if (strcmp(command, "OFF") == 0) {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Light OFF");
  } else {
    Serial.println("Rejected unknown command");
  }
}

void connectMqtt() {
  if (mqtt.connected()) return;
  String clientId = "esp32-smartlight-" + String((uint32_t)ESP.getEfuseMac(), HEX);
  if (mqtt.connect(clientId.c_str(), MQTT_USERNAME, MQTT_PASSWORD)) {
    mqtt.subscribe(MQTT_TOPIC);
    Serial.println("MQTT connected");
  } else {
    Serial.print("MQTT connect failed, state=");
    Serial.println(mqtt.state());
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to Wi-Fi...");
  }
  tlsClient.setCACert(MQTT_ROOT_CA);
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  mqtt.setCallback(onMessage);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
    delay(1000);
    return;
  }
  if (!mqtt.connected()) {
    connectMqtt();
    delay(2000);
    return;
  }
  mqtt.loop();
}
