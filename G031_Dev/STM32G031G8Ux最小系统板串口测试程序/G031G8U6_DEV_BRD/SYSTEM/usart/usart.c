#include "usart.h"

#if EN_USART1_RX

uint8_t USART_RX_BUF[USART_REC_LEN];
uint16_t USART_RX_STA=0;       //鎺ユ敹鐘舵�佸瘎瀛樺櫒锛堜吉锛�

uint8_t aRxBuffer[RXBUFFERSIZE];//HAL搴撲娇鐢ㄧ殑涓插彛鎺ユ敹缂撳啿

//重定义fputc函数
int fputc(int ch, FILE *f)
{
	while((USART2->ISR&0X40)==0);//循环发送,直到发送完毕
    USART2->RDR = (uint8_t) ch;
	return ch;
}

//涓柇鍥炶皟鍑芥暟
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART2)//濡傛灉鏄覆鍙�1
	{
		if((USART_RX_STA&0x8000)==0)//鎺ユ敹鏈畬鎴�
		{
			//鍥炶溅绗︼紙0x0d锛変笌鎹㈣绗︼紙0x0a锛�
			if(USART_RX_STA&0x4000)//鎺ユ敹鍒颁簡0x0d锛堝洖杞﹀墠涓�涓瓧绗︼級
			{
				if(aRxBuffer[0]!=0x0a)
					USART_RX_STA=0;//鎺ユ敹閿欒,閲嶆柊寮�濮�
				else
					USART_RX_STA|=0x8000;	//鎺ユ敹鍒颁簡0x0a锛堝洖杞﹀悗涓�涓瓧绗︼級锛岃〃绀烘帴鏀跺畬鎴愪簡
			}
			else //杩樻病鏀跺埌0X0D
			{
				if(aRxBuffer[0]==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=aRxBuffer[0] ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))
						USART_RX_STA=0;//鎺ユ敹鏁版嵁閿欒,閲嶆柊寮�濮嬫帴鏀�
				}
			}
		}
	}
}

#endif


PUTCHAR_PROTOTYPE
{
	//鍏蜂綋鍝釜涓插彛鍙互鏇存敼huart1涓哄叾瀹冧覆鍙�
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1 , 0xffff);	//闃诲寮忓彂閫�
	return ch;
}






