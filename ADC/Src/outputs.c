/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/* Private variables ---------------------------------------------------------*/
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void Output_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, HF_TIG_MCU_Pin|MMA_MCU_Pin|MMA_LEFTTIG_VRD_MCU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : HF_TIG_MCU_Pin MMA_MCU_Pin MMA_LEFTTIG_VRD_MCU_Pin*/
  GPIO_InitStruct.Pin = HF_TIG_MCU_Pin|MMA_MCU_Pin|MMA_LEFTTIG_VRD_MCU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, PWM_ON_MCU_Pin|F_RUN_Pin|ARCSTART_Pin|GAS_OUTPUT_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PWM_ON_MCU_Pin F_RUN_Pin ARCSTART_Pin GAS_OUTPUT_EN_Pin*/
  GPIO_InitStruct.Pin = PWM_ON_MCU_Pin|F_RUN_Pin|ARCSTART_Pin|GAS_OUTPUT_EN_Pin|BUZZER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	 
	/*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, AC_POLARITY_Pin|ASSIT_AARC_Pin|ARC_VALID_MCU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : AC_POLARITY_Pin ASSIT_AARC_Pin */
  GPIO_InitStruct.Pin = AC_POLARITY_Pin|ASSIT_AARC_Pin|ARC_VALID_MCU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	/*Set state for pins*/
	BUZZER_OFF();
	PWM_ON_MCU_OFF();
  HF_TIG_MCU_OFF();     
  MMA_MCU_OFF();
	AC_POLARITY_OFF();
	ASSIT_AARC_OFF();
	ARC_VALID_MCU_OFF();
	F_RUN_OFF();
  ARCSTART_OFF();
  GAS_OUTPUT_EN_OFF();
  MMA_LEFTTIG_VRD_MCU_OFF();
}
/**@fn sound_beep(void)
 * @param  Node.
 * @description
 * Sound beep
 * @retval None.
 */
void sound_beep(void){
	BUZZER_ON();
	HAL_Delay(10);
  BUZZER_OFF();	
}
/**@fn sound_beep_(void)
 * @param  Node.
 * @description
 * Sound beep
 * @retval None.
 */
void sound_beep_(void){   
	BUZZER_ON();
	HAL_Delay(1);
  BUZZER_OFF();	
}
