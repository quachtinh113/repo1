/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
typedef enum{
	LOW=0,
	HIGH
}HaftwordTypeDef;
typedef enum{
  MMA,
  TIG,
  _2T,
  _4T,
  A,
	V,
  S,
  WARNING,
	CURRENT_OUT
}LedTypeDef;
typedef enum{
	OFF_LED=0,
	ON_LED
}SwitchLedTypeDef;
/* Functions process display leds single*/
extern void switch_led(LedTypeDef led, SwitchLedTypeDef state);
