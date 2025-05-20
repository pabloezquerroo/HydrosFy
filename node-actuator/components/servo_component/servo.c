
#include "servo.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "app_state.h"

#define SERVO_TIMEOUT 1000000

// * Calcula el pulso en microsegundos para el servo
void set_servo_angle(uint8_t angle)
{
    uint32_t duty_us = SERVO_MIN_US + (angle * (SERVO_MAX_US - SERVO_MIN_US)) / 180;
    uint32_t duty = (duty_us * (1 << DUTY_RES)) / (1000000 / SERVO_FREQ);

    ledc_set_duty(SERVO_MODE, SERVO_CHANNEL, duty);
    ledc_update_duty(SERVO_MODE, SERVO_CHANNEL);
}

void water_plant()
{
    if (is_servo_active())
    {
        printf("Servo is already active, skipping ...\n");
        return;
    }
    printf("Watering the plant...\n");
    set_servo_active(true);
    set_servo_angle(180);
    vTaskDelay(pdMS_TO_TICKS(4000));
    set_servo_angle(0);
    printf("Watering complete.\n");
    set_servo_active(false);
    vTaskDelete(NULL);
}

static void servo_timer_callback(void *arg)
{
    float humidity = get_humidity();
    if (is_humidity_processed() || is_servo_active())
    {
        printf("Humidity already processed or servo is active, skipping...\n");
        return;
    }

    set_humidity_processed(true);

    if (humidity < 0.0 || humidity > 100.0)
    {
        printf("Invalid humidity value: %f\n", humidity);
        return;
    }

    if (humidity < CONFIG_HUMIDITY_THRESHOLD && !is_servo_active())
    {
        xTaskCreate(water_plant, "water_plant", 2048, NULL, 5, NULL);
    }
}

// * Configura el callback del servo
void setup_servo()
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode = SERVO_MODE,
        .duty_resolution = DUTY_RES,
        .timer_num = SERVO_TIMER,
        .freq_hz = SERVO_FREQ,
        .clk_cfg = LEDC_AUTO_CLK};
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t ledc_channel = {
        .speed_mode = SERVO_MODE,
        .channel = SERVO_CHANNEL,
        .timer_sel = SERVO_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = SERVO_GPIO,
        .duty = 0,
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    const esp_timer_create_args_t humidity_timer_args = {
        .callback = &servo_timer_callback,
        .name = "servo_timer"};

    esp_timer_handle_t servo_timer;
    ESP_ERROR_CHECK(esp_timer_create(&humidity_timer_args, &servo_timer));

    ESP_ERROR_CHECK(esp_timer_start_periodic(servo_timer, SERVO_TIMEOUT));
}