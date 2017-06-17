//--------------------------------------------------------
//模块名称：模数转换模块底层驱动
//文件名称：ADC.c
//作    者: 15160200109 赵恩仪
//时    间: 2016.06.11
//说    明：ADC1 P0_1
//--------------------------------------------------------


#ifndef __ADC_H__
#define __ADC_H__

#include "LPC11xx.h"

void ADC_Init (void);


extern uint32_t ADC_Read(void);


//uint32_t ADC_Get (void);
extern float MF58 (uint32_t ADdat);

#endif
