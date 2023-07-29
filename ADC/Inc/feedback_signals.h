/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private defines -----------------------------------------------------------*/
#define SAMPLE_TIMES      10
#define NUMBERS_CHANNEL_ADC             6
#define MINIMUM_VOLTAGE_DETECT_REMOTE   0.1
/* Functions process feedback signals*/
extern void MX_ADC1_Init(void);
extern void MX_DMA_Init(void); 
extern void Error_Handler(void);
