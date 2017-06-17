//--------------------------------------------------------
//模块名称：数码管模块
//文件名称：LED.h
//作    者:15160200109 赵恩仪
//时    间: 2017.06.09
//说    明：数码管显示
//--------------------------------------------------------
#ifndef __LED_H__
#define __LED_H__

#include "LPC11xx.h" 

extern void LED_Init (void);
extern void LED (uint16_t Num,uint8_t mode);
extern void delay (void);

#endif
