 /* Includes ------------------------------------------------------------------*/
#include "includes.h"
/*Private variables ---------------------------------------------------------*/
uint8_t LED_PROCESS[NUMBER_MODE]={MMA,TIG};
uint8_t LED_MODE[NUMBER_MODE]={_2T,_4T};
SPI_HandleTypeDef hspi1;

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
HAL_StatusTypeDef SPI1_Init(void){
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;  
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK){
    return HAL_ERROR;
  }
	else {
		return HAL_OK;
	}
}
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void Control_LED_Init(void) 
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DISP_RST_Pin|LEDMUX_Pin|LED_LE_A_Pin|CURRENT_OUT_Pin, GPIO_PIN_RESET);
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ALPHA_NUM_EN_Pin|LIGTS_EN_Pin, GPIO_PIN_RESET);
  /*Configure GPIO pins : DISP_RST_Pin LEDMUX_Pin LED_LE_BC6_Pin CURRENT_OUT_Pin */
  GPIO_InitStruct.Pin = DISP_RST_Pin|LEDMUX_Pin|LED_LE_A_Pin|CURRENT_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : ALPHA_NUM_EN_Pin LIGTS_EN_Pin LED_LE_B_Pin */
  GPIO_InitStruct.Pin = ALPHA_NUM_EN_Pin|LIGTS_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


/**@fn HAL_StatusTypeDef transmiter_buffer(uint16_t data)
 * @param  data: Transmiter 2 bytes through via SPI.
 * @description
 * Transmiter data through via SPI.
 * @retval return HAL_OK if send success and else HAL_ERROR.
 */
HAL_StatusTypeDef transmiter_buffer(uint16_t data){
	uint8_t buf[2]={data>>8,data};
	
	if(HAL_SPI_Transmit(&hspi1,buf,2,1)!=HAL_OK){
		return HAL_ERROR;
	}
	else { 
		return HAL_OK;
	}
}

/**@fn HAL_StatusTypeDef transmiter_byte(uint8_t *data)
 * @param  data: Transmiter a byte through via SPI.
 * @description Transmiter data through via SPI.
 * @retval return HAL_OK if send success and else HAL_ERROR.
 */
HAL_StatusTypeDef transmiter_byte(uint8_t *data){
	if(HAL_SPI_Transmit(&hspi1,data,1,1)!=HAL_OK){
		return HAL_ERROR;
	}
	else { 
		return HAL_OK;
	}
}


