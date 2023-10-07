#ifndef __KEY_LED_H
#define __KEY_LED_H

#include "gpio.h"


/*************����LED����*************/

#define Board_LED_ON HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1)
#define Board_LED_OFF HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1)
#define Board_LED_Toggle HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin)

/*************LED1����*************/

#define LED1_ON HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1)
#define LED1_OFF HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0)
#define LED1_Toggle HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)

/*************LED2����*************/

#define LED2_ON HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1)
#define LED2_OFF HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 0)
#define LED2_Toggle HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin)

/*************��������*************/

// ����Ϊ1ʱ����
uint8_t trigger_gpio(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
// ����Ϊ0ʱ����
uint8_t trigger_gpio_up(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/*************��ఴ���Ķ�ȡ*************/

#define LKEY1 trigger_gpio(KEY_L_1_GPIO_Port, KEY_L_1_Pin)
#define LKEY2 trigger_gpio(KEY_L_2_GPIO_Port, KEY_L_2_Pin)
#define LKEY3 trigger_gpio(KEY_L_3_GPIO_Port, KEY_L_3_Pin)
#define LKEY4 trigger_gpio(KEY_L_4_GPIO_Port, KEY_L_4_Pin)

/*************�Ҳఴ���Ķ�ȡ*************/

#define RKEY1 trigger_gpio(KEY_R_1_GPIO_Port, KEY_R_1_Pin)
#define RKEY2 trigger_gpio(KEY_R_2_GPIO_Port, KEY_R_2_Pin)
#define RKEY3 trigger_gpio(KEY_R_3_GPIO_Port, KEY_R_3_Pin)
#define RKEY4 trigger_gpio(KEY_R_4_GPIO_Port, KEY_R_4_Pin)

/*************���������Ķ�ȡ*************/

#define KEY_UP_L trigger_gpio_up(KEY_UP_L_GPIO_Port, KEY_UP_L_Pin)
#define KEY_UP_R trigger_gpio_up(KEY_UP_R_GPIO_Port, KEY_UP_R_Pin)

/*************���صĶ�ȡ*************/

#define SWITCH_TOTAL HAL_GPIO_ReadPin(SWITCH_TOTAL_GPIO_Port, SWITCH_TOTAL_Pin)
#define SWITCH1 HAL_GPIO_ReadPin(SWITCH1_GPIO_Port, SWITCH1_Pin)
#define SWITCH2 HAL_GPIO_ReadPin(SWITCH2_GPIO_Port, SWITCH2_Pin)

#endif
