/* Include */
#include "main.h"  
/* Private typedef -----------------------------------------------------------*/
#define NUMBER_PROCESS       2
#define NUMBER_MODE          2
#define TIME              3000
#define _100MS              40
#define _10MS                4
#define _2_5MS               1
#define _2S                800
#define PREGAS_TIME          5
#define UP_SLOPE            10
typedef enum{
  turn_off,
  turn_on,
}State;
typedef enum{
  mma,
	tig,
}Process;
typedef enum{
  _2T_,
  _4T_,
}LedMode;
/*Functions process*/
static void Delay(uint32_t time);                                               
extern positionDef restore_state(void);
extern void process_2T(void);
extern void process_4T(void);
static initialTypeDef wait_current_on(void);
static initialTypeDef check_currentON(stateTypeDef presentTrigger);
