#include "ir.h"

#define    IR_GPIO_CLK     RCC_APB2Periph_GPIOC
#define    IR_GPIO_PORT    GPIOC
#define    IR_GPIO_PIN1	   GPIO_Pin_14
#define    IR_GPIO_PIN2	   GPIO_Pin_15

void ir_initialise(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启按键端口（PB）的时钟*/
	RCC_APB2PeriphClockCmd(IR_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = IR_GPIO_PIN1 | IR_GPIO_PIN2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(IR_GPIO_PORT, &GPIO_InitStructure);

}
u8 who_win(void)
{
	if(GPIO_ReadInputDataBit(IR_GPIO_PORT, IR_GPIO_PIN1) == 1
			&& GPIO_ReadInputDataBit(IR_GPIO_PORT, IR_GPIO_PIN2) == 1)
	{
		return 0;
	}
	else if (GPIO_ReadInputDataBit(IR_GPIO_PORT, IR_GPIO_PIN1) == 0
			&& GPIO_ReadInputDataBit(IR_GPIO_PORT, IR_GPIO_PIN2) == 1)
	{
		return 1;
	}
	else if(GPIO_ReadInputDataBit(IR_GPIO_PORT, IR_GPIO_PIN1) == 1
			&& GPIO_ReadInputDataBit(IR_GPIO_PORT, IR_GPIO_PIN2) == 0)
	{
		return 2;
	}
	else
	{
		return 3;
	}

}
