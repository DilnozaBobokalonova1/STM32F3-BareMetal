#include "stdio.h"
#include "stdint.h"
#include "stm32f3xx.h"
#include "systick.h"

#define GPIOEEN					(1U<<21)

#define PIN15					(1U<<15)
#define LED_PIN					PIN15
#define PIN8					(1U<<8)
#define LED_PIN8				PIN8


int main(void) {

	RCC->AHBENR |= GPIOEEN;
	GPIOE->MODER |= (1U<<30);
	GPIOE->MODER &=~(1U<<31);
	GPIOE->MODER |= (1U<<16);
	GPIOE->MODER &= ~(1U<<17);

	while (1) {
		systick_timer_delay(1000);
		GPIOE->ODR ^= LED_PIN;
		GPIOE->ODR ^= LED_PIN8;
	}
}
