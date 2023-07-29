/* Include */
#include "main.h"
/* Private define -----------------------------------------------------------*/
#define TIMEOUT   200
/* Private typedef -----------------------------------------------------------*/
typedef enum{
  CW = 0,  //clock wise
  CCW,     //counter clock wise
	IDLE     //idle
}RotationTypeDef;
/* Define pins use for encoder switch */
#define PIN_CLK              GPIO_PIN_8
#define PIN_DT               GPIO_PIN_7
#define PIN_SW               GPIO_PIN_11
/* Define ports use for encoder switch */
#define PORT_ENCODER         GPIOC
/*Functions encoder switch*/
extern void init_encoder(void);
extern RotationTypeDef read_encoder(uint8_t *lastStateCLK, uint8_t *counter, uint8_t minimum_counter, uint16_t maximum_conuter);

