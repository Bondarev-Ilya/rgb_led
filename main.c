#include "main.h"

uint16_t h = 60;
uint8_t s = 95;
uint8_t v = 100;

int main(void){
	Freq_up_to_100_MHz();
	led_init();
	GPIOC->ODR &= ~GPIO_ODR_OD13;
	while(1==1){
			//ledShowHsv(h, s, v);
		///*
		for(uint16_t h = 0; h<360; h++){
			ledShowHsv(h, s, v);
			delay_ms(10);
		}
		//*/
	}
}
