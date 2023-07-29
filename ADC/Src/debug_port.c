/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/* UART handler declaration */
UART_HandleTypeDef UartHandle;
/*Initialize uart 1*/
void init_uart(void){
	/*##-1- Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
- Word Length = 8 Bits (7 data bit + 1 parity bit) : BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
- Stop Bit    = One Stop bit
- Parity      = No parity
- BaudRate    = 115200 baud
- Hardware flow control disabled (RTS and CTS signals) */
  UartHandle.Instance        = USART1;
  UartHandle.Init.BaudRate   = 115200;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX;
  HAL_UART_Init(&UartHandle);
}
/*Function :Enter a message and send this message to monitor*/
void send_message(char * message){
	HAL_UART_Transmit(&UartHandle,(uint8_t*)message, strlen(message),10);
}
/*Function: Send a byte to monitor*/
void send_byte(uint8_t *data){
	HAL_UART_Transmit(&UartHandle,(uint8_t*)data,1,10);
}
/*Function: Send a number to monitor with number in range [0,9999]*/
void send_numbers(uint32_t number){
	uint8_t vNumber[4];
	vNumber[0]=0x30+number/1000;
	number%=1000;
	vNumber[1]=0x30+number/100;
	number%=100;
	vNumber[2]=0x30+number/10;
	vNumber[3]=0x30+number%10;
	send_message("Number:");
	HAL_UART_Transmit(&UartHandle,(uint8_t*)vNumber,4,10);
	send_message("\r\n");	
}

