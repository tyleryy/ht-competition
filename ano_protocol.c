#include "ano_protocol.h"
#include "usart/usart.h"

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )


void send_data_to_ano(float raw,float distance,float output)
{
	u8 data_to_send[50];
	u8 _cnt=0,sum = 0;

	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xF1;
	data_to_send[_cnt++]=0;

	data_to_send[_cnt++]=BYTE3(raw);
	data_to_send[_cnt++]=BYTE2(raw);
	data_to_send[_cnt++]=BYTE1(raw);
	data_to_send[_cnt++]=BYTE0(raw);

	data_to_send[_cnt++]=BYTE3(distance);
	data_to_send[_cnt++]=BYTE2(distance);
	data_to_send[_cnt++]=BYTE1(distance);
	data_to_send[_cnt++]=BYTE0(distance);

	data_to_send[_cnt++]=BYTE3(output);
	data_to_send[_cnt++]=BYTE2(output);
	data_to_send[_cnt++]=BYTE1(output);
	data_to_send[_cnt++]=BYTE0(output);


	data_to_send[3] = _cnt-4;


	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;

	usart_send_array(UART5,data_to_send, _cnt);
}

