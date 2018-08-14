/*
 * UART_Utils.h
 *
 *  Created on: 27 בפבר׳ 2018
 *      Author: haite
 */

#ifndef APPLICATION_UART_UTILS_H_
#define APPLICATION_UART_UTILS_H_

#include "Board.h"
#include <ti/drivers/uart/UARTCC32XX.h>


extern void uart_function(void);
extern void Write_Message(const char *msg);
extern void Clean_terminal();

#endif /* APPLICATION_UART_UTILS_H_ */
