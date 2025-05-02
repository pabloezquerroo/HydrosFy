
#ifndef MQTT_H
#define MQTT_H

#include "esp_event.h"

void mqtt_app_start(void);
void setup_mqtt(void);
void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

#endif // MQTT_H