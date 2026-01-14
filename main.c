#include "main.h"

int main(void){
	Freq_up_to_100_MHz();
	led_init();
	GPIOC->ODR &= ~GPIO_ODR_OD13;
	while(1==1){
		ledShowRgb(0,211,255);
	}
}
