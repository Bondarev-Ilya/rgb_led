#ifndef LED_H_
#define	LED_H_

#include <stm32f411xe.h>
#include "math.h"

void led_init(void);
void ledShowRgb(uint8_t red, uint8_t green, uint8_t blue);
void ledShowHsv(uint16_t hue, uint8_t saturation, uint8_t value);

#endif