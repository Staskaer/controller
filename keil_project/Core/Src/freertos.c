/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adc.h"
#include "stdio.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "key_led.h"
#include "OLED.h"   
#include <stdlib.h>
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

void draw_rect(uint8_t x,uint8_t y,uint8_t x2,uint8_t y2)
{

	OLED_draw_line(x, y, x2,y,PEN_WRITE);
	OLED_draw_line(x, y, x,y2,PEN_WRITE);
	OLED_draw_line(x2, y2, x2,y,PEN_WRITE);
	OLED_draw_line(x, y2, x2,y2,PEN_WRITE);
	
}

void eraser_rect(uint8_t x,uint8_t y,uint8_t x2,uint8_t y2)
{

	OLED_draw_line(x, y, x2,y,PEN_CLEAR);
	OLED_draw_line(x, y, x,y2,PEN_CLEAR);
	OLED_draw_line(x2, y2, x2,y,PEN_CLEAR);
	OLED_draw_line(x, y2, x2,y2,PEN_CLEAR);
	
}

void draw_point(uint8_t x,uint8_t y)
{
	OLED_draw_point(x,y,PEN_WRITE);
	OLED_draw_point(x-1,y,PEN_WRITE);
	OLED_draw_point(x+1,y,PEN_WRITE);
	OLED_draw_point(x,y-1,PEN_WRITE);
	OLED_draw_point(x,y+1,PEN_WRITE);
}

void eraser_point(uint8_t x,uint8_t y)
{
	OLED_draw_point(x,y,PEN_CLEAR);
	OLED_draw_point(x-1,y,PEN_CLEAR);
	OLED_draw_point(x+1,y,PEN_CLEAR);
	OLED_draw_point(x,y-1,PEN_CLEAR);
	OLED_draw_point(x,y+1,PEN_CLEAR);
}


// 定义了方向，最左侧为1，顺时针增加
#define LFLAG 1
#define UFLAG 2
#define RFLAG 3
#define DFLAG 4

void draw_key_line(uint8_t x, uint8_t y, uint8_t FLAG)
{
	// 给出中间点，自动延伸
	// 左侧   上:21,19 | 下:21,25 | 左:17,20 | 右25,20
	// 右侧   上:21+85,19 | 下:21+85,25 | 左:17+85,20 | 右25+85,20
//	draw_key_line(21,19,UFLAG);
//	draw_key_line(25,20,RFLAG);
//	draw_key_line(17,20,LFLAG);
//	draw_key_line(21,25,DFLAG);
	switch(FLAG)
	{
		case LFLAG:
			OLED_draw_point(x,y,PEN_WRITE);
			OLED_draw_point(x-3,y,PEN_WRITE);
			OLED_draw_point(x-4,y,PEN_WRITE);
			OLED_draw_point(x-7,y,PEN_WRITE);
		
			OLED_draw_point(x-1,y,PEN_CLEAR);
			OLED_draw_point(x-2,y,PEN_CLEAR);
			OLED_draw_point(x-5,y,PEN_CLEAR);
			OLED_draw_point(x-6,y,PEN_CLEAR);
			break;
		case RFLAG:
			OLED_draw_point(x,y,PEN_WRITE);
			OLED_draw_point(x+3,y,PEN_WRITE);
			OLED_draw_point(x+4,y,PEN_WRITE);
			OLED_draw_point(x+7,y,PEN_WRITE);
		
			OLED_draw_point(x+1,y,PEN_CLEAR);
			OLED_draw_point(x+2,y,PEN_CLEAR);
			OLED_draw_point(x+5,y,PEN_CLEAR);
			OLED_draw_point(x+6,y,PEN_CLEAR);
			break;
		case DFLAG:
			OLED_draw_point(x,y,PEN_WRITE);
			OLED_draw_point(x,y+3,PEN_WRITE);
			OLED_draw_point(x,y+4,PEN_WRITE);
			OLED_draw_point(x,y+7,PEN_WRITE);
		
			OLED_draw_point(x,y+1,PEN_CLEAR);
			OLED_draw_point(x,y+2,PEN_CLEAR);
			OLED_draw_point(x,y+5,PEN_CLEAR);
			OLED_draw_point(x,y+6,PEN_CLEAR);
			break;
		case UFLAG:
			OLED_draw_point(x,y,PEN_WRITE);
			OLED_draw_point(x,y-3,PEN_WRITE);
			OLED_draw_point(x,y-4,PEN_WRITE);
			OLED_draw_point(x,y-7,PEN_WRITE);
		
			OLED_draw_point(x,y-1,PEN_CLEAR);
			OLED_draw_point(x,y-2,PEN_CLEAR);
			OLED_draw_point(x,y-5,PEN_CLEAR);
			OLED_draw_point(x,y-6,PEN_CLEAR);
			break;
	}
}

