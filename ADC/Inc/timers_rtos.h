/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private define -----------------------------------------------------------*/
#define TIMEOUT   40
/* Private typedef -----------------------------------------------------------*/
typedef enum{
  NONE = 0,
  SAVE
} FLAG_SAVE;
/* Private Functions -----------------------------------------------------------*/
extern uint8_t times_1ms(void);
