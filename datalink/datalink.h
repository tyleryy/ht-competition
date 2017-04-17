/**
 * \file:
 */
#ifndef __DATALINK_H
#define	__DATALINK_H

typedef enum
{
	SIGNAL1, SIGNAL2, ATTENTION1, ATTENTION2
} data_t;
void initialise_think_data(void);
s16 get_data(data_t data);
u8 send_value(u8 val1, u8 val2);
#endif
