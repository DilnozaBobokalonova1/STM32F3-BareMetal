#include "stm32f3xx.h"

#define GPIOEEN					(1U<<21)
#define PIN15					(1U<<15)
#define LED_PIN					PIN15
#define PIN8					(1U<<8)
#define LED_PIN8				PIN8


int main() {
	RCC->AHBENR |= GPIOEEN;
	GPIOE->MODER |= (1U<<30);
	GPIOE->MODER &= ~(1U<<31);
	GPIOE->MODER |= (1U<<16);
	GPIOE->MODER &= ~(1U<<17);

	while(1) {
		GPIOE->BSRR = LED_PIN;
		GPIOE->BSRR = (1U<<24);
		for (int i = 0; i < 1000000; i++) {}
		GPIOE->BSRR = (1U<<31);
		GPIOE->BSRR = LED_PIN8;
		for (int i = 0; i < 1000000; i++) {}
	}
}
