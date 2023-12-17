#include "spi.h"
#include "stm32f3xx.h"

#define SPI1EN				(1U<<12)
#define GPIOAEN				(1U<<17)

//PA4 -> NSS
//PA5 -> SCK
//PA6 -> MISO
//PA7 -> MOSI
void spi_gpio_init(void) {
	//Enable clock access to GPIOA
	RCC->AHBENR |= GPIOAEN;
	//configure the above pins to alternate function mode
	//using the mode register: Alternate Func mode 10

	//PA4 SS line as Output pin since it'll be set
	//high and low to select the slave device (01)
	GPIOA->MODER |= (1U<<8);
	GPIOA->MODER &= ~(1U<<9);

	//PA5
	//set first bit (within MODER 5) to 0
	// 1101 0000 0001 & (1110 1111 1111) = 1100 0000 0001
	GPIOA->MODER &=~ (1U<<10);
	//set second bit (within MODER 5) to 1
	// 1100 0000 0001 | (0010 0000 0000) = 1110 0000 0001
	GPIOA->MODER |= (1U<<11);

	//PA6
	GPIOA->MODER &=~ (1U<<12);
	GPIOA->MODER |= (1U<<13);

	//PA7
	GPIOA->MODER &=~ (1U<<14);
	GPIOA->MODER |= (1U<<15);

	//Set PA5,PA6,PA7 alternate function type to SPI1
	//0101: AF5 in the alternate function low register

	//PA5: AFRL bits 20, 21, 22, 23.
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &= ~(1U<<21);
	GPIOA->AFR[0] |= (1U<<22);
	GPIOA->AFR[0] &= ~(1U<<23);

	//PA6: AFRL bits 24, 25, 26, 27.
	GPIOA->AFR[0] |= (1U<<24);
	GPIOA->AFR[0] &= ~(1U<<25);
	GPIOA->AFR[0] |= (1U<<26);
	GPIOA->AFR[0] &= ~(1U<<27);

	//PA7: AFRL bits 28, 29, 30, 31.
	GPIOA->AFR[0] |= (1U<<28);
	GPIOA->AFR[0] &= ~(1U<<29);
	GPIOA->AFR[0] |= (1U<<30);
	GPIOA->AFR[0] &= ~(1U<<31);
}

void spi_config(void) {
	//Enable clock access to SPI1 module
	RCC->APB2ENR |= SPI1EN;

	//set the clock of the SPI to fPCLK/4 001
	SPI1->CR1 |= (1U<<3);
	SPI1->CR1 &= ~(1U<<4);
	SPI1->CR1 &= ~(1U<<5);

	//Set CPOL to 1 and CPHA to 1
	SPI1->CR1 |= (1U<<0);
	SPI1->CR1 |= (1U<<1);

	//enable full duplex mode: set bit 10 to 0
	SPI1->CR1 &= ~(1U<<10);

	//set MSB First: bit 7 set to 0
	SPI1->CR1 &= ~(1U<<7);

	//Set SPI to be in Master Mode (MC is Master, Sensor is Slave)
	SPI1->CR1 |= (1U<<2);

	//Set 8-bit data mode
	SPI1->CR1 &= ~(1U<<11);

	//Set SSM & SSI
	SPI1->CR1 |= (1U<<8);
	SPI1->CR1 |= (1U<<9);

	//Enable SPI module peripheral
	SPI1->CR1 |= (1U<<6);
}





