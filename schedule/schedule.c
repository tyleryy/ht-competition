#include "schedule.h"
#include "systick/systick.h"

u16 cnt_1ms = 0, cnt_1s = 0;
u16 task_1s, task_1ms;

void systime_updata(void)
{
	if (cnt_1ms < 999)
	{
		cnt_1ms++;
		task_1ms++;
	}
	else
	{
		cnt_1ms = 0;
		if (cnt_1s < 60)
		{
			cnt_1s++;
			task_1s++;
		}
		else
		{
			cnt_1s = 0;
		}
	}
}

s8 should_task_run(task_t task)
{
	switch (task)
	{
	case MAIN_LOOP:
		if (task_1s >= 1)
		{
			task_1s = 0;
			return 1;
		}
		else
		{
			return 0;
		}

	case ADC_LOOP:
		if (task_1ms >= 100)
		{
			task_1ms = 0;
			return 1;
		}
		else
		{
			return 0;
		}

	default:
		return -1;

	}

}
