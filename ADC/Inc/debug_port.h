/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
extern void init_uart(void);
extern void send_message(char* message);
extern void send_byte(uint8_t *data);
extern void send_numbers(uint32_t number);

