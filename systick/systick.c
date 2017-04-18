#include "systick.h"

#define TICK_PER_SECOND 1000
#define TICK_US	(1000000/TICK_PER_SECOND)

u8 systime_cnt = 0;
void initialise_systick(void)
{
	RCC_ClocksTypeDef rcc_clocks;
	uint32_t cnts;

	RCC_GetClocksFreq(&rcc_clocks);

	cnts = (uint32_t) rcc_clocks.HCLK_Frequency / TICK_PER_SECOND;
	cnts = cnts / 8;

	SysTick_Config(cnts);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}
u32 get_systime_us(void)
{
	register uint32_t ms;
	u32 value;
	ms = systime_cnt;
	value = ms * TICK_US
			+ (SysTick->LOAD - SysTick->VAL) * TICK_US / SysTick->LOAD;
	return value;
}

void SysTick_Handler(void)
{
	systime_cnt++;
	systime_updata();
}
