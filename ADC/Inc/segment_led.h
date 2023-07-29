/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
typedef enum{
  _RIGHT,
  _LEFT 	
}PositionLedTypeDef;
typedef enum{
  CURRENT,
	VOLTAGE,
  TIME_,
	ERROR_START,
	OFF_
}quantityDef;
typedef enum{
	DONE,
	OT,
  ADJUST,
  WELD,
	NORMAL
}taskDef;
/* Functions process 7 segments LEDs*/
extern void out_segment_leds(uint8_t led[], PositionLedTypeDef pos);
extern void display_7seg(uint16_t number, PositionLedTypeDef pos, quantityDef quantity);
