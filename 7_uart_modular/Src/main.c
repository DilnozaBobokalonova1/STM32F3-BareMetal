#include <stdio.h>
#include <stdint.h>

#include <uart.h>
#include "stm32f3xx.h"

/*NOTE: LEFT TO USE AFTER GETTING THE USB TO SERIAL CONVERTER. */
/* Our USART2 is connected to APB1 bus, hence enable it */
/* USART2 is within bit 17 of APB1_ENR Register */
/* PA2(Tx) and PA3 (rx) are Tx/Rx port pins under column AF7 (Alternate Function 7) */
/* So enable PA2 and PA3 and configure to be Alternate Function mode*/
int main(void) {
	uart2_tx_init();

	while(1) {
		printf("Hello from STM32F3Discovery .........\n\r");
	}
}

