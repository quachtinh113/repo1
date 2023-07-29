/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/*Private variables ---------------------------------------------------------*/
float increase;
float jump;
uint8_t time_pregas;
uint8_t time_up_slope;
uint8_t time_down_slope;
uint8_t time_post_gas;
bool Time_Out=FALSE;
bool EnableWaitTimeOut=FALSE;
bool Failed_Start=FALSE;
uint16_t counter_wait_feedback_current=0;
bool enableChangeMode=TRUE;
uint8_t current;
uint16_t dem_len_1S=0;
bool Released=FALSE;
uint8_t down_slope_current;
initialTypeDef check;
bool InitialFail=FALSE;
bool enablePregas=TRUE;
bool enableDelay=FALSE;
bool cho_phep_dem_len_1S=FALSE;
bool lon_hon_1S=FALSE;
bool nho_hon_1S=FALSE;
/*External variables ---------------------------------------------------------*/
extern DAC_HandleTypeDef hdac;
extern uint16_t feedback_volt,feedback_current;
extern uint8_t preset_current;
extern float post_gas;
extern float down_slope;
extern quantityDef left_quantity,right_quantity;
/**@fn Delay(uint32_t time).
* @param time : time delay.
 * @description 
 * Function delay.
 * @retval None.
 */
static void Delay(uint32_t time){
	uint32_t t;
	for(t=time;t>0;t--){
	}
}
/**@fn restore_state(void).
 * @param None.
 * @description 
 * Restore state process and mode.
 * @retval position of process and mode.
 */
positionDef restore_state(void){
	positionDef position;
	position.process=flash_read(address_process);
	position.mode=flash_read(address_mode);
	return position;
}
/**@fn process_2T(void).
 * @param None.
 * @description 
 * Function process 2T.
 * @retval None.
 */
void process_2T(void){
	START:    
	if(check_trigger()==ACTIVE && check_OT()==UNACTIVE){
		enableChangeMode=FALSE;
		/*Turn on gas valve*/
		GAS_OUTPUT_EN_ON();
		/*Enable pregas*/
		if(enablePregas==TRUE){
			#ifdef DEBUG
				send_message("Pregas----");
			#endif 
			/*Set time pregas 500 minisecond*/
			time_pregas=PREGAS_TIME;
			enablePregas=FALSE;
			while(time_pregas>0){
				Delay(1);
				if(check_trigger()==UNACTIVE){
					goto POST_GAS;
				}
				Delay(1);
			}
		}
		/*Yet active current_on then wait active current_on in 2s*/
		if(check_current_on()!=ACTIVE){
			check=wait_current_on();
			if(check==FAIL || check==BREAK){
				if(check==FAIL){
					InitialFail=TRUE;
				}
				goto POST_GAS;                       
			}
		}
		time_up_slope=UP_SLOPE;
		if(time_up_slope>0){
			increase=0;
			jump=(float)(	preset_current-10)/time_up_slope;
	
			while(time_up_slope>0){
				if(check_trigger()==UNACTIVE){
					Released=TRUE;
					time_up_slope=0;
					goto DOWN_SLOPE;
				}
				check=check_currentON(UNACTIVE);
				if(check==FAIL){
					goto START;
				}
			}
		}
		WELDING:
		#ifdef DEBUG
			send_message("----welding");
    	#endif
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*(preset_current));
		EnableWaitTimeOut=FALSE;
		while(check_trigger()==ACTIVE){
			Delay(1);
			if(check_trigger()==UNACTIVE){
				goto DOWN_SLOPE;
			}
			check=check_currentON(ACTIVE);
			if(check==FAIL){
				goto POST_GAS;
			}
		}
		DOWN_SLOPE:
		/*Load time down slope*/
		time_down_slope=down_slope;
		#ifdef DEBUG
			send_message("----down slope");
    #endif
		increase=0;                                                      
		if(check_trigger()==UNACTIVE){
			down_slope_current=preset_current;
			if(time_down_slope>0){
			jump=((float)(preset_current-10)/(time_down_slope));
			}
			else{
				jump=0;
			}
		}
		EnableWaitTimeOut=FALSE;
		while(time_down_slope>0){
			Delay(1);
			if(check_trigger()==ACTIVE){
				time_down_slope=0;
				goto WELDING;
			}
			check=check_currentON(UNACTIVE);
			if(check==FAIL){
				goto POST_GAS;
			}
		}
		/*Turn off PWM*/
		//turn_off_weld();
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*OFF_CURRENT);
		PWM_ON_MCU_OFF(); 
		POST_GAS:
		enableChangeMode=TRUE;
		time_post_gas=post_gas;
		#ifdef DEBUG
			send_message("----post gas");
    #endif
		while(time_post_gas>0){
			Delay(1);
			if(check_trigger()==ACTIVE  && InitialFail==FALSE){
				time_post_gas=0;
				goto START;
			}
			if(check_trigger()==UNACTIVE && InitialFail==TRUE){
				while(check_trigger()==UNACTIVE && time_post_gas>0){
					Delay(1);
				}
				goto END;
			}
		}
		END:
		#ifdef DEBUG
			send_message("----turn off gas valve");
    #endif
    /*Enable pregas flag */
		enablePregas=TRUE;
		GAS_OUTPUT_EN_OFF(); 
		/*Turn off HF and ARCSTART*/
	  HF_TIG_MCU_OFF();  
	  ARCSTART_OFF();   
		InitialFail=FALSE;	
		#ifdef DEBUG
			send_message("----end process\r\n");
    #endif
		}
	}

