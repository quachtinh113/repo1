/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/* Private variables ---------------------------------------------------------*/
uint8_t counter_wait=0;
uint32_t counter_1ms=0;
uint32_t counter_10ms=0;
InputTypeDef previousTime;
uint16_t feedback_volt,feedback_current;
uint8_t previous_preset_current,preset_current;
uint16_t current_welding;
uint8_t previous_arc_force,arc_force;
float previous_post_gas,post_gas;
float previous_down_slope,down_slope;
float feedback_volt_remote_command;
bool wait_timeout_1s=FALSE;
float coefficient_remote;
bool arcForce=FALSE;
bool on_fan=FALSE;
bool start=FALSE;
bool Flag_OT=FALSE;
bool flagStatus=FALSE;
taskDef task=ADJUST;//////////////////////////////
adjustDef adjust=UNADJUST;
uint8_t left_value,right_value;
quantityDef left_quantity=VOLTAGE,right_quantity;
bool changedProcess=TRUE;
/*External variables---------------------------------------------------------*/
extern DAC_HandleTypeDef hdac;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern uint16_t adc_buffer[NUMBERS_CHANNEL_ADC];
extern uint16_t sample_adc_buffer[NUMBERS_CHANNEL_ADC];
extern uint16_t adc_buffer_previous[NUMBERS_CHANNEL_ADC];
extern uint16_t sample_times;
extern uint8_t time_pregas,time_up_slope,time_down_slope,time_post_gas;	;
extern bool Time_Out;
extern bool EnableWaitTimeOut;
extern uint16_t counter_wait_feedback_current;
extern bool Failed_Start;
extern positionDef position;
extern float increase,jump;
extern bool enableChangeMode;
extern uint8_t current;
extern uint8_t down_slope_current;
extern bool enablePregas;
extern bool cho_phep_dem_len_1S;
extern uint16_t dem_len_1S;
extern bool lon_hon_1S;
extern bool nho_hon_1S;
/**@fn process_inputs(void *pvParameters)
 * @description
 * Call functions of correspond inputs.
 * @retval Node.
 */
void process_inputs(void *pvParameters){
	InputTypeDef input;
	while(1){
		input=check_inputs();
		if(input==PROCESS && input!=previousTime && enableChangeMode==TRUE){
			sound_beep();
			if(position.process<NUMBER_PROCESS-1){
				position.process+=1; 
			}
			else{
				position.process=0;
				/*Process MMA turn off follow signals */
				HF_TIG_MCU_ON();
        PWM_ON_MCU_OFF();  
				MMA_LEFTTIG_VRD_MCU_OFF();  
			}
			changedProcess=TRUE;
			update_flash(basic_address,position,NUMBER_BYTES);
			clear_all_LEDs();
		}
		else if(input==MODE && input!=previousTime && enableChangeMode==TRUE && position.process!=0){
			sound_beep();
			HF_TIG_MCU_OFF();
			if(position.mode<NUMBER_MODE-1){
				position.mode+=1; 
			}
			else{
				position.mode=0;
			}
			update_flash(basic_address,position,NUMBER_BYTES);
			clear_all_LEDs();
		}
		/*Check request turn on/off fan*/
		if(check_request_fan()==ACTIVE && on_fan==FALSE){
			F_RUN_ON(); 
			on_fan=TRUE;
		}
		else if(check_request_fan()==UNACTIVE && on_fan==TRUE){
			F_RUN_OFF(); 
			on_fan=FALSE;
		}
		/*Check feedback current*/
		if(feedback_current>=_5A ){
			task=WELD;
		}
		else {
			task=ADJUST;
		}
		previousTime=input;
		vTaskDelay(1);
	}
}

/**@fn process_feedback_signals(void *pvParameters)
 * @description
 * Convert ADC feedback signals 
 * @retval Node.
 */
