/*
 * uart.h
 *
 *  Created on: Dec 17, 2023
 *      Author: dilnozabobokalonova
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f3xx.h"

void uart2_rx_tx_init(void);
void uart2_tx_init(void);
char uart2_read(void);

#endif /* UART_H_ */
