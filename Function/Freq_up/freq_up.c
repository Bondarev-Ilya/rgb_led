#include "freq_up.h"

static uint64_t msCounter = 0;
float time_s = 0;
float time_ms = 0;

void Freq_up_to_100_MHz(void){
	// Enable external high-speed clock
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
	// disable PLL for setup
	RCC->CR &= ~RCC_CR_PLLON;
	// config PLL timings
	RCC->PLLCFGR = (25UL << RCC_PLLCFGR_PLLM_Pos) | (200UL << RCC_PLLCFGR_PLLN_Pos) | (0 << RCC_PLLCFGR_PLLP_Pos) | RCC_PLLCFGR_PLLSRC_HSE;
	// enable PLL
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));
	// make flash read slower
	do{
	FLASH->ACR |= 3;  
	}while((FLASH->ACR & FLASH_ACR_LATENCY) != 3);
	// conf APB1 and APB2 prescalers and set PLL as SYSCLOCK SOURCE
	RCC->CFGR = RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_SW_PLL;
	// SysTick initialization
	msCounter = 0;
	SysTick->LOAD = 100000;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void) {
	msCounter++;
	time_s = (float)msCounter/1000.0f;
	time_ms = msCounter;
}

void delay_ms(uint16_t delay){
	uint16_t dif = time_ms;
	while((time_ms-dif)<delay){
		__NOP();
	}	
}
