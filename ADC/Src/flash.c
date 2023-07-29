/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/**@fn HAL_StatusTypeDef flash_write(uint32_t address, uint8_t data[],uint16_t size)
 * @param  address: start address need flash, data: a array data need write, size: length of array
 * @description Write a buffer data into memory flash.
 * @retval HAL_OK if write flash success and else HAL_ERROR.
 */
HAL_StatusTypeDef flash_write(uint32_t address, uint8_t data[],uint16_t size){ 
	uint8_t i;
	uint32_t temp;
	/*Variable used for Erase procedure*/
	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PAGEError = 0;
	HAL_StatusTypeDef err_code;
	/* Fill EraseInit structure*/
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = address;
	EraseInitStruct.NbPages     = 1; //only erase a page.
	/* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();
	/* Erase data*/
	HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);
	/* Write data*/
	for(i=0;i<=size/4;i++){
		temp=((1<<24)*data[4*i+3])+((1<<16)*data[4*i+2])+((1<<8)*data[4*i+1])+((data[4*i]));
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address+4*i,temp);
	}
	/* Lock the Flash to disable the flash control register access (recommended
		 to protect the FLASH memory against possible unwanted operation) *********/
	HAL_FLASH_Lock();
	return err_code;
} 
/**@fn refresh_flash(void).
 * @param  None
 * @description Refresh flash.
 * @retval None
 */
void refresh_flash(void){
	/*Variable used for Erase procedure*/
	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PAGEError = 0;
	/* Fill EraseInit structure*/
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = basic_address;
	EraseInitStruct.NbPages     = 1; //Erase a page.
	/* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();
	/* Erase data*/
	HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);
}
/**@fn flash_read(uint32_t address)
 * @param  address: address of data need read.
 * @description Read a word data from memory flash.  
 * @retval a byte data read from flash.
 */
uint8_t flash_read(uint32_t address){
	return *(uint8_t *)address;
}
/**@fn read_buffer(uint32_t basic_address,uint8_t *buffer,uint8_t length)
 * @param  basic_address: address of data flash need read, buffer: buffer load data read from flash, size: size of buffer.  
 * @description Read a array data from memory flash. 
 * @retval None.
 */
void read_buffer(uint32_t basic_address,uint8_t *buffer,uint8_t length){
	for(uint8_t i=0; i< length; i++){
		buffer[i]=*(uint8_t *)(basic_address+i);
	}
}
/**@fn update_flash(uint32_t address, positionDef pos, uint8_t length).
 * @param  address: address store data, pos: are select process and mode, length: size data store into memory.  
 * @description Write a array or a byte into specified page.
 * @retval None.
 */
void update_flash(uint32_t address, positionDef pos, uint8_t length){
	uint8_t buf[length];
	buf[0]=pos.process;
	buf[1]=pos.mode;
	flash_write(address,buf,length);
}
