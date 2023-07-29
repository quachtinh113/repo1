/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "timers_rtos.h"

/** @fn uint8_t times_1ms(void).
 * @description 
 * Check enable save counter encoder.
 * @retval SAVE if enable counter encoder and NONE.
 */
uint8_t times_1ms(void){
	if(Enable_timer_1ms==TRUE){
		counter_1ms+=1;
		/* After this time will save counter encoder.*/
		if(counter_1ms>TIMEOUT){ 
			counter_1ms=0;
			Enable_timer_1ms=FALSE;
			return SAVE;
		}
	}
	return NONE;
}
