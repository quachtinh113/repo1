/* Includes */
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
typedef enum{
  _PREGAS=16,
  _INITIAL_CURRENT=17,
  _UP_SLOPE=18,
  _PEAK_CURRENT=19,
  _BASE_CURRENT=21, 
  _DOWN_SLOPE=25,
  _CRATER_CURRENT=26,
  _POST_GAS=27,
	_PULSE_FREQUENCY=20,
	_PULSE_DUTY_CYCLE=22,
	_AC_FREQUENCY=23,
  _AC_DUTY_CYCLE=24
}LedBencMarkTypeDef;
/* Private defines -----------------------------------------------------------*/
#define _10A     10
#define _5A     5
#define ALL_LEDS 8
#define CURRENT_OUT_Pin GPIO_PIN_0
#define CURRENT_OUT_GPIO_Port GPIOC
#define DISP_RST_Pin GPIO_PIN_4
#define DISP_RST_GPIO_Port GPIOC
#define LEDMUX_Pin GPIO_PIN_5
#define LEDMUX_GPIO_Port GPIOC
#define ALPHA_NUM_EN_Pin GPIO_PIN_13
#define ALPHA_NUM_EN_GPIO_Port GPIOB
#define LIGTS_EN_Pin GPIO_PIN_14
#define LIGTS_EN_GPIO_Port GPIOB
#define LED_LE_A_Pin GPIO_PIN_6
#define LED_LE_A_GPIO_Port GPIOC
#define DISP_RST_LOW()           HAL_GPIO_WritePin(DISP_RST_GPIO_Port, DISP_RST_Pin, GPIO_PIN_RESET)
#define DISP_RST_HIGH()          HAL_GPIO_WritePin(DISP_RST_GPIO_Port, DISP_RST_Pin, GPIO_PIN_SET)
#define LIGTS_EN_LOW()           HAL_GPIO_WritePin(LIGTS_EN_GPIO_Port, LIGTS_EN_Pin, GPIO_PIN_RESET)
#define LIGTS_EN_HIGH()          HAL_GPIO_WritePin(LIGTS_EN_GPIO_Port, LIGTS_EN_Pin, GPIO_PIN_SET)
#define LED_LE_A_LOW()           HAL_GPIO_WritePin(LED_LE_A_GPIO_Port, LED_LE_A_Pin, GPIO_PIN_RESET)
#define LED_LE_A_HIGH()          HAL_GPIO_WritePin(LED_LE_A_GPIO_Port, LED_LE_A_Pin, GPIO_PIN_SET)
#define LEDMUX_LOW()             HAL_GPIO_WritePin(LEDMUX_GPIO_Port, LEDMUX_Pin, GPIO_PIN_RESET)
#define LEDMUX_HIGH()            HAL_GPIO_WritePin(LEDMUX_GPIO_Port, LEDMUX_Pin, GPIO_PIN_SET)
#define ALPHA_NUM_EN_LOW()       HAL_GPIO_WritePin(ALPHA_NUM_EN_GPIO_Port, ALPHA_NUM_EN_Pin, GPIO_PIN_RESET)
#define ALPHA_NUM_EN_HIGH()      HAL_GPIO_WritePin(ALPHA_NUM_EN_GPIO_Port, ALPHA_NUM_EN_Pin, GPIO_PIN_SET)
#define CURRENT_OUT_OFF()        HAL_GPIO_WritePin(CURRENT_OUT_GPIO_Port, CURRENT_OUT_Pin, GPIO_PIN_RESET)
#define CURRENT_OUT_ON()         HAL_GPIO_WritePin(CURRENT_OUT_GPIO_Port, CURRENT_OUT_Pin, GPIO_PIN_SET)
/* Functions process display*/
extern void Control_LED_Init(void);
extern HAL_StatusTypeDef SPI1_Init(void);
extern HAL_StatusTypeDef transmiter_buffer(uint16_t data);
extern HAL_StatusTypeDef transmiter_byte(uint8_t *data); 
extern void leds_button(positionDef position);
extern void clear_all_LEDs(void);



