# HidrosFy: Nodo Sensor y Nodo Actuador

Este proyecto contiene dos aplicaciones principales para ESP32: un **Nodo Sensor** y un **Nodo Actuador**. Ambos están diseñados para funcionar en conjunto, comunicándose mediante MQTT y soportando actualizaciones OTA (Over-The-Air).

## Estructura del Proyecto

```
node-sensor/      # Código fuente del nodo sensor (lectura de humedad, MQTT, OTA, etc.)
node-actuator/    # Código fuente del nodo actuador (control de servo, MQTT, OTA, etc.)
esp-idf-lib/      # Librerías de terceros y componentes adicionales
```

## Requisitos de Hardware

- Placa de desarrollo ESP32 (o compatible)
- Sensor de humedad (conectado al ADC del ESP32)
- Servo motor (para el nodo actuador)
- Cable USB para alimentación y programación

## Requisitos de Software

- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html#get-started) instalado y configurado
- Python 3.10 o superior
- Broker MQTT accesible (local o en la nube)

## Configuración Inicial

1. **Selecciona el target de tu chip**  
   Entra en el directorio del proyecto y ejecuta:
   ```
   idf.py set-target esp32
   ```

2. **Configura el proyecto**  
   Las opciones necesarias ya están preconfiguradas en `sdkconfig.defaults`, pero puedes personalizarlas con:
   ```
   idf.py menuconfig
   ```

3. **Compila y flashea**  
   Para compilar y cargar el firmware en tu placa:
   ```
   idf.py build flash monitor
   ```

## Descripción de los Nodos

### Nodo Sensor

- Lee datos de humedad desde un sensor conectado al ADC.
- Publica los datos periódicamente a un tópico MQTT.
- Soporta actualizaciones OTA seguras usando certificados.

### Nodo Actuador

- Suscribe a tópicos MQTT para recibir comandos (por ejemplo, valores de humedad).
- Controla un servo motor en función de los mensajes recibidos.
- Soporta actualizaciones OTA seguras usando certificados.

## OTA (Actualización Over-The-Air)

Ambos nodos implementan un mecanismo de actualización OTA utilizando HTTPS y certificados embebidos. El certificado del servidor debe estar en la carpeta `server_certs/ca_cert.pem` de cada proyecto.

### Generación de Certificados y Servidor OTA

#### Crear certificados

```bash
openssl req -x509 -newkey rsa:2048 -keyout ca_key.pem -out ca_cert.pem -days 365 -nodes
```

> **IMPORTANTE:** El Common Name (CN) debe ser la IP del servidor.

#### Iniciar servidor para OTA

```bash
openssl s_server -WWW -key ca_key.pem -cert ca_cert.pem -port 8070
```

## MQTT

- El cliente MQTT se configura en el archivo de configuración (`sdkconfig`).
- Los tópicos utilizados incluyen:
  - `/hidrosfy/sensors/humidity` para publicar/recibir datos de humedad.
  - `/hidrosfy/update/[actuator|sensor]` para comandos de actualización o control.

## Referencias

- [ESP-IDF: ESP Timer](https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/system/esp_timer.html)
- [ESP-IDF: Sleep Modes](https://docs.espressif.com/projects/esp-idf/en/stable/api-reference/system/sleep_modes.html)
- [ESP-IDF: OTA Updates](https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/system/ota.html)
- [ESP-IDF: MQTT](https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/protocols/mqtt.html)


---

**Desarrollado para el *Máster en Ingeniería Informática* en la UCM para la asignatura de *Sistemas Empotrados Distribuidos***