//--------------------------------------------------------
//模块名称：串行口通模块
//文件名称：Uart.c
//作    者: 15160200108 邓明明
//时    间: 2017.06.11
//说    明：串行通信接口基本功能
//--------------------------------------------------------

#ifndef __UART_H__
#define __UART_H__

#include "LPC11xx.h"

extern void UART_Init (void);
extern void UART_SendByte (uint8_t TData);
extern void UART_SendStr (char *PStr);

#endif