void bold_key_line(uint8_t x, uint8_t y, uint8_t FLAG)
{
	// 给出中间点，自动延伸
	// 左侧   上:21,19 | 下:21,25 | 左:17,20 | 右25,20
	// 右侧   上:21+85,19 | 下:21+85,25 | 左:17+85,20 | 右25+85,20
	switch(FLAG)
	{
		case LFLAG:
			OLED_draw_point(x-1,y,PEN_WRITE);
			OLED_draw_point(x-2,y,PEN_WRITE);
			OLED_draw_point(x-5,y,PEN_WRITE);
			OLED_draw_point(x-6,y,PEN_WRITE);
			break;
		case RFLAG:
			OLED_draw_point(x+1,y,PEN_WRITE);
			OLED_draw_point(x+2,y,PEN_WRITE);
			OLED_draw_point(x+5,y,PEN_WRITE);
			OLED_draw_point(x+6,y,PEN_WRITE);
			break;
		case DFLAG:
			OLED_draw_point(x,y+1,PEN_WRITE);
			OLED_draw_point(x,y+2,PEN_WRITE);
			OLED_draw_point(x,y+5,PEN_WRITE);
			OLED_draw_point(x,y+6,PEN_WRITE);
			break;
		case UFLAG:
			OLED_draw_point(x,y-1,PEN_WRITE);
			OLED_draw_point(x,y-2,PEN_WRITE);
			OLED_draw_point(x,y-5,PEN_WRITE);
			OLED_draw_point(x,y-6,PEN_WRITE);
			break;
	}
}


uint8_t compute_bias(uint16_t data)
{
	return (uint8_t)(data/4096.0*21);
}

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId miantaskHandle;
osThreadId ADCtaskHandle;
osThreadId keytaskHandle;
osThreadId iictaskHandle;
osSemaphoreId adc_semHandle;
osSemaphoreId key_semHandle;
osSemaphoreId iic_semHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

// 全局变量，使用信号量来进行控制

struct Data
{
// ADC采样数据，x1、y1是左手柄的x、y值，摇杆在中间时，两者均为2048左右
// x2、y2是右手柄的x、y值，摇杆在中间时，两者均为2048左右
// b1 b2是顶部左右两个电位器，电位器向中间旋转时，数值会增大
uint16_t g_x1, g_x2, g_y1, g_y2, g_b1, g_b2;

// 一共8+2+3的读取，用16位来表示，仅使用后13位
// 后八位为key_left和key_right的表示
// 前5位为switch和顶部key的表示
uint16_t g_key_result;

// 表示位置和当前的x、y方向上的角度
// pos_x的范围为[420,850] pos_y的范围为[320, 610]
// 角度x的范围为(-50, +50) 角度y的范围为(-80, +80)
float g_pos_x,g_pos_y;
float g_x,g_y;

} global_data={0};


void trans_func(struct Data d)
{
	
	if(d.g_y1<1000)
		printf("w");
	else if(d.g_x1<1000)
		printf("a");
	else if(d.g_x1>3900)
		printf("d");
}

/* USER CODE END FunctionPrototypes */