/**@fn process_4T(void).
 * @param None.
 * @description 
 * Function process 4T. 
 * @retval None.
 */
void process_4T(void){
	START:
	if(check_trigger()==ACTIVE && check_OT()==UNACTIVE){
		enableChangeMode=FALSE;
		/*Turn on gas valve*/
		GAS_OUTPUT_EN_ON();	
		/*Enable pregass*/
		if(enablePregas==TRUE){
			#ifdef DEBUG
				send_message("Pregas");
			#endif 
			/*Set time pregas 500 minisecond*/
			time_pregas=PREGAS_TIME;
			enablePregas=FALSE;
			while(time_pregas>0){
				Delay(1);
				if(check_trigger()==UNACTIVE){
					goto POST_GAS;
				}
			}
		}
	  /*Yet active current_on then wait active current_on in 2s*/
		if(check_current_on()!=ACTIVE){
			check=wait_current_on();
			if(check==FAIL || check==BREAK){
				if(check==FAIL){
					InitialFail=TRUE;
				}
				goto POST_GAS;                       
			}
		}		
		/*Load initial current from memory*/
		#ifdef DEBUG
			send_message("----initialize current");
    #endif
		HAL_Delay(200);
		/*Set initial current*/
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*INITIAL_CURRENT);
		
		EnableWaitTimeOut=FALSE;
		
		while(check_trigger()==ACTIVE){
			Delay(1);
			check=check_currentON(UNACTIVE);
			if(check==FAIL){
				goto POST_GAS;
			}
		}
		cho_phep_dem_len_1S=TRUE;
		if(check_trigger()==UNACTIVE){
			if(nho_hon_1S==TRUE){
				
				goto 	WELDING;
			}
			else	{
				goto POST_GAS;
				HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*(0));
			}
		}
		WELDING:
		#ifdef DEBUG
			send_message("----welding");
    #endif
		
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*(preset_current));
		EnableWaitTimeOut=FALSE;
		
		while(nho_hon_1S==TRUE){
		while(check_trigger()==UNACTIVE){
			check=check_currentON(UNACTIVE);
			if(check==FAIL){
				goto START;
				
			}
		}
	}
		while(check_trigger()==ACTIVE){
					if(check_trigger()==UNACTIVE){
					goto POST_GAS;
				}
			}
	
			DOWN_SLOPE:
		/*Load time down slope*/
		time_down_slope=down_slope;	
		#ifdef DEBUG
			send_message("----down slope");
    #endif
		increase=0;
		/*Crater current 30A*/
		if(preset_current>=CRATER_CURRENT){
			jump=((float)(preset_current-CRATER_CURRENT))/(time_down_slope);
		}
		else {
			jump=((float)(CRATER_CURRENT-preset_current))/(time_down_slope);
		}
		EnableWaitTimeOut=FALSE;
		while(time_down_slope>0){
			Delay(1);
			check=check_currentON(ACTIVE);
			if(check==FAIL){
				goto POST_GAS;
			}
			if(check_trigger()==UNACTIVE){
				time_down_slope=0;
				goto WELDING;
			}
		}
		/*Set Crater current*/
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*CRATER_CURRENT);
		#ifdef DEBUG
			send_message("----crater current");
    #endif
		EnableWaitTimeOut=FALSE;
		while(check_trigger()==ACTIVE){ 
			Delay(1);
			check=check_currentON(ACTIVE);
			if(check==FAIL){
				goto END;
			}
		}
		/*Turn off PWM*/
		PWM_ON_MCU_OFF(); 
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*OFF_CURRENT);
		POST_GAS:
		/*Load time post gas*/
		time_post_gas=post_gas;
		enableChangeMode=TRUE; 
		#ifdef DEBUG
			send_message("----post gas");
    #endif
		while(time_post_gas>0){
			Delay(1);
			if(check_trigger()==ACTIVE && InitialFail==FALSE){
				time_post_gas=0; 
				goto START;
			}
			if(check_trigger()==UNACTIVE && InitialFail==TRUE){
				while(check_trigger()==UNACTIVE && time_post_gas>0){
					Delay(1);
				}
				goto END;
			}
		}
		END:
		#ifdef DEBUG
			send_message("----turn off gas valve");
    #endif
    /*Enable pregas flag */
		enablePregas=TRUE;
		GAS_OUTPUT_EN_OFF();
		/*Turn off HF and ARCSTART*/
  	HF_TIG_MCU_OFF();  
	  ARCSTART_OFF();   
		InitialFail=FALSE;
		#ifdef DEBUG
			send_message("----end process\r\n");
		#endif
	}
}
/**@fn wait_current_on(void).
 * @param None.
 * @description 
 * Wait current on if after 2 seconds not current on will message error.
 * @retval BREAK, FAIL or OK.
 */
