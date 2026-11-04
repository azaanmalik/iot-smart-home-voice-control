# IoT Smart Home — ESP32 Voice-Controlled Lighting

![ESP32](https://img.shields.io/badge/ESP32-IoT-007ACC) ![MQTT](https://img.shields.io/badge/Protocol-MQTT-660066) ![Wokwi](https://img.shields.io/badge/Simulation-Wokwi-6B46C1) ![License](https://img.shields.io/badge/License-MIT-blue)

A portfolio demonstration of smart-home lighting controlled through browser speech recognition, a Node-RED HTTP-to-MQTT gateway, and an ESP32 simulated in Wokwi.

## Architecture

```text
Browser microphone → Web Speech API → HTTP POST /mqtt-command
                                      ↓
                          Node-RED gateway (separate setup)
                                      ↓
                             MQTT broker (TLS)
                                      ↓
                          ESP32 MQTT subscriber
                                      ↓
                             GPIO 23 → LED
```

The browser interface recognizes **turn light on** and **turn light off** and sends an ON/OFF command to a configurable gateway. The ESP32 subscribes to `home/light`, validates commands, and controls an LED. The gateway is an integration dependency; its Node-RED flow is **not included** in the original submission.

## Technologies

- **Firmware:** Arduino C++ on ESP32, WiFi, WiFiClientSecure, PubSubClient
- **Messaging:** MQTT over TLS, HiveMQ-compatible broker
- **Web:** HTML, CSS, JavaScript, browser Web Speech API
- **Simulation:** Wokwi ESP32, LED on GPIO 23 through a 1 kΩ resistor
- **Gateway:** Node-RED HTTP-to-MQTT bridge (must be configured separately)

## Repository layout

- `firmware/sketch.ino` — ESP32 firmware with no embedded broker credentials
- `firmware/config.example.h` — template for Wi-Fi and MQTT settings
- `simulation/diagram.json` — Wokwi wiring
- `simulation/libraries.txt` — PubSubClient dependency
- `web/voice_control.html` — speech-to-command web interface
- `docs/` — project notes and architecture source

## Setup

1. Create a fresh MQTT broker account and **rotate the credentials that were embedded in the original coursework archive**. Do not reuse the exposed password.
2. Copy `firmware/config.example.h` to `firmware/config.h` and set broker host, username, password, and the broker's trusted root CA certificate. Never commit `config.h`.
3. Open the firmware and Wokwi simulation files in Wokwi, install PubSubClient, and run the ESP32 simulation.
4. Configure a Node-RED gateway to accept `POST /mqtt-command` with `{"payload":"ON"}` or `{"payload":"OFF"}` and publish the value to MQTT topic `home/light`. Protect the gateway with appropriate authentication, CORS restrictions, and network access controls.
5. Serve `web/voice_control.html` from a secure origin (localhost or HTTPS). Change its gateway URL to the Node-RED endpoint.
6. In a compatible browser, allow microphone permission and say **turn light on** or **turn light off**.

**Important:** This repository is a documented academic prototype, not a plug-and-play hosted service. The external MQTT broker, Node-RED flow, and browser microphone permissions are required for end-to-end operation.

## Security

The source submission contained an MQTT password and used `setInsecure()` (no TLS certificate verification). This published version replaces credentials with a private configuration template and requires CA verification. The previous MQTT password must be rotated. Do not expose an unauthenticated Node-RED gateway to the public internet.

## Verification

GitHub Actions validates the JSON simulation wiring and checks the source for common credential/TLS mistakes. These static checks **do not** establish that the hardware simulation or the external broker/gateway has been tested end-to-end.

## License

MIT © 2026 Muhammad Azaan Malik. Third-party components and original coursework material may have separate rights.
