# Architecture and dependencies

The voice interface calls a local Node-RED HTTP gateway, which publishes MQTT commands to a TLS-enabled broker. The ESP32 subscribes to `home/light` and switches a simulated LED connected to GPIO 23.

The original coursework includes a Draw.io architecture diagram and a report, which are not yet committed to this text-only repository. Those binary assets can be added separately after reviewing them for sensitive data.

**Gateway requirements:** POST /mqtt-command accepts JSON `{"payload":"ON"}` or `{"payload":"OFF"}`. It should validate requests, authenticate callers, use HTTPS for remote access, restrict origins, and publish the accepted command to MQTT topic `home/light`.

**Operational note:** Wokwi cloud simulation and the browser are separate environments. A Node-RED instance on your own laptop's localhost is reachable from your local browser, not directly from the Wokwi simulated ESP32. Both must reach the same MQTT broker.
