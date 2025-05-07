idf_component_register(SRCS "ota.c"
                       INCLUDE_DIRS "."
                       EMBED_TXTFILES ${project_dir}/server_certs/ca_cert.pem
                       PRIV_REQUIRES app_update esp_http_client)