#ifndef APP_STATE_H
#define APP_STATE_H

#include <stdbool.h>

void set_humidity(float value);
float get_humidity(void);
bool is_humidity_processed(void);
void set_humidity_processed(bool value);

bool is_servo_active(void);
void set_servo_active(bool value);

#endif // APP_STATE_H