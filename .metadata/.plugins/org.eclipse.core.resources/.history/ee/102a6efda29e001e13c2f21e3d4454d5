#include "stdio.h"
#include "stdint.h"
#include "stm32f3xx.h"
#include "adc.h"

#define GPIOEEN					(1U<<21)

#define PIN15					(1U<<15)
#define LED_PIN					PIN15
#define PIN8					(1U<<8)
#define LED_PIN8				PIN8

uint32_t sensor_value;

int main(void) {

	RCC->AHBENR |= GPIOEEN;
	GPIOE->MODER |= (1U<<30);
	GPIOE->MODER &=~(1U<<31);
	GPIOE->MODER |= (1U<<16);
	GPIOE->MODER &= ~(1U<<17);



	pa_1_adc_init();
	start_conversion();

	while(1) {
		sensor_value = adc_read();
//		GPIOE->BSRR = LED_PIN;
//		GPIOE->BSRR = LED_PIN8;
		printf("sensor value: %d \n\r", (int) sensor_value);
		if ((int) sensor_value == 0) {
			GPIOE->BSRR = (1U<<31);
			GPIOE->BSRR = (1U<<24);
//			GPIOE->BSRR = LED_PIN;
//			GPIOE->BSRR = LED_PIN8;
		} else {
			GPIOE->BSRR = (1U<<31);
			GPIOE->BSRR = (1U<<24);
		}
	}
}
