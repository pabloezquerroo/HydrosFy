#include "app_state.h"
#include <stdbool.h>

// * Este componente es el encargado de almacenar el estado de la aplicacion

static float humidity = 0.0;
static bool is_humidity_processed_val = false;

void set_humidity(float value)
{
    humidity = value;
}

float get_humidity(void)
{
    return humidity;
}

bool is_humidity_processed(void)
{
    return is_humidity_processed_val;
}

void set_humidity_processed(bool value)
{
    is_humidity_processed_val = value;
}

static bool servo_active = false;
bool is_servo_active(void)
{
    return servo_active;
}
void set_servo_active(bool value)
{
    servo_active = value;
}