static initialTypeDef wait_current_on(void){
	/*Toggle hot start current*/
	#ifdef DEBUG
		send_message("----hot start current");
	#endif
	/*Set hotstart*/
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*50);
  /*Turn on HF, PWM and ARCSTART*/
	HF_TIG_MCU_ON();  
	PWM_ON_MCU_ON();   
	ARCSTART_ON();
	EnableWaitTimeOut=TRUE;
	counter_wait_feedback_current=0;
	Time_Out=FALSE;
	while(check_current_on()==UNACTIVE){
		/*Only into this block when more than 2 seconds current_on still off */
		if(Time_Out==TRUE){
			Time_Out=FALSE;
			/*Turn off gas valve, PWM ,HF and ARCSTART*/
			GAS_OUTPUT_EN_OFF();
			ARCSTART_OFF();    
			PWM_ON_MCU_OFF(); 
			HF_TIG_MCU_OFF();  
			Failed_Start=TRUE;
			/*Off wedding*/
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*0);	
			while(check_trigger()==ACTIVE){
        CHECK:				
				HAL_Delay(10);	
				if(check_trigger()==UNACTIVE){
					Failed_Start=FALSE;
					enableChangeMode=TRUE;
					left_quantity=OFF_;
          right_quantity=CURRENT;   
					HAL_Delay(1000);
					return FAIL;
				}
			}
			goto CHECK;
		}
		/*Only into this block when less than 2 seconds but release trigger*/ 
		else if(Time_Out==FALSE && check_trigger()==UNACTIVE){
			enableChangeMode=TRUE;
			/*PWM , HF and ARCSTART*/
			ARCSTART_OFF();   
			PWM_ON_MCU_OFF(); 
			HF_TIG_MCU_OFF();  
			#ifdef DEBUG
			  send_message("----released trigger");
      #endif
			return BREAK;
		}
		//HAL_Delay(1);
	}	
	/*Turn off HF and ARCSTART*/
	HF_TIG_MCU_OFF();  
	ARCSTART_OFF();   
	/*Delay 30ms*/
	HAL_Delay(30);
	return OK;
}
/**@fn check_currentON(void).
 * @param None.
 * @description 
 * Wait current on if after 5 seconds not current on will message error.
 * @retval FALSE or TRUE.
 */
static initialTypeDef check_currentON(stateTypeDef presentTrigger){
	EnableWaitTimeOut=TRUE;
	counter_wait_feedback_current=0;
	Time_Out=FALSE;
	while(check_current_on()==UNACTIVE){
		/*Turn off gas valve and PWM*/
		GAS_OUTPUT_EN_OFF(); 		
		PWM_ON_MCU_OFF();  
		Failed_Start=TRUE;
		/*Off wedding*/
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R,COEFFICIENT_DAC*0);
		/*Reset variables*/
		time_up_slope=0;
		time_down_slope=0;
		time_post_gas=0;
		if(presentTrigger==ACTIVE){
			while(check_trigger()==ACTIVE){
				CHECK:
				HAL_Delay(10);
				if(check_trigger()==UNACTIVE){
					Failed_Start=FALSE;
					enableChangeMode=TRUE;
					return FAIL;
				}
			}
			goto CHECK;
		}
		else{
			while(check_trigger()==UNACTIVE){
				CHECK1:
				HAL_Delay(10);
				if(check_trigger()==ACTIVE){
					while(check_trigger()==ACTIVE);
					Failed_Start=FALSE;
					enableChangeMode=TRUE;
					left_quantity=OFF_;
					right_quantity=CURRENT;
					return FAIL;
				}
			}
			goto CHECK1;
		}	
	}
	return OK;
}
