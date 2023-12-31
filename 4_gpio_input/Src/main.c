#include "stm32f3xx.h"

#define GPIOAEN					(1U<<17)
#define GPIOEEN					(1U<<21)

#define PIN15					(1U<<15)
#define LED_PIN					PIN15
#define PIN8					(1U<<8)
#define LED_PIN8				PIN8

#define PIN0					(1U<<0)
#define BTN_PIN					PIN0


//B1 USER: user and wake-up button connected to the I/O PA0
//when we press the push button, the LED comes on
int main(void) {
	/*Enable clock access to GPIOA & GPIOE*/
	RCC->AHBENR |= GPIOAEN;
	RCC->AHBENR |= GPIOEEN;

	/*Set PE8 & PE15 as Output Pins
	 * set MODER bits 16/17, 30/31 */

	//it's like 8*2
	GPIOE->MODER |= (1U<<30);
	//it's like 8*2 + 1
	GPIOE->MODER &=~(1U<<31);

	GPIOE->MODER |= (1U<<16);
	GPIOE->MODER &= ~(1U<<17);

	/*Set PA0 as Input Pin so set MODER bits 0,1 to 00*/
	GPIOA->MODER &=~(1U<<0);
	GPIOA->MODER &=~(1U<<1);

	while(1) {
		//Button is pressed
		if (GPIOA->IDR & BTN_PIN) { //if both result in 1
			//turn on LED
			//BSRR bits 15:0 correspond to setting the bit
			GPIOE->BSRR = LED_PIN;
			GPIOE->BSRR = LED_PIN8;
		} else {
			//turn off LED
			//BSRR bits 31:16 correspond to resetting
			GPIOE->BSRR = (1U<<31);
			GPIOE->BSRR = (1U<<24);
		}
	}

}
