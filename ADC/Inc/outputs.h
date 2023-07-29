/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private defines -----------------------------------------------------------*/
#define BUZZER_Pin GPIO_PIN_4
#define BUZZER_GPIO_Port GPIOB
#define PWM_ON_MCU_Pin GPIO_PIN_12
#define PWM_ON_MCU_GPIO_Port GPIOB
#define HF_TIG_MCU_Pin GPIO_PIN_10
#define HF_TIG_MCU_GPIO_Port GPIOA
#define MMA_MCU_Pin GPIO_PIN_12
#define MMA_MCU_GPIO_Port GPIOA
#define AC_POLARITY_Pin GPIO_PIN_1
#define AC_POLARITY_GPIO_Port GPIOC
#define ASSIT_AARC_Pin GPIO_PIN_2
#define ASSIT_AARC_GPIO_Port GPIOC
#define ARC_VALID_MCU_Pin GPIO_PIN_3
#define ARC_VALID_MCU_GPIO_Port GPIOC
#define F_RUN_Pin GPIO_PIN_11
#define F_RUN_GPIO_Port GPIOB
#define ARCSTART_Pin GPIO_PIN_1
#define ARCSTART_GPIO_Port GPIOB
#define GAS_OUTPUT_EN_Pin GPIO_PIN_2
#define GAS_OUTPUT_EN_GPIO_Port GPIOB
#define MMA_LEFTTIG_VRD_MCU_Pin GPIO_PIN_11
#define MMA_LEFTTIG_VRD_MCU_GPIO_Port GPIOA
#define BUZZER_OFF()               HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET)
#define BUZZER_ON()                HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET)
#define PWM_ON_MCU_OFF()           HAL_GPIO_WritePin(PWM_ON_MCU_GPIO_Port, PWM_ON_MCU_Pin, GPIO_PIN_RESET)
#define PWM_ON_MCU_ON()            HAL_GPIO_WritePin(PWM_ON_MCU_GPIO_Port, PWM_ON_MCU_Pin, GPIO_PIN_SET)
#define HF_TIG_MCU_OFF()           HAL_GPIO_WritePin(HF_TIG_MCU_GPIO_Port, HF_TIG_MCU_Pin, GPIO_PIN_RESET)
#define HF_TIG_MCU_ON()            HAL_GPIO_WritePin(HF_TIG_MCU_GPIO_Port, HF_TIG_MCU_Pin, GPIO_PIN_SET)
#define MMA_MCU_OFF()              HAL_GPIO_WritePin(MMA_MCU_GPIO_Port, MMA_MCU_Pin, GPIO_PIN_RESET)
#define MMA_MCU_ON()               HAL_GPIO_WritePin(MMA_MCU_GPIO_Port, MMA_MCU_Pin, GPIO_PIN_SET)
#define AC_POLARITY_OFF()          HAL_GPIO_WritePin(AC_POLARITY_GPIO_Port, AC_POLARITY_Pin, GPIO_PIN_RESET)
#define AC_POLARITY_ON()           HAL_GPIO_WritePin(AC_POLARITY_GPIO_Port, AC_POLARITY_Pin, GPIO_PIN_SET)
#define ASSIT_AARC_OFF()           HAL_GPIO_WritePin(ASSIT_AARC_GPIO_Port, ASSIT_AARC_Pin, GPIO_PIN_RESET)
#define ASSIT_AARC_ON()            HAL_GPIO_WritePin(ASSIT_AARC_GPIO_Port, ASSIT_AARC_Pin, GPIO_PIN_SET)
#define ARC_VALID_MCU_OFF()        HAL_GPIO_WritePin(ARC_VALID_MCU_GPIO_Port, ARC_VALID_MCU_Pin, GPIO_PIN_RESET)
#define ARC_VALID_MCU_ON()         HAL_GPIO_WritePin(ARC_VALID_MCU_GPIO_Port, ARC_VALID_MCU_Pin, GPIO_PIN_SET)
#define F_RUN_OFF()                HAL_GPIO_WritePin(F_RUN_GPIO_Port, F_RUN_Pin, GPIO_PIN_RESET)
#define F_RUN_ON()                 HAL_GPIO_WritePin(F_RUN_GPIO_Port, F_RUN_Pin, GPIO_PIN_SET)
#define ARCSTART_OFF()             HAL_GPIO_WritePin(ARCSTART_GPIO_Port, ARCSTART_Pin, GPIO_PIN_RESET)
#define ARCSTART_ON()              HAL_GPIO_WritePin(ARCSTART_GPIO_Port, ARCSTART_Pin, GPIO_PIN_SET)
#define GAS_OUTPUT_EN_OFF()        HAL_GPIO_WritePin(GAS_OUTPUT_EN_GPIO_Port, GAS_OUTPUT_EN_Pin, GPIO_PIN_RESET)
#define GAS_OUTPUT_EN_ON()         HAL_GPIO_WritePin(GAS_OUTPUT_EN_GPIO_Port, GAS_OUTPUT_EN_Pin, GPIO_PIN_SET)
#define MMA_LEFTTIG_VRD_MCU_OFF()  HAL_GPIO_WritePin(MMA_LEFTTIG_VRD_MCU_GPIO_Port, MMA_LEFTTIG_VRD_MCU_Pin, GPIO_PIN_RESET)
#define MMA_LEFTTIG_VRD_MCU_ON()   HAL_GPIO_WritePin(MMA_LEFTTIG_VRD_MCU_GPIO_Port, MMA_LEFTTIG_VRD_MCU_Pin, GPIO_PIN_SET)
extern void Output_Init(void);
extern void sound_beep(void);
extern void sound_beep_(void);

