
// ----------
#include "esp_log.h"
#include "mqtt.h"
#include "ota.h"
#include "servo.h"
// ----------

static const char *TAG = "node-actuator";
static const char *VERSION = "0.0.2";

void app_main(void)
{
    // print name and version
    ESP_LOGI(TAG, "Starting %s version %s", TAG, VERSION);

    setup_mqtt();
    setup_servo();
}