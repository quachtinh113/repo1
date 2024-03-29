/**
  ******************************************************************************
  * @file    FreeRTOS/FreeRTOS_ThreadCreation/Inc/main.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the main.c
  *          file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
#define DEBUG
#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_nucleo.h"
/* Exported types ------------------------------------------------------------*/
typedef enum{	FALSE=0,
	TRUE=1
}bool;
typedef struct {
	uint8_t process;
	uint8_t mode;
}positionDef;
typedef enum{
	UNACTIVE,
	ACTIVE
} stateTypeDef;
typedef enum{
  PRESS,
	RELEASE
} StateInputTypeDef;
typedef struct {
	uint8_t Process;
	uint8_t Mode;
	uint8_t ArcForce;
}PreviousStateDef;

typedef enum{
	BREAK,
	FAIL,
	OK
} initialTypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
