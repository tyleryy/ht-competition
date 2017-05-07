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
#include "key.h"
#include "ir.h"
#include "led.h"

//#define MAINDEBUG

#ifdef MAINDEBUG
#define main_debug(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#else
#define main_debug(fmt, ...)
#endif

//#define KEYDEBUG

#ifdef KEYDEBUG
#define key_debug(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#else
#define key_debug(fmt, ...)
#endif

//#define RFRDEBUG

#ifdef RFRDEBUG
#define rfr_debug(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#else
#define rfr_debug(fmt, ...)
#endif

typedef enum
{
	INIT, READY, START, OVER
} state_t;
int main(void)
{
	s16 signal1 = 0, signal2 = 0, attention1 = 0, attention2 = 0;
	state_t state = INIT;
	initialise_board();
	main_debug("INIT\r\n");
	//play_voice(GAME_START);
	while (1)
	{
		if (should_task_run(MAIN_LOOP))
		{
			signal1 = get_data(SIGNAL1);
			signal2 = get_data(SIGNAL2);
			attention1 = get_data(ATTENTION1);
			attention2 = get_data(ATTENTION2);
			if (signal1 != 0)
				attention1 = 0;
			if (signal2 != 0)
				attention2 = 0;
			set_led(signal1, signal2);

			if ((signal1 > 0) && (signal2 > 0))
			{

			}
			else if ((signal1 == 0) && (signal2 == 0))
			{
				if (state == READY)
				{
					state = START;
					play_voice(GAME_START);
				}

			}
			if (state == START)
			{

				send_value(attention1, attention2);
			}
			else
			{
				send_value(0, 0);
			}

			main_debug(
					"signal1:<%d>signal2:<%d>attention1:<%d>attention2:<%d>state:<%d>\r\n",
					signal1, signal2, attention1, attention2, state);

		}
		if (should_task_run(ADC_LOOP))
		{

			//main_debug("adc:%d \n", get_adc_raw_data());
		}
		if (should_task_run(CHECK_SIGNAL) && state == READY)
		{
			if (signal1 != 0 && signal2 != 0)
			{
				play_voice(POOR_SINGAL);
			}
		}
		if (should_task_run(SCAN_BTN))
		{
			if ((state == INIT) && (is_ready_pressed()))
			{
				state = READY;
			}
			if (is_ready_pressed() == 0)
			{
				state = INIT;
				reset_led_win1();
				reset_led_win2();
				stop_playing();

			}
			if (state != START && is_reset1_pressed())
			{
				send_value(99, 0);
			}
			if (state != START && is_reset2_pressed())
			{
				send_value(0, 99);
			}
		}
		if (should_task_run(REFEREE) && state == START)
		{
			u8 who = 0;
			who = who_win();
			switch (who)
			{
			case 1:
				rfr_debug("1win\r\n");
				state = OVER;
				play_voice(WIN_2);
				set_led_win1();
				break;
			case 2:
				rfr_debug("2win\r\n");
				state = OVER;
				play_voice(WIN_1);
				set_led_win2();
				break;
			default:
				//rfr_debug("retval is %d \r\n",who);
				break;
			}

		}

	}
}

