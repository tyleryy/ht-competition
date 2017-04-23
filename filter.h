/**
 * \file:
 */
#ifndef __FILTER_H
#define	__FILTER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"

float moving_median(u8 item,u8 width_num,float in);

#ifdef __cplusplus
}
#endif

#endif