void process_feedback_signals(void *pvParameters){  
	while(1){ 
		/*Start convert ADC*/
	  HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adc_buffer, NUMBERS_CHANNEL_ADC);
		sample_adc_buffer[0]+=adc_buffer[0];
		sample_adc_buffer[1]+=adc_buffer[1];
		sample_adc_buffer[2]+=adc_buffer[2];
		sample_times+=1;
		/*Get average of simple feedback voltgate and current, after calculation of feedback voltgate and current*/
		if(sample_times>=SAMPLE_TIMES){
			/*Calculation of feedback voltgate, current, command mcu and remote command mcu*/
			feedback_volt=((((float)adc_buffer[0]+ AVERAGE_TOLERANCE)*3.3f)/4096)/0.02;//Feedback voltage in range 0->6.5V
			feedback_current=LESS_MIN_CURRENT+((((float)adc_buffer[1])*3.3f)/4096)/0.005;//Feedback current in range 0->2.5V
			feedback_volt_remote_command=(((float)adc_buffer[2])*3.3f)/4096;	
			/*Reset sampple_buffer*/
			sample_times=0;
			sample_adc_buffer[0]=0;
			sample_adc_buffer[1]=0;
			sample_adc_buffer[2]=0;	
			/*Check have connect remote*/
			if(feedback_volt_remote_command > MINIMUM_VOLTAGE_DETECT_REMOTE){
				coefficient_remote=feedback_volt_remote_command/2.0;  //Voltage remote into multiply circuit with ratio k=0.2 => 10V*k=2.0V 
			}
			else{
				coefficient_remote=1;
			}	
			/*Read adjust preset current*/
			preset_current=10+adc_buffer[3]/16.6;
			if(preset_current>250){
				preset_current=250;
			}
			if(preset_current<previous_preset_current-DIFFERRENCE || preset_current>previous_preset_current+DIFFERRENCE){
				#ifdef DEBUG
					send_message("Adjust preset current:");
					send_numbers(preset_current);				
				#endif	
				counter_1ms=0;
				adjust=ADJUST_CURRENT;
				wait_time_out();
				HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*preset_current);
			}
			previous_preset_current=preset_current;
			/*Read adjust arc force*/
			if(position.process==mma){
				arc_force=adc_buffer[4]/56.8;
				if(arc_force>70){
					arc_force=70;
				}
				if(arc_force<previous_arc_force-DIFFERRENCE || arc_force>previous_arc_force+DIFFERRENCE){
					#ifdef DEBUG
						send_message("Adjust arc force:");
						send_numbers(arc_force);		
					#endif
					counter_1ms=0;
					adjust=ADJUST_ARC_FORCE;
					wait_time_out();
				}
				previous_arc_force=arc_force;
			}
			/*Read adjust post gas*/
			else if(position.process==tig){
				post_gas=10+adc_buffer[5]/20;
				if(post_gas>200){
					post_gas=200;
				}
				if(post_gas<previous_post_gas-DIFFERRENCE || post_gas>previous_post_gas+DIFFERRENCE){
					#ifdef DEBUG
						send_message("Adjust post gas:");
						send_numbers(post_gas);	
					#endif
					counter_1ms=0;
					adjust=ADJUST_POST_GAS;
					wait_time_out();
				}
				previous_post_gas=post_gas;
			}
			/*Read adjust down slope*/
			if(position.process==tig){
				down_slope=adc_buffer[4]/40;
				if(down_slope>100){
					down_slope=100;
				}
				if(down_slope<previous_down_slope-DIFFERRENCE || down_slope>previous_down_slope+DIFFERRENCE){
					#ifdef DEBUG
						send_message("Adjust down slope:");
						send_numbers(down_slope);	
					#endif
					counter_1ms=0;
					adjust=ADJUST_DOWN_SLOPE;
					wait_time_out();
				}
				previous_down_slope=down_slope;
			}
		}
		vTaskDelay(20); 
	}
}
/**@fn process_display(void *pvParameters)
 * @description 
 * Display single LEDs and 7 segment LEDs.
 * @retval Node.
 */
void process_display(void *pvParameters){  
	while(1){ 
		clear_all_LEDs();
		if(feedback_current>=_5A && check_OT()==UNACTIVE && check_current_on()==ACTIVE){
			switch_led(CURRENT_OUT,ON_LED); 
		}
		if(check_OT()==ACTIVE){
			left_quantity=OFF_;
			right_quantity=OFF_;
			switch_led(WARNING,ON_LED); 
			if(Flag_OT==FALSE){
				Flag_OT=TRUE;
				BUZZER_ON();
			}
		}
		else {
			if(Flag_OT==TRUE){
				Flag_OT=FALSE;
				BUZZER_OFF();
			}
			if((task==WELD && check_current_on()==ACTIVE) || (task!=WELD && Failed_Start==TRUE && check_current_on()==ACTIVE)){
				if(flagStatus==TRUE){
					flagStatus=FALSE;
				}
				if(Failed_Start==FALSE){
					left_quantity=VOLTAGE;
					right_quantity=CURRENT;
					switch_led(V,ON_LED);
					switch_led(A,ON_LED);  
				}
				else {
					left_quantity=ERROR_START;
					right_quantity=ERROR_START;
					switch_led(V,OFF_LED);
					switch_led(A,OFF_LED);
				}
				left_value=feedback_volt;
				right_value=feedback_current;
			}
			else if(task==ADJUST){
				if(flagStatus==FALSE){
					flagStatus=TRUE;
					right_value=preset_current;
				}
				left_quantity=OFF_;
				switch_led(V,OFF_LED);
				if(adjust==ADJUST_CURRENT){
					right_value=preset_current;
					right_quantity=CURRENT;
					switch_led(A,ON_LED);
				}
				else if(adjust==ADJUST_ARC_FORCE){
					right_value=arc_force;
					right_quantity=CURRENT;
					switch_led(A,ON_LED);
				}
				else if(adjust==ADJUST_POST_GAS){
					right_value=post_gas;
					right_quantity=TIME_;
					switch_led(S,ON_LED);
				}
				else if(adjust==ADJUST_DOWN_SLOPE){
					right_value=down_slope;
					right_quantity=TIME_;
					switch_led(S,ON_LED);
				}	
			}
			leds_button(position);
		}
		display_7seg(left_value,_LEFT,left_quantity);
		display_7seg(right_value,_RIGHT,right_quantity);	
		vTaskDelay(1);
	}
}
/**@fn process_timer_1ms(void *pvParameters)
 * @description
 * Increase counter after 1 minisecond.
 * @retval Node.
 */
