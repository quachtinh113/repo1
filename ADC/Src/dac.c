/* Includes ------------------------------------------------------------------*/
#include "dac.h"
#include "feedback_signals.h"
#include "stm32f1xx_hal_tim.h"
DAC_HandleTypeDef hdac;
/**@fn DAC_Init(void)
 * @description
 * Initialazation DAC
 * @retval Node.
 */
void DAC_Init(void){
  DAC_ChannelConfTypeDef sConfig = {0};
  /** DAC Initialization */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK){
    Error_Handler();
  }
  /** DAC channel OUT1 config */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK){
    Error_Handler();
  }
}
/**@fn start_DAC(void)
 * @description
 * Start DAC
 * @retval Node.
 */
void start_DAC(void){
	HAL_DAC_Start(&hdac,DAC_CHANNEL_1);
}
