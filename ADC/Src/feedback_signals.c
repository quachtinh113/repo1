/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
uint16_t adc_buffer[NUMBERS_CHANNEL_ADC];
uint16_t sample_adc_buffer[NUMBERS_CHANNEL_ADC];
uint16_t sample_times=0;
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void){
}
/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
void MX_ADC1_Init(void){
  ADC_ChannelConfTypeDef sConfig = {0};
  /** Common config 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 6;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_2;
	
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_3;

  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
	 /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = ADC_REGULAR_RANK_4;
	
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
	 /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = ADC_REGULAR_RANK_5;

  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
	 /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_13;
  sConfig.Rank = ADC_REGULAR_RANK_6;

  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/** 
  * Enable DMA controller clock
  */
void MX_DMA_Init(void) {
	/* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}
void babientro(void){
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
		}			

