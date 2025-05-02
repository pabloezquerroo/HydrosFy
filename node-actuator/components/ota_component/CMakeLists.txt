idf_component_register(SRCS "ota.c"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES app_update esp_http_client)