#ifndef __KEY_H
#define	__KEY_H

#include "stm32f10x.h"


void Key_GPIO_Config(void);
u8 is_ready_pressed(void);
u8 is_reset1_pressed(void);
u8 is_reset2_pressed(void);
#endif

