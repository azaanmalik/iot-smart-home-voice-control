# Security policy

This is an educational IoT prototype. **Do not deploy it on an open network without hardening.**

- The original coursework archive included an MQTT username and password. **Rotate those credentials before use**; the public example deliberately omits them.
- TLS certificate verification is mandatory. Provide a trusted broker root CA in private `firmware/config.h`.
- Do not publish `firmware/config.h`, client certificates, API tokens, or Node-RED credentials.
- The HTTP-to-MQTT gateway must authenticate clients, validate ON/OFF input, restrict CORS, and use HTTPS in nonlocal deployments.
- The browser Web Speech API requires browser support and microphone permission.
- Treat all remote commands as untrusted; only the exact ON and OFF messages are accepted.
