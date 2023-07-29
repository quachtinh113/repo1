/**
  ******************************************************************************
  * @file    FreeRTOS/FreeRTOS_ThreadCreation/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
/* Private variables ---------------------------------------------------------*/
positionDef position;
int main(void){
  HAL_Init();
  /*Configure the System clock to 64 MHz */
  SystemClock_Config();
	/*Initialize serial port*/
	#ifdef DEBUG
	  init_uart();
		send_message("Initialize device\r\n");  
  #endif
	/*Initialize buttons*/
	MX_GPIO_Init();
	/*Initialize display*/
	SPI1_Init();
	Control_LED_Init();
	/*Initialize outputs*/
	Output_Init();
	/*Initialize ADC and DMA*/
	MX_DMA_Init();
  MX_ADC1_Init();

		
  /* Create task process display LEDs */ 	
	xTaskCreate( 
		process_display,                  /* Function pointer */ 
		"Task display",                   /* Task name - for debugging only*/ 
		configMINIMAL_STACK_SIZE,         /* Stack depth in words */ 
		(void*) NULL,                     /* Pointer to tasks arguments (parameter) */ 
		tskIDLE_PRIORITY + 2UL,           /* Task priority*/ 
		NULL                              /* Task handle */ 
  ); 		
  /* Create task process Feedback signals */ 	
	xTaskCreate( 
		process_feedback_signals,                  /* Function pointer */ 
		"Task feedback signals",                   /* Task name - for debugging only*/ 
		configMINIMAL_STACK_SIZE,                  /* Stack depth in words */ 
		(void*) NULL,                              /* Pointer to tasks arguments (parameter) */ 
		tskIDLE_PRIORITY + 2UL,                    /* Task priority*/ 
		NULL                                       /* Task handle */ 
  ); 						
	/* Start the RTOS scheduler */
  vTaskStartScheduler();
		
	/* Halt */

		while(1);
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
