#include"nvic.h"

void initialise_nvic_group(void)
{
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
}
