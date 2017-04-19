/**
 * \file:
 */
#ifndef __SCHEDULE_H
#define	__SCHEDULE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"

typedef enum
{
	MAIN_LOOP, LED_LOOP, ADC_LOOP
} task_t;

s8 should_task_run(task_t task);
void systime_updata(void);

#ifdef __cplusplus
}
#endif

#endif
