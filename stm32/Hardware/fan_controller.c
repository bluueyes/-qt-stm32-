#include "fan_controller.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

#define FAN_PWM_PIN      GPIO_Pin_6
#define FAN_PWM_PORT     GPIOA
#define FAN_IN1_PIN      GPIO_Pin_4
#define FAN_IN2_PIN      GPIO_Pin_5
#define FAN_GPIO_PORT    GPIOA
#define FAN_PWM_TIM      TIM3
#define FAN_PWM_CHANNEL  TIM_Channel_1

// 初始化PWM和GPIO
void Fan_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_InitStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;

    // 1. 使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    // 2. 配置方向控制引脚（PA4, PA5）
    GPIO_InitStruct.GPIO_Pin = FAN_IN1_PIN | FAN_IN2_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FAN_GPIO_PORT, &GPIO_InitStruct);

    // 3. 配置PWM引脚（PA6 - TIM3_CH1）
    GPIO_InitStruct.GPIO_Pin = FAN_PWM_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;  // 复用推挽输出
    GPIO_Init(FAN_PWM_PORT, &GPIO_InitStruct);

    // 4. 初始化定时器（PWM频率 = 72MHz / (719 + 1) / (999 + 1) = 100Hz）
    TIM_InitStruct.TIM_Prescaler = 719;       // 72MHz / 720 = 100kHz
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStruct.TIM_Period = 999;          // 100kHz / 1000 = 100Hz
    TIM_InitStruct.TIM_ClockDivision = 0;
    TIM_TimeBaseInit(FAN_PWM_TIM, &TIM_InitStruct);

    // 5. 配置PWM通道
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 0;           // 初始占空比0%
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(FAN_PWM_TIM, &TIM_OCInitStruct);

    // 6. 启动PWM
    TIM_CtrlPWMOutputs(FAN_PWM_TIM, ENABLE);
    TIM_OC1PreloadConfig(FAN_PWM_TIM, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(FAN_PWM_TIM, ENABLE);
    TIM_Cmd(FAN_PWM_TIM, ENABLE);

    // 7. 初始状态：停止
    GPIO_ResetBits(FAN_GPIO_PORT, FAN_IN1_PIN | FAN_IN2_PIN);
}

// 设置风扇转速（0-100%）
void Fan_SetSpeed(uint8_t speed) {
    if (speed > 100) speed = 100;  // 限制范围
    uint16_t pulse = (speed * 999) / 100;  // 计算占空比
    TIM_SetCompare1(FAN_PWM_TIM, pulse);   // 更新PWM占空比
}

// 设置风扇方向
void Fan_SetDirection(FanState direction) {
    switch (direction) {
        case FAN_FORWARD:
            GPIO_SetBits(FAN_GPIO_PORT, FAN_IN1_PIN);
            GPIO_ResetBits(FAN_GPIO_PORT, FAN_IN2_PIN);
            break;
        case FAN_REVERSE:
            GPIO_ResetBits(FAN_GPIO_PORT, FAN_IN1_PIN);
            GPIO_SetBits(FAN_GPIO_PORT, FAN_IN2_PIN);
            break;
        default:  // FAN_OFF
            GPIO_ResetBits(FAN_GPIO_PORT, FAN_IN1_PIN | FAN_IN2_PIN);
    }
}

// 紧急停止（立即关闭PWM和方向控制）
void Fan_EmergencyStop(void) {
    TIM_SetCompare1(FAN_PWM_TIM, 0);  // PWM占空比归零
    GPIO_ResetBits(FAN_GPIO_PORT, FAN_IN1_PIN | FAN_IN2_PIN);

}
