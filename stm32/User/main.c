#include "stm32f10x.h"
#include "dht11.h"
#include "Serial.h"
#include <string.h>

// 定义数据缓冲区（长度需足够容纳格式化后的字符串）
#define DATA_BUFFER_SIZE 64
char dht11_data_buffer[DATA_BUFFER_SIZE];
DHT11_Data_TypeDef data;

int main()
{
//	Systick_Init();
	Serial_Init();
	DHT11_Init(GPIO_Mode_Out_PP);
	Serial_SendString(USART1, "Hello world!\r\n");

	while(1)
	{
		// 数据校验成功后，格式化到字符串
		if( Read_DHT11 ( & data ) == SUCCESS) {
			snprintf(dht11_data_buffer, DATA_BUFFER_SIZE, 
					"T:%.1f, H:%.1f\n", 
					data.temp_int + data.temp_deci * 0.1,
					data.humi_int + data.humi_deci * 0.1);
		} else {
			strncpy(dht11_data_buffer, "DHT11 Error", DATA_BUFFER_SIZE);
			
		}
		Serial_SendString(USART1,dht11_data_buffer);
		Delay_s(1);															//延时1us
	}
}
