//--------------------------------------------------------
//模块名称：模数转换模块
//文件名称：ADC.c
//作    者: 15160200109  赵恩仪
//时    间: 2017.06.11
//说    明：ADC1 P0_1
//--------------------------------------------------------


#include "LPC11xx.h"
#include "ADC.h"

uint32_t ADCBuf,ADCFlag;
uint8_t Buff[20];

//--------------------------------------------------------
//函数  名：ADC_Init
//函数功能：ADC1 初始化
//入口参数：无
//返回  值：无
//--------------------------------------------------------

void ADC_Init(void)
{
	   
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);
	LPC_IOCON->PIO1_11&=~0xBF;
	LPC_IOCON->PIO1_11|=0x01;
	LPC_SYSCON->PDRUNCFG&=~(0X01<<4);
	LPC_SYSCON->SYSAHBCLKCTRL|=(0X01<<13);
	LPC_ADC->CR = (1<<7)|                     /* bit7:bit0   选择通道7作为ADC输入，即P1.11引脚 */
	          ((SystemCoreClock/1000000-1)<<8)|
						(0<<16)|
						(0<<17)|
						(0<<24)|
						(0<<27);
}





//void ADC_Init (void)
//{
//	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);	
//	LPC_IOCON->R_PIO1_0 &=~0xbf;	
//	LPC_IOCON->R_PIO1_0 |= 0x02;	
//	LPC_SYSCON->SYSAHBCLKCTRL &=~(1<<16);	
//	LPC_SYSCON->PDRUNCFG &=~(0x01<<4);		
//	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);	 
//	LPC_ADC->CR = (0x01<<1)|((SystemCoreClock/1000000-1)<<8)|(0<<16)|(0<<17)|(0<<24)|(0<<27);	
//}

//--------------------------------------------------------
//函数  名：ADC_Read
//函数功能：ADC 采集转化
//入口参数：AD通道
//返回  值：电压值
//--------------------------------------------------------
//uint32_t ADC_Read(uint8_t C)
//{
//	uint32_t adc_value=0;
//	uint32_t ulADCBuf=0;
//	uint8_t i;
//	
//	for(i=0;i<30;i++)
//	{
//		adc_value = ((LPC_ADC->DR[C]>>6)&0x3FF);			    
//		ulADCBuf += adc_value;
//	}
//	adc_value = ulADCBuf / 30;
//	adc_value = (adc_value*3300)/1024; 
//	
//	return adc_value; 
//}

////--------------------------------------------------------
////函数  名：ADC_Get
////函数功能：ADC 取值
////入口参数：ADC通道数
////返回  值：uint32_t 
////--------------------------------------------------------
//uint32_t ADC_Get (void)
//{
//	uint32_t ulADCDat=0 , ulADCBuf=0;
//	uint8_t i=0;

//	for(i=0;i<10;i++)
//	{
//		LPC_ADC->CR |= (1<<24);
//		while((LPC_ADC->DR[1]&0x80000000) == 0);
//		LPC_ADC->CR |= (1<<24);
//		while((LPC_ADC->DR[1]&0x80000000) == 0);
//		ulADCBuf = LPC_ADC->DR[1];
//		ulADCBuf = (ulADCBuf>>6)&0x3ff;
//		ulADCDat += ulADCBuf;
//	}
//	ulADCDat = ulADCDat / 10;
//	ulADCDat = (ulADCDat*3300)/1024;
//	
//	return ulADCDat;
//}



uint32_t ADC_Read(void)
{
	uint32_t adc_value=0;
	uint32_t adc_data=0;
	uint32_t i;

	for(i=0;i<10;i++)		  // 再连续读取10个电压值
	{
    
  		LPC_ADC->CR|=(1<<24);
			while((LPC_ADC->DR[7]&0x80000000)==0);
			LPC_ADC->CR|=(1<<24);
			
		  while((LPC_ADC->DR[7]&0x80000000)==0);
			adc_value=LPC_ADC->DR[7];
			adc_value=(adc_value>>6)&0x03ff;
			adc_data+=adc_value;


	}
	
	
	adc_data = adc_data/10;  // 把读到的10个电压值取平均值
	adc_data = (adc_data*3300)/1024; // 转换为真正的电压值

	return adc_data;	  // 返回结果
}

//--------------------------------------------------------
//函数  名：ADC_IRQHandler
//函数功能：ADC中断服务函数
//入口参数：无
//返回  值：无
//--------------------------------------------------------
void ADC_IRQHandler (void)
{
	ADCBuf = LPC_ADC->DR[1];
	ADCBuf = (ADCBuf>>6)&0x3ff;
	ADCFlag = 1;
}

//--------------------------------------------------------
//函数  名：MF58
//函数功能：采集温度值
//入口参数：AD值
//返回  值：温度
//--------------------------------------------------------
float MF58 (uint32_t ADdat)
{


	float res_value=0 , temp=0;
	uint16_t k;
				
	res_value = (ADdat*10000)/(3296-ADdat);    
//	
//uint32 k;   // 斜率
//	int32 temp;  //	温度值
	
	if( (res_value<33970)&&(res_value>20310) ) // 0~10摄氏度
	{
	 	k = 1366;
		temp = ((33970-res_value)/k)+0;
	}
	else if( (res_value<20310)&&(res_value>12570) )	// 10~20摄氏度
	{
	  	k = 774;
		temp = ((20310-res_value)/k)+10;
	}
	else if( (res_value<12570)&&(res_value>8034) )	// 20~30摄氏度
	{
	  	k = 454;
		temp = ((12570-res_value)/k)+20;
	}
	else if( (res_value<8034)&&(res_value>5298) )	// 30~40摄氏度
	{
	  	k = 274;
		temp = ((8034-res_value)/k)+30;
	}
	else if( (res_value<5298)&&(res_value>3586) )	// 40~50摄氏度
	{
	  	k = 171;
		temp = ((5298-res_value)/k)+40;
	}
	else if( (res_value<3586)&&(res_value>2484) )	// 50~60摄氏度
	{
	  	k = 110;
		temp = ((3586-res_value)/k)+50;
	}
		


	return  temp;   // 返回温度值

//	float Res=0 , T=0;
//	uint16_t k;
//				
//	Res = (ADdat*10000)/(3296-ADdat);    
//			
//	if( (Res<29371)&&(Res>=18680) )
//	{
//		k = 1069;
//		T = ((29370-Res)/k)+3;
//	}
//	else if( (Res<18681)&&(Res>=12240) )
//	{
//		k = 644;
//		T = ((18680-Res)/k)+13;
//	}
//	else if( (Res<12241)&&(Res>=8221) )
//	{
//		k = 402;
//		T = ((12240-Res)/k)+23;
//	}
//	else if( (Res<8222)&&(Res>=5648) )
//	{
//		k = 257;
//		T = ((8221-Res)/k)+33;
//	}
//	
//	return T;
}


