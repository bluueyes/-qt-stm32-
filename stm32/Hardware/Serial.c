#include "stm32f10x.h"    // Device header
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stm32f10x_usart.h>

uint8_t Serial_TxPacket[4];				//FF 01 02 03 04 FE
uint8_t Serial_RxPacket[4];
uint8_t Serial_RxFlag;

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(USART_TypeDef* USARTx, char *DataString)
{
	int i = 0;
	USART_ClearFlag(USARTx,USART_FLAG_TC);										//发送字符前清空标志位（否则缺失字符串的第一个字符）
	while(DataString[i] != '\0')												//字符串结束符
	{
		USART_SendData(USARTx,DataString[i]);									//每次发送字符串的一个字符
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == 0);					//等待数据发送成功
		USART_ClearFlag(USARTx,USART_FLAG_TC);									//发送字符后清空标志位
		i++;
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
//	Serial_SendString(String);
}


void Serial_SendPacket(void)
{
	Serial_SendByte(0xFF);
	Serial_SendArray(Serial_TxPacket, 4);
	Serial_SendByte(0xFE);
}

uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

char USART_ReceiveString[50];													//接收PC端发送过来的字符
int Receive_Flag = 0;															//接收消息标志位
int Receive_sum = 0;															//数组下标
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == 1)							//USART_FLAG_RXNE判断数据，== 1则有数据
	{
		if(Receive_sum > 49)													//数组能存放50个字节的数据				
		{
			USART_ReceiveString[49] = '\0';										//数据字节超过50位时，将最后一位设置为\0	
			Receive_Flag = 1;													//接收标志位置1，停止接收数据
			Receive_sum = 0;													//数组下标置0
		}
		
		if(Receive_Flag == 0)													//接收标志位等于0，开始接收数据
		{
			USART_ReceiveString[Receive_sum] = USART_ReceiveData(USART1);		//通过USART1串口接收字符
			Receive_sum++;														//数组下标++
		}
		
		if(Receive_sum >= 2)													//数组下标大于2
		{
			if(USART_ReceiveString[Receive_sum-2] == '\r' && USART_ReceiveString[Receive_sum-1] == '\n' )
			{
				USART_ReceiveString[Receive_sum-1] = '\0';						
				USART_ReceiveString[Receive_sum-2] = '\0';
				Receive_Flag = 1;												//接收标志位置1，停止接收数据
				Receive_sum = 0;												//数组下标置0
				printf("%s\r\n",USART_ReceiveString);					

				if(strcmp(USART_ReceiveString,"hello") == 0)
				{
					GPIO_WriteBit(GPIOA, GPIO_Pin_9, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_9))); // 翻转PA9
				}
				if(strcmp(USART_ReceiveString,"world") == 0)
				{
					GPIO_WriteBit(GPIOA, GPIO_Pin_10, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_10))); // 翻转PA10
				}
				if(strcmp(USART_ReceiveString,"jiajia") == 0)
				{
					GPIO_WriteBit(GPIOA, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_13))); // 翻转PA13
				}
				if(strcmp(USART_ReceiveString,"haha") == 0)
				{
					GPIO_WriteBit(GPIOA, GPIO_Pin_14, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_14))); // 翻转PA14
				}
			}		
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);							//接收后先清空标志位
	}
}
