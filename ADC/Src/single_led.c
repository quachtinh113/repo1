/* Includes */
#include "main.h"
#include "display.h"
#include "single_led.h"
/*Private  variables---------------------------------------------------------*/
uint8_t LED=0x00;
/**@fn void switch_led(LedTypeDef led, SwitchLedTypeDef state)
@param  led: name of LED, state: bit state of LED ( ON or OFF ).
 * @description
 * On or off a LED.
 * @retval None.
 */
void switch_led(LedTypeDef led, SwitchLedTypeDef state){
	/* Set state for LED */
	if(state==ON_LED){
		LED|=(1<<led);
	}
	else {
		LED&=~(1<<led);
	}
	/*Transmiter 8 bit state of LEDs*/
	transmiter_buffer(LED);
  /* Out bit state of LED*/
	LED_LE_A_LOW();
	LED_LE_A_HIGH();
	if(led==CURRENT_OUT){
		if(state==ON_LED){
			CURRENT_OUT_ON();
		}
		else {
			CURRENT_OUT_OFF();
		}
	}
}
