/*
 * adc.c
 *
 *  Created on: Aug 16, 2023
 *      Author: dilnozabobokalonova
 */
#include "stm32f3xx.h"
#include <adc.h>

#define GPIOAEN					(1U<<17)

//ADC1/2 are enabled within RCC clock enable register
//for AHB3 bus located at bit position 28
#define ADC1EN					(1U<<28)

// ADC1 Channel 2 to be put within Sequence register 1 that
// starts at bit position 6 of ADC regular sequence register 1.
// set positions 6-10 to 00010 in the 32-bit register (0000 ... 0000 1000 0000)
#define ADC1_CH2				(1U<<7)

//00000 for only 1 conversion length
#define ADC1_SEQ_LEN	 		0x00

//Set bit 0 to 1 within the ADC Control Register to enable the ADC
#define CR_ADC_EN				(1U<<00)
//Set bit 2 to 1 within the ADC Control Register to start the ADC conversion
#define CR_ADC_START			(1U<<2)

//status register end of conversion flag
//our EOC is at bit 2 of the register
//setting it to 1 means ADC conversion complete
#define SR_EOC					(1U<<2)


#define GPIOEEN					(1U<<21)
#define PIN15					(1U<<15)
#define LED_PIN					PIN15
#define PIN8					(1U<<8)
#define LED_PIN8				PIN8

void pa_1_adc_init(void) {

					/*Configure the ADC GPIO pin*/

	/*	Enable clock access to GPIOA*/
	RCC->AHBENR |= GPIOAEN;

	/*	Set the mode of PA1 to analog mode*/
	/* 	PA1 is located at MODE1 which are bits 2 & 3 */
	/* 	To set to analog mode, both bits have to be set to 1 */
	GPIOA->MODER |= ((1U << 2) | (1U << 3));

					/*Configure the ADC module*/

	/*Enable clock access to ADC */
	RCC->AHBENR |= ADC1EN;

	/*Conversion sequence start*/
	//I'm using Channel 2 within ADC1 so set first conversion of sequence register to 00010
	ADC1->SQR1 = ADC1_CH2;

	//Set the sequence length of the ADC conversion
	//Now note that the SQR1 SQ1 bits have been set, so we cannot modify them. OR the SEQ len bits
	ADC1->SQR1 |= ADC1_SEQ_LEN;

	/*Enable ADC module*/
	ADC1->CR |= CR_ADC_EN;
}

void start_conversion(void) {
	//start the ADC conversion
	ADC1->CR |= CR_ADC_START;

}

uint32_t adc_read(void) {

	RCC->AHBENR |= GPIOEEN;
	GPIOE->MODER |= (1U<<30);
	GPIOE->MODER &=~(1U<<31);
	GPIOE->MODER |= (1U<<16);
	GPIOE->MODER &= ~(1U<<17);

	//wait for the conversion to be complete
	//while the status register for EOC is set to 0,
	//aka conversion not complete, we get stuck here
	while (!(ADC1->ISR & SR_EOC)) {
		GPIOE->BSRR = LED_PIN;
		GPIOE->BSRR = LED_PIN8;
		GPIOE->BSRR = (1U<<31);
		GPIOE->BSRR = (1U<<24);
	};

//	GPIOE->BSRR = (1U<<31);
//	GPIOE->BSRR = (1U<<24);
	//Read converted result
	return (ADC1->DR);
}





