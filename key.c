
#include "key.h" 

#define KEY_ON	0
#define KEY_OFF	1

#define    COL_1_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    COL_1_GPIO_PORT    GPIOB
#define    COL_1_GPIO_PIN	  GPIO_Pin_14

#define    COL_2_GPIO_CLK     RCC_APB2Periph_GPIOB
#define    COL_2_GPIO_PORT    GPIOB
#define    COL_2_GPIO_PIN	  GPIO_Pin_15
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*���������˿ڣ�PB����ʱ��*/
	RCC_APB2PeriphClockCmd(COL_1_GPIO_CLK | COL_2_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = COL_1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	//ʹ�ýṹ���ʼ������
	GPIO_Init(COL_1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = COL_2_GPIO_PIN;

	GPIO_Init(COL_2_GPIO_PORT, &GPIO_InitStructure);

}

u8 is_ready_pressed(void)
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);
}