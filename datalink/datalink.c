#include "stream_parser/StreamParser.h"
#include "usart/usart.h"
#include "datalink.h"

enum
{
	VAL1 = 2, VAL2
};

ThinkGearStreamParser parser1;
ThinkGearStreamParser parser2;

void initialise_think_data(void)
{
	THINKGEAR_initParser(&parser1, PARSER_TYPE_PACKETS);
	THINKGEAR_initParser(&parser2, PARSER_TYPE_PACKETS);
}

/**
 * Get the data selected.
 * \param: select a data.
 * \retval: -1 data not ready.-2 the param is invalid.
 */
s16 get_data(data_t data)
{
	switch (data)
	{
	case SIGNAL1:
		if (parser1.signalrdy)
		{
			parser1.signalrdy = 0;
			return parser1.signal;
		}
		else
			return -1;

	case SIGNAL2:
		if (parser2.signalrdy)
		{
			parser2.signalrdy = 0;
			return parser2.signal;
		}
		else
			return -1;
	case ATTENTION1:
		if (parser1.attentionrdy)
		{
			parser1.attentionrdy = 0;
			return parser1.attention;
		}
		else
			return -1;
	case ATTENTION2:
		if (parser2.attentionrdy)
		{
			parser2.attentionrdy = 0;
			return parser2.attention;
		}
		else
			return -1;

	default:
		return -2;
	}
}

u8 send_value(u8 val1, u8 val2)
{
	u8 data_buff[] =
	{ 0xaa, 0xaa, 0, 0, 0xaf };
	data_buff[VAL1] = val1;
	data_buff[VAL2] = val2;
	usart_send_array(UART4,data_buff,5);

}

void USART2_IRQHandler(void)
{
	uint8_t ch;

	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		ch = USART_ReceiveData(USART2);
		THINKGEAR_parseByte(&parser1, ch);
	}

}

void USART3_IRQHandler(void)
{
	uint8_t ch;

	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		ch = USART_ReceiveData(USART3);
		THINKGEAR_parseByte(&parser2, ch);
	}

}
void UART4_IRQHandler(void)
{
	uint8_t ch;

	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		ch = USART_ReceiveData(UART4);
		/*		usart_send_byte(UART4, ch);*/
	}

}
