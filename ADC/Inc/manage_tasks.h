/* Include */
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
#define OT_DISPLAY          0
#define _4SECOND         1600
#define _50MS             100
#define DIFFERRENCE         0.9
#define MINIMUM_CURRENT    10
#define INITIAL_CURRENT    30
#define CRATER_CURRENT     30
#define OFF_CURRENT         0
#define SAMPLE             50
#define HOT_START_MMA      50
#define _10A               10
#define _5A               	5
#define LESS_MIN_CURRENT    9.99
#define AVERAGE_TOLERANCE  65
typedef enum{    
	ADJUST_CURRENT,
	ADJUST_ARC_FORCE,
	ADJUST_POST_GAS,
	ADJUST_DOWN_SLOPE,
	UNADJUST
}adjustDef;
/* Functions process tasks*/
extern void process_inputs(void *pvParameters);
extern void process_welding(void *pvParameters);
extern void process_timer_1ms(void *pvParameters);
extern void process_timer_update_duty(void *pvParameters);
extern void process_display(void *pvParameters);
extern void process_feedback_signals(void *pvParameters);
extern void update_outputs(void *pvParameters);
static void turn_off_weld(void);
static void wait_time_out(void);





