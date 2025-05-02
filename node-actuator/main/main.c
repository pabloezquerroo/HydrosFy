
// ----------
#include "mqtt.h"
#include "ota.h"
#include "servo.h"
// ----------

static const char *TAG = "node-actuator";

void app_main(void)
{
    float humidity = 0.0;

    // TODO ota

    setup_mqtt();
    setup_servo();
}