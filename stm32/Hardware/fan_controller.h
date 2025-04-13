#ifndef __FAN_CONTROLLER_H
#define __FAN_CONTROLLER_H

#include "stm32f10x.h"

// 风扇状态枚举
typedef enum {
    FAN_OFF = 0,
    FAN_FORWARD,
    FAN_REVERSE
} FanState;

// 初始化函数
void Fan_Init(void);

// 控制函数
void Fan_SetSpeed(uint8_t speed);  // 0-100%
void Fan_SetDirection(FanState direction);
void Fan_EmergencyStop(void);

#endif
