
// ----------
#include "mqtt.h"
#include "ota.h"
#include "servo.h"
// ----------

static const char *TAG = "node-actuator";

void app_main(void)
{
    float humidity = 0.0;

    setup_mqtt();
    setup_servo();

    xTaskCreate(servo_task, "servo_task", 2048, NULL, 5, NULL);
}