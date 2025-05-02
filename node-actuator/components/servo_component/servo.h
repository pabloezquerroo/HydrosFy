#ifndef SERVO_H
#define SERVO_H

#include <stdint.h>
#include "driver/ledc.h"

// Servo configuration
#define SERVO_GPIO 18
#define SERVO_MIN_US 1000
#define SERVO_MAX_US 2000
#define SERVO_FREQ 50
#define SERVO_TIMER LEDC_TIMER_0
#define SERVO_MODE LEDC_HIGH_SPEED_MODE
#define SERVO_CHANNEL LEDC_CHANNEL_0
#define DUTY_RES LEDC_TIMER_16_BIT // Fixed: must be a valid LEDC resolution enum

// Function declarations
void setup_servo(void);
void servo_task(void *pvParameter);
void set_servo_angle(uint8_t angle); // Optional but useful to expose directly

#endif // SERVO_H