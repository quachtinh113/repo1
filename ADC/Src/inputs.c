/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/*Private variables ---------------------------------------------------------*/
PreviousStateDef previousState;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None+
  */
 void MX_GPIO_Init(void){
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PROCESS_Pin ARC_FORCE_Pin FAN_START_Pin OT_IN_Pin ARC_START_Pin*/
  GPIO_InitStruct.Pin = PROCESS_Pin | ARC_FORCE_Pin | FAN_START_Pin | OT_IN_Pin | ARC_START_Pin | CURRENT_ON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
  /*Configure GPIO pin : MODE_Pin */
  GPIO_InitStruct.Pin = MODE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(MODE_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : TRIGGER COMMAND */
  GPIO_InitStruct.Pin = TRIGGER_COMMAND_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(TRIGGER_COMMAND_GPIO_Port, &GPIO_InitStruct);
	
	/*Configure GPIO pin : CURRENT_ON_Pin*/
  /*GPIO_InitStruct.Pin = CURRENT_ON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(CURRENT_ON_GPIO_Port, &GPIO_InitStruct);*/
	
	/*Start state of buttons are release*/
	previousState.Process=RELEASE;
	previousState.Mode=RELEASE;
	previousState.ArcForce=RELEASE;
}
/** @fn check_inputs_press(void).
 * @description 
 * Check button presssed.
 * @retval Code button defined by developer.
 */
InputTypeDef check_inputs(void){
	if(HAL_GPIO_ReadPin(PROCESS_GPIO_Port,PROCESS_Pin)==GPIO_PIN_RESET && previousState.Process==RELEASE){
		previousState.Process=PRESS;
		return PROCESS;
	}
	else if(HAL_GPIO_ReadPin(PROCESS_GPIO_Port,PROCESS_Pin)==GPIO_PIN_SET && previousState.Process==PRESS){
		previousState.Process=RELEASE;
	}
	
	else if(HAL_GPIO_ReadPin(MODE_GPIO_Port,MODE_Pin)==GPIO_PIN_RESET && previousState.Mode==RELEASE){
		previousState.Mode=PRESS;
		return MODE;
	}
	else if(HAL_GPIO_ReadPin(MODE_GPIO_Port,MODE_Pin)==GPIO_PIN_SET && previousState.Mode==PRESS){
		previousState.Mode=RELEASE;
	}
	return WAIT;
}
/** @fn check_arc_force(void).
 * @description 
 * Check state arc force.
 * @retval ACTIVE or UNACTIVE.
 */
stateTypeDef check_arc_force(void){
	if(HAL_GPIO_ReadPin(ARC_FORCE_GPIO_Port,ARC_FORCE_Pin)==GPIO_PIN_RESET){
		return ACTIVE;
	}		
	else{
		return UNACTIVE;
	}			
}
/** @fn check_trigger(void).
 * @description 
 * Check state trigger.
 * @retval ACTIVE or UNACTIVE.
 */
stateTypeDef check_trigger(void){
	if(HAL_GPIO_ReadPin(TRIGGER_COMMAND_GPIO_Port,TRIGGER_COMMAND_Pin)==GPIO_PIN_RESET){
		return ACTIVE;
	}		
	else{
		return UNACTIVE;
	}			
}
/** @fn check_OT(void).
 * @description 
 * Check state OT.
 * @retval ACTIVE or UNACTIVE.
 */
stateTypeDef check_OT(void){
	if(HAL_GPIO_ReadPin(OT_IN_GPIO_Port,OT_IN_Pin)==GPIO_PIN_RESET){
		return ACTIVE;
	}		
	else{
		return UNACTIVE;
	}			
}
/** @fn check_current_on(void).
 * @description 
 * Check state current on.
 * @retval ACTIVE or UNACTIVE.
 */
stateTypeDef check_current_on(void){
	if(HAL_GPIO_ReadPin(CURRENT_ON_GPIO_Port,CURRENT_ON_Pin)==GPIO_PIN_RESET){
		return ACTIVE;
	}		
	else{
		return UNACTIVE;
	}			
}
/** @fn check_request_fan(void).
 * @description 
 * Check request.
 * @retval ACTIVE or UNACTIVE.
 */
stateTypeDef check_request_fan(void){
	if(HAL_GPIO_ReadPin(FAN_START_GPIO_Port,FAN_START_Pin)==GPIO_PIN_RESET){ 
		return ACTIVE;
	}		
	else{
		return UNACTIVE;
	}			
}
/** @fn check_request_fan(void).
 * @description 
 * Check arc start.
 * @retval ACTIVE or UNACTIVE.
 */
stateTypeDef check_arc_start(void){
	if(HAL_GPIO_ReadPin(ARC_START_GPIO_Port,ARC_START_Pin)==GPIO_PIN_RESET){ 
		return ACTIVE;
	}		
	else{
		return UNACTIVE;
	}			
}


 
