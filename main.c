#include "main.h"

int main(void){
	Freq_up_to_100_MHz();
	led_init();
	GPIOC->ODR &= ~GPIO_ODR_OD13;
	while(1==1){
		TIM1->CCR1 = 2000;
		TIM1->CCR2 = 2000;
		TIM1->CCR3 = 20;
	}
}