void main_func(void const * argument);
void ADC_func(void const * argument);
void key_func(void const * argument);
void iic_func(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of adc_sem */
  osSemaphoreDef(adc_sem);
  adc_semHandle = osSemaphoreCreate(osSemaphore(adc_sem), 1);

  /* definition and creation of key_sem */
  osSemaphoreDef(key_sem);
  key_semHandle = osSemaphoreCreate(osSemaphore(key_sem), 1);

  /* definition and creation of iic_sem */
  osSemaphoreDef(iic_sem);
  iic_semHandle = osSemaphoreCreate(osSemaphore(iic_sem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of miantask */
  osThreadDef(miantask, main_func, osPriorityNormal, 0, 128);
  miantaskHandle = osThreadCreate(osThread(miantask), NULL);

  /* definition and creation of ADCtask */
  osThreadDef(ADCtask, ADC_func, osPriorityIdle, 0, 128);
  ADCtaskHandle = osThreadCreate(osThread(ADCtask), NULL);

  /* definition and creation of keytask */
  osThreadDef(keytask, key_func, osPriorityIdle, 0, 128);
  keytaskHandle = osThreadCreate(osThread(keytask), NULL);

  /* definition and creation of iictask */
  osThreadDef(iictask, iic_func, osPriorityIdle, 0, 128);
  iictaskHandle = osThreadCreate(osThread(iictask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_main_func */
/**
  * @brief  Function implementing the miantask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_main_func */
void main_func(void const * argument)
{
  /* USER CODE BEGIN main_func */
	// 定义一些局部变量来暂存全局数据
	struct Data local_data;
	
	{
	// 两个大矩形来表示摇杆
	draw_rect(9,39,33,63);
	draw_point(21,51);
	
	draw_rect(94,39,118,63);
	draw_point(106,51);

	// 绘制电阻器的两个矩形框
	draw_rect(9,1,33,5);
	draw_point(21,3);
	
	draw_rect(94,1,118,5);
	draw_point(106,3);

	
	// 绘制顶部按键的两个矩形框
	draw_rect(3,1,7,5);
	draw_rect(120,1,124,5);
	
	// 绘制中间三个矩形按键表示
	draw_rect(36,17,52,25);
	OLED_draw_line(36+8,17,36+8,25,PEN_WRITE);
	draw_rect(55,17,71,25);
	OLED_draw_line(55+8,17,55+8,25,PEN_WRITE);
	draw_rect(74,17,90,25);
	OLED_draw_line(74+8,17,74+8,25,PEN_WRITE);
	
	// 绘制中间最大的矩形，用于表示mpu数据
	draw_rect(40,30,87,63);
	
	// 绘制8个按键
	draw_key_line(21,17,UFLAG);
	draw_key_line(25,20,RFLAG);
	draw_key_line(17,20,LFLAG);
	draw_key_line(21,23,DFLAG);
	draw_key_line(21+85,17,UFLAG);
	draw_key_line(25+85,20,RFLAG);
	draw_key_line(17+85,20,LFLAG);
	draw_key_line(21+85,23,DFLAG);
	
	osDelay(100);
	
	}
  /* Infinite loop */
  for(;;)
  {
	
		//OLED_operate_gram(PEN_CLEAR);//清缓存
		if( xSemaphoreTake(adc_semHandle,portMAX_DELAY)==pdPASS)
		{
			if( xSemaphoreTake(key_semHandle,portMAX_DELAY)==pdPASS)
			{
				if( xSemaphoreTake(iic_semHandle,portMAX_DELAY)==pdPASS)
				{
					// 到达这里表示三个锁已经全部获取，可以暂存数据并用于后续输出
					
					memcpy(&local_data, &global_data ,sizeof(struct Data));
					xSemaphoreGive(iic_semHandle);
				}
				else
				{
					continue;
				}
				xSemaphoreGive(key_semHandle);
			}
			else
			{
				continue;
			}
			xSemaphoreGive(adc_semHandle);
		}
		else
		{
			continue;
		}
		
		// 然后执行发送函数
		trans_func(local_data);
		
		Board_LED_Toggle;
		osDelay(300);
//		LED1_Toggle;
//		LED2_Toggle;
//    osDelay(200);
  }
  /* USER CODE END main_func */
}

/* USER CODE BEGIN Header_ADC_func */
/**
* @brief Function implementing the ADCtask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ADC_func */
void ADC_func(void const * argument)
{
  /* USER CODE BEGIN ADC_func */
  /* Infinite loop */
	uint8_t x1=21,y1=51;
	uint8_t x2=106,y2=51;
	uint8_t b1=21,b2=106;
	

	uint16_t ADC_Values[6]={0};
	HAL_ADCEx_Calibration_Start(&hadc1);
	osDelay(50);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_Values,6);
  for(;;)
  {
//		OLED_printf(2, 0,"%4d, %4d, %4d    ",ADC_Values[0],ADC_Values[1],ADC_Values[2]);
//		OLED_printf(3, 0,"%4d, %4d, %4d    ",ADC_Values[3],ADC_Values[4],ADC_Values[5]);
		
		// 画图
		eraser_point(b1,3);
		b1 = compute_bias(ADC_Values[1])+9+2;
		draw_point(b1,3);
		
		eraser_point(b2,3);
		b2 = 118-(compute_bias(ADC_Values[0])+2);
		draw_point(b2,3);
		
		eraser_point(x1,y1);
		x1 = compute_bias(ADC_Values[2])+9+2;
		y1 = 39+2+compute_bias(ADC_Values[3]);
		draw_point(x1,y1);
		
		eraser_point(x2,y2);
		x2 = compute_bias(ADC_Values[4])+9+85+2;
		y2 = 39+2+compute_bias(ADC_Values[5]);
		draw_point(x2,y2);
		
		OLED_refresh_gram();//全局刷新
		
		// 最后更新全局数据
		if( xSemaphoreTake(adc_semHandle,portMAX_DELAY)==pdPASS)
		{
			global_data.g_x1 = ADC_Values[2];
			global_data.g_x2 = ADC_Values[4];
			global_data.g_y1 = ADC_Values[3];
			global_data.g_y2 = ADC_Values[5];
			global_data.g_b1 = ADC_Values[1];
			global_data.g_b2 = ADC_Values[0];
			xSemaphoreGive(adc_semHandle);
		}
		else
		{
			continue;
		}
		
//		for(int i =0;i<6;i++)
//		{
//			OLED_printf(2, 0,"%d, %d\n",i,ADC_Values[i]);
//			//OLED_show_floatnum(4, 12, i, 0);
//			printf("%d, %d\n",i,ADC_Values[i]);
//			OLED_refresh_gram();//全局刷新
//		}
		//osDelay(100);
  }
  /* USER CODE END ADC_func */
}

/* USER CODE BEGIN Header_key_func */
/**
* @brief Function implementing the keytask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_key_func */
void key_func(void const * argument)
{
  /* USER CODE BEGIN key_func */
  /* Infinite loop */
	// 一共8+2+3的读取，用16位来表示，仅使用后13位
	// 后八位为key_left和key_right的表示
	// 前5位为switch和顶部key的表示
	uint16_t key_result=0;
	uint8_t tmp;
  for(;;)
  {
		key_result = 0;
		{
		// 左侧4个按键
		tmp = LKEY1;
		key_result |= (tmp==1 ? (1<<7) : 0);
		if(!tmp)
			draw_key_line(17,20,LFLAG);
		else
			bold_key_line(17,20,LFLAG);
		
		tmp = LKEY2;
		key_result |= (tmp==1 ? (1<<6) : 0);
		if(!tmp)
			draw_key_line(21,17,UFLAG);
		else
			bold_key_line(21,17,UFLAG);
		
		tmp = LKEY3;
		key_result |= (tmp==1 ? (1<<5) : 0);
		if(!tmp)
			draw_key_line(25,20,RFLAG);
		else
			bold_key_line(25,20,RFLAG);
		
		tmp = LKEY4;
		key_result |= (tmp==1 ? (1<<4) : 0);
		if(!tmp)
			draw_key_line(21,23,DFLAG);
		else
			bold_key_line(21,23,DFLAG);
		
		// 右侧4个按键
		tmp = RKEY1;
		key_result |= (tmp==1 ? (1<<3) : 0);
		if(!tmp)
			draw_key_line(17+85,20,LFLAG);
		else
			bold_key_line(17+85,20,LFLAG);
		
		
		tmp = RKEY2;
		key_result |= (tmp==1 ? (1<<2) : 0);
		if(!tmp)
			draw_key_line(21+85,17,UFLAG);
		else
			bold_key_line(21+85,17,UFLAG);
		
		
		tmp = RKEY3;
		key_result |= (tmp==1 ? (1<<1) : 0);
		if(!tmp)
			draw_key_line(25+85,20,RFLAG);
		else
			bold_key_line(25+85,20,RFLAG);
		
		tmp = RKEY4;
		key_result |= (tmp==1 ? (1<<0) : 0);
		if(!tmp)
			draw_key_line(21+85,23,DFLAG);
		else
			bold_key_line(21+85,23,DFLAG);
		
		// 顶部2个按键
		tmp = KEY_UP_L;
		key_result |= (tmp==0 ? (1<<9) : 0);
		if(tmp)
			draw_point(5,3);
		else
			eraser_point(5,3);
		
		tmp = KEY_UP_R;
		key_result |= (tmp==0 ? (1<<10) : 0);
		if(tmp)
			draw_point(122,3);
		else
			eraser_point(122,3);
	}
		
		// 3个开关
		key_result |= (SWITCH_TOTAL==1 ? (1<<13) : 0);
		
		key_result |= (SWITCH1==1 ? (1<<12) : 0);
		key_result |= (SWITCH2==1 ? (1<<11) : 0);
		
		// 绘制三个开关的显示
		if(!SWITCH1)
		{
			draw_point(36+2,17+2);
			draw_point(36+2+4,17+2);
			draw_point(36+2,17+2+4);
			draw_point(36+2+4,17+2+4);
			eraser_point(44+2,17+2);
			eraser_point(44+2+4,17+2);
			eraser_point(44+2,17+2+4);
			eraser_point(44+2+4,17+2+4);
		}
		else
		{
			eraser_point(36+2,17+2);
			eraser_point(36+2+4,17+2);
			eraser_point(36+2,17+2+4);
			eraser_point(36+2+4,17+2+4);
			draw_point(44+2,17+2);
			draw_point(44+2+4,17+2);
			draw_point(44+2,17+2+4);
			draw_point(44+2+4,17+2+4);
		}
		if(!SWITCH_TOTAL)
		{
			draw_point(55+2,17+2);
			draw_point(55+2+4,17+2);
			draw_point(55+2,17+2+4);
			draw_point(55+2+4,17+2+4);
			eraser_point(63+2,17+2);
			eraser_point(63+2+4,17+2);
			eraser_point(63+2,17+2+4);
			eraser_point(63+2+4,17+2+4);
		}
		else
		{
			eraser_point(55+2,17+2);
			eraser_point(55+2+4,17+2);
			eraser_point(55+2,17+2+4);
			eraser_point(55+2+4,17+2+4);
			draw_point(63+2,17+2);
			draw_point(63+2+4,17+2);
			draw_point(63+2,17+2+4);
			draw_point(63+2+4,17+2+4);
		}
		if(!SWITCH2)
		{
			draw_point(74+2,17+2);
			draw_point(74+2+4,17+2);
			draw_point(74+2,17+2+4);
			draw_point(74+2+4,17+2+4);
			eraser_point(82+2,17+2);
			eraser_point(82+2+4,17+2);
			eraser_point(82+2,17+2+4);
			eraser_point(82+2+4,17+2+4);
		}
		else
		{
			eraser_point(74+2,17+2);
			eraser_point(74+2+4,17+2);
			eraser_point(74+2,17+2+4);
			eraser_point(74+2+4,17+2+4);
			draw_point(82+2,17+2);
			draw_point(82+2+4,17+2);
			draw_point(82+2,17+2+4);
			draw_point(82+2+4,17+2+4);
		}
		
		
		// 最后更新全局数据
		if( xSemaphoreTake(key_semHandle,portMAX_DELAY)==pdPASS)
		{
			global_data.g_key_result = key_result;
			xSemaphoreGive(key_semHandle);
		}
		else
		{
			continue;
		}
		//printf("%x\n",key_result);
		//OLED_printf(4, 0,"%x",key_result);
		//OLED_refresh_gram();//全局刷新
		
    //osDelay(100);
  }
  /* USER CODE END key_func */
}

/* USER CODE BEGIN Header_iic_func */
/**
* @brief Function implementing the iictask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_iic_func */
void iic_func(void const * argument)
{
  /* USER CODE BEGIN iic_func */
  /* Infinite loop */
	float pos_x=630,pos_y=470;
	float x,y,x_t,y_t,z_t;
	draw_point(pos_x,pos_y);
  for(;;)
  {
		
		mpu_dmp_get_data(&x_t,&y_t,&z_t);
		//printf("x=%f y=%f\n",x,y);
		x = x_t;
		y = y_t;
		x = x>50?50:x;
		x = x<-50?-50:x;
		x = x/30;
		
		y = y>80?80:y;
		y = y<-80?-80:y;
		y = y/35;
		
		eraser_point((uint8_t)(pos_x/10),(uint8_t)(pos_y/10));
		pos_x-=y;
		pos_y+=x;
		
		pos_x = pos_x>=850?850:pos_x;
		pos_x = pos_x<=420?420:pos_x;
		
		pos_y = pos_y>=610?610:pos_y;
		pos_y = pos_y<=320?320:pos_y;
		
		draw_point((uint8_t)(pos_x/10),(uint8_t)(pos_y/10));
		
		//printf("x=%d y=%d\n",pos_x,pos_y);
		
		//OLED_printf(0, 0,"%.2f %.2f %.2f",x,y,z);
		//OLED_refresh_gram();//全局刷新
		// 最后更新全局数据
		if( xSemaphoreTake(iic_semHandle,portMAX_DELAY)==pdPASS)
		{
			global_data.g_pos_x = pos_x;
			global_data.g_pos_y = pos_y;
			global_data.g_x = x_t;
			global_data.g_y = y_t;
			xSemaphoreGive(iic_semHandle);
		}
		else
		{
			continue;
		}
     
  }
  /* USER CODE END iic_func */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

