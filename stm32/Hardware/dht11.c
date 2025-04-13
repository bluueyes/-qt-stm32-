#include "dht11.h"

#define DHT11_PIN   GPIO_Pin_1
#define DHT11_PORT  GPIOA

//DHT11初始化，并将模式以参数形式传入
void DHT11_Init(GPIOMode_TypeDef mode)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    // 使能GPIOA时钟（APB2总线）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = DHT11_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    
    // 根据模式配置GPIO
    if (mode == GPIO_Mode_Out_PP) {
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出
    } else {
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
    }
    
    GPIO_Init(DHT11_PORT, &GPIO_InitStruct);			//初始化
}

//读取DHT11的数据
unsigned char Read_Byte(void)
{
    uint8_t data = 0;
    for (int i = 0; i < 8; i++) {
        while (DHT11_DATA_IN() == 0); // 等待低电平结束
        
        Delay_us(40); // 关键延时（必须为微秒级）
        
        if (DHT11_DATA_IN() == 1) {   // 检测高电平
            data |= (1 << (7 - i));   // MSB优先
            while (DHT11_DATA_IN() == 1); // 等待高电平结束
        }
    }
    return data;
}

unsigned char Read_DHT11(DHT11_Data_TypeDef *data)
{  
    uint16_t retry = 0;
    
    // 发送起始信号
    DHT11_Init(GPIO_Mode_Out_PP);
    DHT11_DATA_OUT(0);
    Delay_ms(18);    // 18ms低电平
    
    DHT11_DATA_OUT(1);
    Delay_us(30);    // 30us高电平
    
    // 切换为输入模式
    DHT11_Init(GPIO_Mode_IN_FLOATING);
    
    // 等待DHT11响应
    retry = 0;
    while (DHT11_DATA_IN() == 1) {  // 等待低电平
        if (retry++ > 100) return 0;
        Delay_us(1);
    }
    
    retry = 0;
    while (DHT11_DATA_IN() == 0) {  // 等待高电平
        if (retry++ > 100) return 0;
        Delay_us(1);
    }
    
    retry = 0;
    while (DHT11_DATA_IN() == 1) {  // 等待数据开始
        if (retry++ > 100) return 0;
        Delay_us(1);
    }
    
    // 读取数据
    data->humi_int  = Read_Byte();
    data->humi_deci = Read_Byte();
    data->temp_int  = Read_Byte();
    data->temp_deci = Read_Byte();
    data->check_sum = Read_Byte();
    
    // 校验数据
    if (data->check_sum == data->humi_int + data->humi_deci + data->temp_int + data->temp_deci) {
        return 1;
    }
    return 0;
}
