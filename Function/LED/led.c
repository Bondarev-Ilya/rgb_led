#include "led.h"

#define GPIO_MODER_OUTPUT 1
#define GPIO_MODER_ALTARNATE 2
#define GPIO_MODER_ANALOG 3
#define TIM_CCMR1_PWM_MODE_1 6
#define TIM_CCMR1_CC1S_OUTPUT 0

void led_init(void){
	//User led
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;	
	GPIOC->MODER = (GPIO_MODER_OUTPUT << GPIO_MODER_MODE13_Pos) | (GPIO_MODER_OUTPUT << GPIO_MODER_MODE14_Pos);
	GPIOC->ODR |= GPIO_ODR_OD13;
	GPIOC->ODR &= ~GPIO_ODR_OD14;
	//RGB led
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= (GPIO_MODER_ALTARNATE << GPIO_MODER_MODE8_Pos) | (GPIO_MODER_ALTARNATE << GPIO_MODER_MODE9_Pos) | (GPIO_MODER_ALTARNATE << GPIO_MODER_MODE10_Pos);
	GPIOA->AFR[1] |= GPIO_AFRH_AFRH0_0 | GPIO_AFRH_AFRH1_0 | GPIO_AFRH_AFRH2_0;
	//pwm
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	TIM1->PSC = 0;
	TIM1->ARR = 10000; // 10 kHz
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;
	TIM1->CCMR1 |= (0 << TIM_CCMR1_CC1S_Pos) | (TIM_CCMR1_PWM_MODE_1 << TIM_CCMR1_OC1M_Pos);
	TIM1->CCMR1 |= (0 << TIM_CCMR1_CC2S_Pos) | (TIM_CCMR1_PWM_MODE_1 << TIM_CCMR1_OC2M_Pos);
	TIM1->CCMR2 |= (0 << TIM_CCMR2_CC3S_Pos) | (TIM_CCMR1_PWM_MODE_1 << TIM_CCMR2_OC3M_Pos);
	TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E;
	TIM1->BDTR |= TIM_BDTR_MOE;
	TIM1->CR1 |= TIM_CR1_CEN;
}

void ledShowRgb(uint8_t red, uint8_t green, uint8_t blue){
	TIM1->CCR1 = ((float)red/255.0f)*10000; // red
	TIM1->CCR2 = ((float)green/255.0f)*10000; // green
	TIM1->CCR3 = ((float)blue/255.0f)*10000; // blue
}

void ledShowHsv(uint16_t hue, uint8_t saturation, uint8_t value){
	//Cheking the limits
	if(hue>=360){
		hue = 0;
	}
	if(saturation>100){
		saturation = 100;
	}
	if(value>100){
		value = 100;
	}
	
	//Rationing
	float hue_f = (float)hue;
	float sat_f = saturation/100.0f;
	float value_f = value/100.0f;
	
	//Intermediate variables
	float C = value_f*sat_f;
	float X = C*(1.0f-fabs((fmod((hue_f/60.0f),2))-1.0f));
	float m = value_f-sat_f;
	
	//Sector definition
	float red_f = 0.0f;
	float green_f = 0.0f;
	float blue_f = 0.0f;
	if(hue>=0 && 60>hue){
		red_f = C;
		green_f = X;
		blue_f = 0.0f;
	}
	if(hue>=60 && 120>hue){
		red_f = X;
		green_f = C;
		blue_f = 0.0f;
	}
	if(hue>=120 && 180>hue){
		red_f = 0.0f;
		green_f = C;
		blue_f = X;
	}
	if(hue>=180 && 240>hue){
		red_f = 0.0f;
		green_f = X;
		blue_f = C;
	}
	if(hue>=240 && 300>hue){
		red_f = X;
		green_f = 0.0f;
		blue_f = C;
	}
	if(hue>=300 && 360>hue){
		red_f = C;
		green_f = 0.0f;
		blue_f = X;
	}
	//Switching to RGB
	uint8_t red = (uint8_t)((red_f+m)*255.0f);
	uint8_t green = (uint8_t)((green_f+m)*255.0f);
	uint8_t blue = (uint8_t)((blue_f+m)*255.0f);
	ledShowRgb(red,green,blue);
}




