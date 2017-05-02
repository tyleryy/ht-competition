/**
 * \file:
 */
#ifndef __IR_H
#define	__IR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"
void ir_initialise(void);
u8 who_win(void);

#ifdef __cplusplus
}
#endif

#endif
