#include "stm32f10x.h"
#include "dht11.h"
#include "Serial.h"
#include <string.h>
#include "fan_controller.h"



// 定义数据缓冲区（长度需足够容纳格式化后的字符串）
#define DATA_BUFFER_SIZE 64
char dht11_data_buffer[DATA_BUFFER_SIZE];
DHT11_Data_TypeDef data;

int main()
{
//	Systick_Init();
	Fan_Init();
	Serial_Init();
	DHT11_Init(GPIO_Mode_Out_PP);
	Serial_SendString(USART1, "Hello world!\r\n");

//	DHT11_Data_TypeDef dht_data;
    uint8_t fan_speed = 0;
	
	while(1)
	{
		// 数据校验成功后，格式化到字符串
		if( Read_DHT11 ( & data ) == SUCCESS) {
			snprintf(dht11_data_buffer, DATA_BUFFER_SIZE, 
					"T:%.1f, H:%.1f, V:%u\n", 
					data.temp_int + data.temp_deci * 0.1,
					data.humi_int + data.humi_deci * 0.1,fan_speed);
		    
			// 根据温度自动控制风扇
            if (data.temp_int > 30 && !Serial_GetRxFlag()) {
                fan_speed = 100;  // 全速
				//Serial_SendByte(fan_speed);
            } else if (data.temp_int > 20 && !Serial_GetRxFlag()) {
                fan_speed = 70;   // 70%转速
				//Serial_SendByte(fan_speed);
            }else if(Serial_GetRxData() <100&& Serial_GetRxFlag()){
				fan_speed = Serial_GetRxData();
				//Serial_SendByte(fan_speed);
			}else {
                fan_speed = 0;    // 关闭
				//Serial_SendByte(fan_speed);
            }
			Fan_SetDirection(FAN_FORWARD);  // 设置正转
            Fan_SetSpeed(fan_speed);        // 更新转速
		
		} else {
			strncpy(dht11_data_buffer, "DHT11 Error", DATA_BUFFER_SIZE);
			
		}
		Serial_SendString(USART1,dht11_data_buffer);
	
		Delay_s(1);			//延时1us
        
    }
	
}
