#include "init.h"
#include "usart.h"
#include "stm32f10x.h"
#include "misc.h"
#include "datalink/datalink.h"
#include "systick/systick.h"

void initialise_board()
{
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/*initialise usarts*/
	initialise_usart1(9600); /**<use for WT9501*/
	initialise_usart2(57600); /**<use for bluetooth*/
	initialise_usart3(57600); /**<use for bluetooth*/
	initialise_uart4(115200); /**<use for telecommute*/
	initialise_uart5(115200);
	initialise_systick();
	initialise_think_data();

}
