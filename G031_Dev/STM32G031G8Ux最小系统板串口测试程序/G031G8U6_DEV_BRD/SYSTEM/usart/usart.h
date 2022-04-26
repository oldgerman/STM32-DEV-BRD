#ifndef __USART_H
#define __USART_H
#include "main.h"

#include "stdio.h"//寰楀厛鍖呭惈

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

// 浠ヤ笅涓哄師瀛愮殑
#define USART_REC_LEN  			200  		//瀹氫箟鏈�澶ф帴鏀跺瓧鑺傛暟 200
#define EN_USART1_RX 			1			//浣胯兘锛�1锛�/绂佹锛�0锛変覆鍙�1鎺ユ敹

extern uint8_t  USART_RX_BUF[USART_REC_LEN]; 	//鎺ユ敹缂撳啿,鏈�澶SART_REC_LEN涓瓧鑺�.鏈瓧鑺備负鎹㈣绗�
extern uint16_t USART_RX_STA;         			//鎺ユ敹鐘舵�佹爣璁�
extern UART_HandleTypeDef UART1_Handler; 	//UART鍙ユ焺

#define RXBUFFERSIZE   1 					//缂撳瓨澶у皬
extern uint8_t aRxBuffer[RXBUFFERSIZE];			//HAL搴揢SART鎺ユ敹Buffer

void uart_init(uint32_t bound);


extern UART_HandleTypeDef huart2;
#endif
