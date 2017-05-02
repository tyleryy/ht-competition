#include "schedule.h"
#include "systick/systick.h"

u16 cnt_1ms = 0, cnt_1s = 0;
u16 task_1s, task_1ms, task_30s, task_100ms,task_10ms;

void systime_updata(void)
{
	if (cnt_1ms < 999)
	{
		cnt_1ms++;
		task_1ms++;
		task_100ms++;
		task_10ms++;
	}
	else
	{
		cnt_1ms = 0;
		if (cnt_1s < 60)
		{
			cnt_1s++;
			task_1s++;
			task_30s++;
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
		if (task_1ms >= 1)
		{
			task_1ms = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	case CHECK_SIGNAL:
		if (task_30s >= 180)
		{
			task_30s = 0;
			return 1;
		}
		else
			return 0;
	case SCAN_BTN:
		if (task_100ms >= 100)
		{
			task_100ms = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	case REFEREE:
		if (task_10ms >= 1000)
		{
			task_10ms = 0;
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
