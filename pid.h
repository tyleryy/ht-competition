
/**
 * \file:
 */
#ifndef __PID_H
#define	__PID_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"

typedef struct
{
	float p;
	float i;
	float d;
	float error;
	float pre_error;
	float deriv;
	float integ;
	float output;

} pid_s;

void pid_cal(pid_s *pid, float target, float measure, u32 dert_t);

#ifdef __cplusplus
}
#endif

#endif

