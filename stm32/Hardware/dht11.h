#ifndef _DHT11_H_
#define _DHT11_H_

//头文件
#include "stm32f10x.h"
#include "Delay.h"
#include "Serial.h"


//宏定义
#define DHT11_HIGH  1                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
#define DHT11_LOW   0
#define DHT11_DATA_OUT(a) \
    do { \
        if (a) \
            GPIO_SetBits(GPIOA, GPIO_Pin_1); \
        else \
            GPIO_ResetBits(GPIOA, GPIO_Pin_1); \
    } while(0)

#define  DHT11_DATA_IN()	  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)

//外部变量声明
typedef struct
{
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
}DHT11_Data_TypeDef;

//函数声明
void DHT11_Init(GPIOMode_TypeDef mode);
unsigned char Read_Byte(void);
unsigned char Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);

#endif //__DHT11_H_
