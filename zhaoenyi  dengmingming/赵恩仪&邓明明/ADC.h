//--------------------------------------------------------
//ģ�����ƣ�ģ��ת��ģ��ײ�����
//�ļ����ƣ�ADC.c
//��    ��: 15160200109 �Զ���
//ʱ    ��: 2016.06.11
//˵    ����ADC1 P0_1
//--------------------------------------------------------


#ifndef __ADC_H__
#define __ADC_H__

#include "LPC11xx.h"

void ADC_Init (void);


extern uint32_t ADC_Read(void);


//uint32_t ADC_Get (void);
extern float MF58 (uint32_t ADdat);

#endif
