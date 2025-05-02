idf_component_register(SRCS "mqtt.c"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES mqtt esp_wifi protocol_examples_common nvs_flash)