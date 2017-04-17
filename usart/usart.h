#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"

void initialise_usart1(u32 baud_rate);
void initialise_usart2(u32 baud_rate);
void initialise_usart3(u32 baud_rate);
void initialise_uart4(u32 baud_rate);
void initialise_uart5(u32 baud_rate);

void usart_send_byte(USART_TypeDef * pUSARTx, uint8_t byte);
void usart_send_string(USART_TypeDef * pUSARTx, char* string);
void usart_send_array(USART_TypeDef * pUSARTx, u8* array, u8 length);

#endif /* __USART_H */
