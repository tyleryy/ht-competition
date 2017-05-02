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
float get_distance(void);
u16 get_adc_raw_data(void);

#ifdef __cplusplus
}
#endif

#endif
