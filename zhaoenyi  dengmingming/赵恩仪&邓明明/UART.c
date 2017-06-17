//--------------------------------------------------------
//ģ�����ƣ����п�ͨģ��
//�ļ����ƣ�Uart.c
//��    ��: 15160200108 ������
//ʱ    ��:2017.06.11
//˵    ��������ͨ�Žӿڻ�������
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
////����  ����UART_Init()
////�������ܣ����ڳ�ʼ�� ���ս��ж�
////��ڲ�����������
////����  ֵ����
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
//	LPC_UART->LCR = 0x83;//1000  0011   8λʹ�ܶ������������ķ���
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
////����  ����UART_SendByte()
////�������ܣ����ڷ���1�ֽ�����
////��ڲ�����uint8_t �����͵�����
////����  ֵ����
////--------------------------------------------------------
//void UART_SendByte (uint8_t TData)
//{
//	LPC_UART->THR = TData;
//	while((LPC_UART->LSR & 0x40) == 0);
//}

////--------------------------------------------------------
////����  ����UART_SendStr()
////�������ܣ����ڷ����ַ���
////��ڲ�����char *PStr �������ַ����׵�ַ
////����  ֵ����
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
//����  ����UART_IRQHandler()
//�������ܣ������жϷ�����
//��ڲ�������
//����  ֵ����
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
