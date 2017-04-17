#include "playvoice.h"
#include"usart.h"

enum
{
	TENS_DIGIT = 6, UNITS_DIGIT

};
void play_voice(voice_name voice)
{
	u8 data_buffer[] =
	{ 0x7e, 0x06, 0xa0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x7e };

	if (voice < 10)
	{
		data_buffer[UNITS_DIGIT] = 0x30 + voice;

	}
	usart_send_array(USART1, data_buffer, 9);

}
