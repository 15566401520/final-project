//--------------------------------------------------------
//模块名称：串行口通模块
//文件名称：Uart.c
//作    者: 15160200108 邓明明
//时    间:2017.06.11
//说    明：串行通信接口基本功能
//--------------------------------------------------------

#include "LPC11xx.h"
#include "UART.h"

#define UART_BPS 9600
volatile uint8_t UART_Flag;
uint8_t UART_Buff[10];
uint32_t UART_Num;


void UART_Init(void)
{
    uint16_t usFdiv;
    LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);
    LPC_IOCON->PIO1_6 &=~0X07;
	  LPC_IOCON->PIO1_6 |=(1<<0);
	  LPC_IOCON->PIO1_7 &=~0X07;
	  LPC_IOCON->PIO1_7 |=(1<<0);
	  LPC_SYSCON->SYSAHBCLKCTRL|=(1<<12);
	  LPC_SYSCON->UARTCLKDIV=0X01;
	  LPC_UART->LCR=0X83;
    usFdiv=(SystemCoreClock/LPC_SYSCON->UARTCLKDIV/16)/UART_BPS;
	  LPC_UART->DLM=usFdiv/256;
	  LPC_UART->DLL=usFdiv%256;
    LPC_UART->LCR=0X03;
    LPC_UART->FCR=0X07;
}




void UART_SendByte(uint8_t ucDat) 
{
LPC_UART->THR=ucDat;
while((LPC_UART->LSR&0X40)==0);
}

void UART_SendStr(char*pucStr)
{
	while(1){
		if(*pucStr=='\0')break;
		UART_SendByte(*pucStr++);
	}
}











////--------------------------------------------------------
////函数  名：UART_Init()
////函数功能：串口初始化 接收进中断
////入口参数：波特率
////返回  值：无
////--------------------------------------------------------
//void UART_Init (void)
//{
//	uint16_t usFdiv;
//	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
//	LPC_IOCON->PIO1_6 &=~0x07;
//	LPC_IOCON->PIO1_6 |= (1<<0);
//	LPC_IOCON->PIO1_7 &=~0x07;
//	LPC_IOCON->PIO1_7 |= (1<<0);
//	LPC_SYSCON->SYSAHBCLKCTRL &=~(1<<16);
//	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
//	LPC_SYSCON->UARTCLKDIV = 0x01;
//	LPC_UART->LCR = 0x83;//1000  0011   8位使能对数字锁存器的访问
//	usFdiv = SystemCoreClock / LPC_SYSCON->UARTCLKDIV / 16 / UART_BPS;
//	LPC_UART->DLM = usFdiv / 256;
//	LPC_UART->DLL = usFdiv % 256;
//	LPC_UART->LCR = 0x03;
//	LPC_UART->FCR = 0x87;
//	NVIC_EnableIRQ(UART_IRQn);
//	NVIC_SetPriority(UART_IRQn , 0);
//	LPC_UART->IER = 0x01;
//}


////--------------------------------------------------------
////函数  名：UART_SendByte()
////函数功能：串口发送1字节数据
////入口参数：uint8_t 待发送的数据
////返回  值：无
////--------------------------------------------------------
//void UART_SendByte (uint8_t TData)
//{
//	LPC_UART->THR = TData;
//	while((LPC_UART->LSR & 0x40) == 0);
//}

////--------------------------------------------------------
////函数  名：UART_SendStr()
////函数功能：串口发送字符串
////入口参数：char *PStr 待发送字符串首地址
////返回  值：无
////--------------------------------------------------------
//void UART_SendStr (char *PStr)
//{
//	while(1)
//	{
//		if(*PStr == '\0') break;
//		UART_SendByte(*PStr++);
//	}
//}

//--------------------------------------------------------
//函数  名：UART_IRQHandler()
//函数功能：串口中断服务函数
//入口参数：无
//返回  值：无
//--------------------------------------------------------
//void UART_IRQHandler (void)
//{
//	UART_Num = 0;
//	while((LPC_UART->IIR&0x01) == 0)
//	{
//		switch(LPC_UART->IIR&0x0e)
//		{
//			case 0x04:
//				UART_Flag = 1;
//			  for(UART_Num=0;UART_Num<8;UART_Num++)
//					UART_Buff[UART_Num]=LPC_UART->RBR;
//				break;
//			
//			case 0x0c:
//				UART_Flag = 1;
//				while((LPC_UART->LSR&0x01) == 0x01)
//					UART_Buff[UART_Num++]=LPC_UART->RBR;
//				break;
//				
//			default:
//				break;	
//		}
//	}
//}
