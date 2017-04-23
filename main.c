#include "usart.h"
#include "playvoice.h"
#include "init.h"
#include "datalink/datalink.h"
#include "stdio.h"
#include "schedule/schedule.h"
#include "adc/adc.h"
#include "ano_protocol.h"
#include "filter.h"
#include "pid.h"

//#define MAINDEBUG

#ifdef MAINDEBUG
#define main_debug(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#else
#define main_debug(fmt, ...)
#endif


int main(void)
{
	initialise_board();
	s16 signal1 = 0, signal2 = 0, attention1 = 0, attention2 = 0;
	float distance,distance_raw;
	pid_s pid;
	pid.p=0.35;
	pid.d=0;

	main_debug("start");
	while (1)
	{
		if (should_task_run(MAIN_LOOP))
		{
			signal1 = get_data(SIGNAL1);
			signal2 = get_data(SIGNAL2);
			attention1 = 0;
			attention2 = 0;
			if ((signal1 > 0) && (signal2 > 0))
			{
				play_voice(POOR_SINGAL);
			}
			else if ((signal1 == 0) && (signal2 == 0))
			{
				play_voice(GAME_START);
				attention1 = get_data(ATTENTION1);
				attention2 = get_data(ATTENTION2);
			}
			send_value(attention1, attention2);

			main_debug(
					"signal1:<%d>signal2:<%d>attention1:<%d>attention2:<%d>\n",
					signal1, signal2, attention1, attention2);


		}
		if(should_task_run(ADC_LOOP))
		{
			static u8 i=0;
			i++;
			//main_debug("adc:%d \n",get_distance());
			distance_raw=get_distance();
			distance=moving_median(1,5,distance_raw);

			if (i>=10)
			{
				i=0;
				pid_cal(&pid,60,distance,1);
				send_value((u8)(20-pid.output),(u8)(20+pid.output));
				send_data_to_ano(distance_raw,distance,pid.output);
			}

		}


	}
}

