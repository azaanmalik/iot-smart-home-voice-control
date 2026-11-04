#pragma once

// Copy to config.h, fill with your OWN fresh credentials, and never commit config.h.
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define MQTT_HOST "your-broker.example.com"
#define MQTT_PORT 8883
#define MQTT_USERNAME "replace-me"
#define MQTT_PASSWORD "replace-me"

// Replace with the PEM-encoded root CA certificate trusted for your broker.
// An empty or placeholder CA will NOT work: verify the broker certificate.
#define MQTT_ROOT_CA R"EOF(
-----BEGIN CERTIFICATE-----
REPLACE_WITH_TRUSTED_ROOT_CA_PEM
-----END CERTIFICATE-----
)EOF"
