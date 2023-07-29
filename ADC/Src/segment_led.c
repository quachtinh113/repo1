/* Includes ------------------------------------------------------------------*/
#include "segment_led.h"
#include "display.h"
#include "cmsis_os.h"
/* Private variables ---------------------------------------------------------*/
uint8_t LESs[6]={0x20,0x10,0x08,0x04,0x02,0x01};
uint8_t code_segment[23]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0x00,0x40,0x73};//0,1,...,8,9,0.,1., , 9.,_,-,P.
/**@fn out_segment_leds(uint8_t led[], PositionLedTypeDef pos)
 * @param  led: a array 3 elements these are 6 code segment for 3 LEDs, pos : position of LED ( left or right ).
 * @description
 * Out data for 3 7 segments LEDs.
 * @retval None.
 */
void out_segment_leds(uint8_t led[], PositionLedTypeDef pos){	
	for(uint8_t i=0;i<=2;i++){
		/* Disable display LEDs*/
		LIGTS_EN_HIGH(); 
		/* Out code 7 segments to LEDs*/		    
		transmiter_byte(&led[i]);  
		ALPHA_NUM_EN_LOW();
		ALPHA_NUM_EN_HIGH(); 	
		/* Select LED display*/	 
 		transmiter_byte(&LESs[i+3*pos]);
		LEDMUX_LOW();
		LEDMUX_HIGH(); 
		/* Enable display LEDs*/
		LIGTS_EN_LOW();
		vTaskDelay(1); 
	}
}
/**@fn display_7seg(uint16_t number, PositionLedTypeDef pos, quantityDef left_quantity).
* @param  number: a number [0,999] or [0.0, 99.9], pos : position of LED ( left or right ), quantity : display quantity.
 * @description
 * Display 3 7 segments LEDs.
 * @retval None.
 */
void display_7seg(uint16_t number, PositionLedTypeDef pos, quantityDef quantity){ 
	uint8_t LED[3];
	/*Load 'POP' for LEDs */
	if(quantity==ERROR_START){
		LED[2]=code_segment[22];
		LED[1]=code_segment[0];
		LED[0]=code_segment[22];
	}
	/*Off LEDs */
	else if(quantity==OFF_){
		LED[2]=code_segment[20];
		LED[1]=code_segment[20];
		LED[0]=code_segment[20];
	}
	
	/*Load number for LEDs */
	else if(quantity==TIME_){
		if(number<100){
			/* number in range[0.0 , 9.9]*/
			LED[2]=code_segment[20];
			LED[1]=code_segment[number/10+10];
			LED[0]=code_segment[number%10]; 
		}
		else if(number<999){
			/* number in range[10.0 , 99.9]*/
			LED[2]=code_segment[number/100];
			LED[1]=code_segment[(number%100)/10+10];
			LED[0]=code_segment[(number%100)%10];
		}
	}
		
	/*Load number current or voltage for LEDs */
	else if(quantity==CURRENT || quantity==VOLTAGE){
		if(number/100==0){
			/* number in range[0,9]*/
			if((number%100/10)==0){
				LED[2]=code_segment[20];
				LED[1]=code_segment[20];
				LED[0]=code_segment[number%100%10];  
			}
			/* number in range[10,99]*/
			else {
				LED[2]=code_segment[20];
				LED[1]=code_segment[number%100/10];
				LED[0]=code_segment[number%100%10];  
			}
		}
		/* number in range[100,999]*/
		else {
			LED[2]=code_segment[number/100];
			LED[1]=code_segment[number%100/10];
			LED[0]=code_segment[number%100%10];  	
		}
	}
	out_segment_leds(LED,pos);
}
