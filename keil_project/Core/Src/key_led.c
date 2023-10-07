#include "key_led.h"
#include "cmsis_os.h"


uint8_t trigger_gpio(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	int result = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
	osDelay(8);
	if(result == HAL_GPIO_ReadPin(GPIOx, GPIO_Pin))
		return result==1;
	return 0;
}


uint8_t trigger_gpio_up(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	int result = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
	osDelay(8);
	if(result == HAL_GPIO_ReadPin(GPIOx, GPIO_Pin))
		return result==0;
	return 0;
}
