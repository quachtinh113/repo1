/* Include */
#include "main.h"
/* Private defines -----------------------------------------------------------*/
#define MODE_Pin GPIO_PIN_12
#define MODE_GPIO_Port GPIOC
#define ARC_FORCE_Pin GPIO_PIN_7
#define ARC_FORCE_GPIO_Port GPIOC
#define PROCESS_Pin GPIO_PIN_2
#define PROCESS_GPIO_Port GPIOD
#define TRIGGER_COMMAND_Pin GPIO_PIN_10
#define TRIGGER_COMMAND_GPIO_Port GPIOB
#define FAN_START_Pin GPIO_PIN_15
#define FAN_START_GPIO_Port GPIOC

//#define CURRENT_ON_Pin GPIO_PIN_15
//#define CURRENT_ON_GPIO_Port GPIOA
#define CURRENT_ON_Pin GPIO_PIN_11
#define CURRENT_ON_GPIO_Port GPIOC

#define OT_IN_Pin GPIO_PIN_10
#define OT_IN_GPIO_Port GPIOC
#define ARC_START_Pin GPIO_PIN_9
#define ARC_START_GPIO_Port GPIOC
/* Private typedef -----------------------------------------------------------*/
typedef enum{
  WAIT = 0,
  PROCESS,
	MODE,
	FAN_START,
	CURRENT_ON,
	OT_IN,
	AC_TIG,
	OV_WARNING,
	ARC_START_MCU,
	AUTO_MODE_A_MCU,
	AUTO_MODE_B_MCU,
	POLARITY_EN_MCU,
	PULSE_BASE_MCU,
	TRIGGER_COMMAND,
	ARC_FORCE
} InputTypeDef;
/*Functions button*/
extern void MX_GPIO_Init(void);
extern InputTypeDef check_inputs(void);
extern stateTypeDef check_arc_force(void); 
extern stateTypeDef check_trigger(void); 
extern stateTypeDef check_OT(void);
extern stateTypeDef check_current_on(void);
extern stateTypeDef check_request_fan(void);
extern stateTypeDef check_arc_start(void);
