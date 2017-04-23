/**
 * \file:
 */
#ifndef __ANO_PROTOCOL_H
#define	__ANO_PROTOCOL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"
void send_data_to_ano(float raw,float distance,float output);

#ifdef __cplusplus
}
#endif

#endif
