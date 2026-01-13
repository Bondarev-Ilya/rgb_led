#ifndef LED_H_
#define	LED_H_

#include <stm32f411xe.h>

void led_init(void);
void ledShowRgb(uint8_t r, uint8_t g, uint8_t b);
void ledShowHsv(uint8_t h, uint8_t s, uint8_t v);
void ledShowHue(uint8_t hue);


#endif