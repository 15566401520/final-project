//--------------------------------------------------------
//模块名称: MF58模块
//文件名称：MF58.c
//作    者: 15160200109 15160200108
//时    间: 2017.06.10
//说    明：热敏电阻模块
//--------------------------------------------------------
#include "MF58.h"
#include "LPC11xx.h"

//--------------------------------------------------------
//函数  名：MF58_GetTemperature()
//函数功能：采集温度值
//入口参数：AD值
//返回  值：温度
//--------------------------------------------------------
float MF58_GetTemperature(uint32_t ADdat)
{
	float res_value=0 , temp=0;
	uint16_t k;
				
	res_value = (ADdat*10000)/(3300-ADdat);    
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

//	
//	if( (Res<29371)&&(Res>=18680) )
//	{
//		k = 1069;
//		T = ((29370-Res)/k)+5;
//	}
//	else if( (Res<18681)&&(Res>=12240) )
//	{
//		k = 644;
//		T = ((18680-Res)/k)+15;
//	}
//	else if( (Res<12241)&&(Res>=8221) )
//	{
//		k = 402;
//		T = ((12240-Res)/k)+25;
//	}
//	else if( (Res<8222)&&(Res>=5648) )
//	{
//		k = 257;
//		T = ((8221-Res)/k)+35;
//	}
//	
//	return T;
}




