//--------------------------------------------------------
//ģ�����ƣ�������
//�ļ����ƣ�main.c
//��    ��: 15160200108 15160200109
//ʱ    ��: 2017.06.11
//˵    ������
//--------------------------------------------------------
#include "LPC11xx.h"
#include "UART.h"
#include "ADC.h"
#include "LED.h"
#include "KEY.h"
#include <stdio.h>
#include <string.h>

extern volatile uint8_t UART_Flag;
char AD_Data_Buff[20];
extern uint8_t choose;


//--------------------------------------------------------
//����  ����main()
//�������ܣ�����
//��ڲ�������
//����  ֵ������״̬
//--------------------------------------------------------
int main (void)
{
	float Temp; 
	uint32_t i;
	UART_Init();
	LED_Init();
	ADC_Init();
	KEY_Init();
	while(1)
	{
		Temp=MF58(ADC_Read());
		
		
		for(i=0;i<100;i++)
			LED(Temp,choose);
		
//		if(UART_Flag==1)	
//		{
//			UART_Flag = 0;
//			if(choose==1)	Temp=Temp*1.8+32;
			sprintf(AD_Data_Buff , "�¶�%4.2f�� \r\n" , Temp);	
			UART_SendStr(AD_Data_Buff);
//			
//		}
	}	
}

