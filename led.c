#include "led.h"
#include "datalink.h"

#define    LED_GPIO_CLK     	RCC_APB2Periph_GPIOC
#define    LED_GPIO_PORT   		GPIOC
#define    LED_GPIO_PIN_1	  	GPIO_Pin_2
#define    LED_GPIO_PIN_2	  	GPIO_Pin_3
#define    LED_GPIO_PIN_3	  	GPIO_Pin_4
#define    LED_GPIO_PIN_4	  	GPIO_Pin_5

#define    WINLED_GPIO_CLK     	RCC_APB2Periph_GPIOB
#define    WINLED_GPIO_PORT   		GPIOB
#define    WINLED_GPIO_PIN_1	  	GPIO_Pin_0
#define    WINLED_GPIO_PIN_2	  	GPIO_Pin_1

//#define    LED_GPIO_PIN_5	  	GPIO_Pin_6
//#define    LED_GPIO_PIN_6	  	GPIO_Pin_7
//#define    LED_GPIO_PIN_7	  	GPIO_Pin_8
//#define    LED_GPIO_PIN_8	  	GPIO_Pin_9
//#define    IR_GPIO_PIN_1	  	GPIO_Pin_14
//#define    IR_GPIO_PIN_2	  	GPIO_Pin_25
static void led_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启按键端口（PB）的时钟*/
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK|WINLED_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN_1 | LED_GPIO_PIN_2
			| LED_GPIO_PIN_3 | LED_GPIO_PIN_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//使用结构体初始化按键
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = WINLED_GPIO_PIN_1 | WINLED_GPIO_PIN_2;
	GPIO_Init(WINLED_GPIO_PORT, &GPIO_InitStructure);
}
void initialise_led_gpio(void)
{
	led_gpio_config();
	GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_1);
	GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_2);
	GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_3);
	GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_4);


}
void set_led(s16 signal1, s16 signal2)
{
	s16 temp = 0;
	temp = signal1;
	//0
	if ((temp == -1) || (temp == 200))
	{
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_1);
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_2);
	}
	//0
	else if (25 * 3 <= temp && temp <= 29 * 3)
	{
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_1);
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_2);
	}
	//1
	else if (25 * 2 <= temp && temp <= 29 * 2)
	{
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN_1);
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_2);


	}
	//2
	else if (25 * 1 <= temp && temp <= 29 * 1)
	{
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_1);
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN_2);


	}
	//3
	else if (temp == 0)
	{
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN_1);
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN_2);

	}

	temp = signal2;
	//0
	if ((temp == -1) || (temp == 200))
	{
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_3);
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_4);
	}
	//0
	else if (25 * 3 <= temp && temp <= 29 * 3)
	{
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_3);
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_4);
	}
	//1
	else if (25 * 2 <= temp && temp <= 29 * 2)
	{
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN_3);
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_4);


	}
	//2
	else if (25 * 1 <= temp && temp <= 29 * 1)
	{
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN_3);
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN_4);


	}
	//3
	else if (temp == 0)
	{
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN_3);
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN_4);

	}

}
void set_led_win1(void)
{
	GPIO_SetBits(WINLED_GPIO_PORT, WINLED_GPIO_PIN_1);
}
void set_led_win2(void)
{
	GPIO_SetBits(WINLED_GPIO_PORT, WINLED_GPIO_PIN_2);
}
void reset_led_win1(void)
{
	GPIO_ResetBits(WINLED_GPIO_PORT, WINLED_GPIO_PIN_1);
}
void reset_led_win2(void)
{
	GPIO_ResetBits(WINLED_GPIO_PORT, WINLED_GPIO_PIN_2);
}
