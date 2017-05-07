/**
 * \file:
 */
#ifndef __LED_H
#define	__LED_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"

void initialise_led_gpio(void);
void set_led(s16 signal1,s16 signal2);
void set_led_win1(void);
void set_led_win2(void);
void reset_led_win1(void);
void reset_led_win2(void);

#ifdef __cplusplus
}
#endif

#endif
