#include "key.h" 

#define KEY_ON	0
#define KEY_OFF	1

#define    COL_1_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    COL_1_GPIO_PORT    GPIOB
#define    COL_1_GPIO_PIN	  GPIO_Pin_14

#define    COL_2_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    COL_2_GPIO_PORT    GPIOB
#define    COL_2_GPIO_PIN	  GPIO_Pin_15

#define		RESET2_BTN_PIN	 GPIO_Pin_16
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启按键端口（PB）的时钟*/
	RCC_APB2PeriphClockCmd(COL_1_GPIO_CLK | COL_2_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//设置按键的引脚为上拉输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	//使用结构体初始化按键
	GPIO_Init(COL_1_GPIO_PORT, &GPIO_InitStructure);


}

u8 is_ready_pressed(void)
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);
}
u8 is_reset1_pressed(void)
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}
u8 is_reset2_pressed(void)
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15);
}