void process_timer_1ms(void *pvParameters){
	while(1){
		if(wait_timeout_1s==TRUE){
			counter_1ms+=1;
			if(counter_1ms>_4SECOND || start==FALSE){
				if(start==FALSE){
					start=TRUE;
				}
				adjust=UNADJUST;
				counter_1ms=0;
				wait_timeout_1s=FALSE;
			}
		}
	
		/*Counter wait 100MS check point on bencmark choose.*/
		counter_wait+=1;
		if(counter_wait>=_100MS){
			counter_wait=0;
			if(time_pregas>0){
				time_pregas-=1;
				if(check_OT()==ACTIVE){
					time_pregas=0;
				}
			}
			if(time_down_slope>0){
				time_down_slope-=1;
				if(check_OT()==ACTIVE){
					time_down_slope=0;
				}
				increase+=jump; 
				
				if(position.mode==_2T_){
					HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*(down_slope_current-(uint16_t)increase));
				}
				else if(position.mode==_4T_){
					if(preset_current>=MINIMUM_CURRENT){
						current=preset_current-(uint16_t)increase;
					}
					else {
						current=preset_current+(uint16_t)increase;
					}
					HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*(current));
				}
			}
			
			if(time_post_gas>0){
				time_post_gas-=1;
				if(check_OT()==ACTIVE){
					time_post_gas=0;
				}
			}
		}
		if(EnableWaitTimeOut==TRUE){
			counter_wait_feedback_current+=1;   
			if(counter_wait_feedback_current>=_2S){
				counter_wait_feedback_current=0;
				EnableWaitTimeOut=FALSE;
		    Time_Out=TRUE;
			}
		}
		if(cho_phep_dem_len_1S==TRUE){
			dem_len_1S++;
		if(dem_len_1S>=1000){
			cho_phep_dem_len_1S=FALSE;
			dem_len_1S=0;
			nho_hon_1S=TRUE;
			}
		else{
			lon_hon_1S=FALSE;
		}
		}
		vTaskDelay(5);
	}
}
/**@fn wait_time_out(void).
 * @description
 * Enable wait timeout.
 * @retval Node.
 */
static void wait_time_out(void){
	task=ADJUST;
	wait_timeout_1s=TRUE;
	counter_1ms=0;
}
/**@fn process_welding(void *pvParameters)
 * @description
 * Call functions of process welding switch .
 * @retval Node.
 */ 
void process_welding(void *pvParameters){
	while(1){
		/*Welding MMA*/
		if(position.process==mma){
			if(changedProcess==TRUE){
				changedProcess=FALSE;
				HF_TIG_MCU_OFF(); 
			  ARCSTART_OFF();
			  PWM_ON_MCU_ON();
			}
			if(check_OT()==ACTIVE){
				turn_off_weld();
			}
			else {
				if(feedback_current<_5A){
					if(check_current_on()==ACTIVE){
						current_welding = HOT_START_MMA;
					}
				}
				else {
					if(check_arc_force()==ACTIVE && arcForce==FALSE){
						arcForce=TRUE;
						current_welding=preset_current+arc_force;		
					}
					else if(check_arc_force()==UNACTIVE){
						if(arcForce==TRUE){
							arcForce=FALSE;
						}
						current_welding=preset_current;
					}
				}
				HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*current_welding);
			}
		}
		/*Welding TIG*/
		else if(position.process==tig){
			if(changedProcess==TRUE){
				changedProcess=FALSE;
				ARCSTART_OFF();
			  	PWM_ON_MCU_OFF();
			}
			turn_off_weld();
			/*Mode 2T*/
			if(position.mode==_2T_){
				process_2T();
			}
			/*Mode 4T*/
			else if(position.mode==_4T_){
				process_4T();
			}
		}
	}
}
/**@fn turn_off_weld(void).
 * @description
 * Turn off weld
 * @retval Node.
 */ 
static void turn_off_weld(void){
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*0);
}
