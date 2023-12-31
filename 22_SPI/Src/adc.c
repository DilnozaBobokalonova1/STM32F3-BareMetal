/*
 * adc.c
 *
 *  Created on: Aug 16, 2023
 *      Author: dilnozabobokalonova
 */
#include "stm32f3xx.h"
#include <adc.h>

#define GPIOAEN				(1U<<17)
//I'd like to enable ADC2_IN2 that is located at PA5
//our ADC1/2 within RCC clock enable register is at bit 28
#define ADC2EN				(1U<<28)

//#define ADC2_CH2		(~(0x1F<<6) | (1<<1))
//the sequence length will be 1 as we are only making one conversion
#define ADC_SEQ_LEN_1	 	0x00

#define CR_AD_EN			(1U<<00)
#define CR_ADSTART			(1U<<2)

//status register end of conversion flag
//our EOC is at bit 2 of the register
//setting it to 1 means ADC conversion complete
#define SR_EOC				(1U<<2)

//adc configged with 3 channels
//ch2, ch3, ch5
//1st = ch5
//2nd = ch2
//3rd = ch3
void pa_5_adc_init(void) {

	/*Configure the ADC GPIO pin*/

	/*Enable clock access to GPIOA*/
	RCC->AHBENR |= GPIOAEN;
	/*Set the mode of PA5 to analog mode*/
	/* PA5 is located at MODE5 which are bits 10 & 11 */
	/* To set to analog mode, both bits have to be set to 1 */
//	GPIOA->MODER |= (1U<<10);
//	GPIOA->MODER |= (1U<<11);
	//one-liner
	GPIOA->MODER |= ((1U << 10) | (1U << 11));

	/*Configure the ADC module*/
	/*Enable clock access to ADC */
	//our ADCs are connected to AHB3 bus
	RCC->AHBENR |= ADC2EN;

	/*Conversion sequence length*/
	//setting it first cus it's located within SQ1 which I'm later using to set my channel
	ADC2->SQR1 = ADC_SEQ_LEN_1;
	/*Conversion sequence start*/
	//our SQR1's SQ1 needs to be set to channel 2 (ADC2_IN2 is chann 2)
	//hence we set the bits of SQ1 to contain 2 in binary form.
	uint32_t currentVal = ADC2->SQR1;
	//we set the bits 6-10 to 00010 to represent the 2nd channel being in 1st sequence
	ADC2->SQR1 = (currentVal & ~ 0xC0) | (0x01 << 7);
	/*Enable ADC module*/
	//in my case, the channel I'm using is channel 2
	ADC2->CR = CR_AD_EN;


}

void start_conversion(void) {
	//start the ADC conversion
	//need to check control registers to see which value allows us to start conversion
	ADC2->CR |= CR_ADSTART;

}

uint32_t adc_read(void) {
	//wait for the conversion to be complete
	//while the status register for EOC is set to 0,
	//aka conversion not complete, we get stuck here
	while (!(ADC2->ISR & SR_EOC)) {};

	//Read converted result
	return (ADC2->DR);

}





