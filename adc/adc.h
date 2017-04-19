/**
 * \file:
 */
#ifndef __ADC_H
#define	__ADC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"

void initialise_adc(void);
u8 get_distance(void);

#ifdef __cplusplus
}
#endif

#endif
