//--------------------------------------------------------
//ģ�����ƣ����п�ͨģ��
//�ļ����ƣ�Uart.c
//��    ��: 15160200108 ������
//ʱ    ��: 2017.06.11
//˵    ��������ͨ�Žӿڻ�������
//--------------------------------------------------------

#ifndef __UART_H__
#define __UART_H__

#include "LPC11xx.h"

extern void UART_Init (void);
extern void UART_SendByte (uint8_t TData);
extern void UART_SendStr (char *PStr);

#endif
