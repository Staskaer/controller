#include "user.h"
#include "stdio.h"
#include "key_led.h"

/*
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
// 
// 角度x的范围为(-50, +50) 角度y的范围为(-80, +80)
float g_pos_x,g_pos_y;
float g_x,g_y;

};
*/


// 此函数会在开始时调用，可以用于通过串口配置模块功能
void trans_init()
{
//	printf("start!\n");
//	LED1_Toggle;
//	LED2_Toggle;
};


// 此函数会在完成数据同步后调用，用于给串口发送数据
void trans_func(struct Data d)
{
	/*
	Data d中为当前状态的各个参数，修改此函数可以完成需要的数据的修改功能
	printf可以用于向串口发送数据
	
	其中Data中参数含义如下：
	
	**********************************************************************************************
	g_x1, g_y1 左摇杆的x、y数值，摇杆不动时为2048，最大值为4096，摇杆在最左端时g_x1=0 最上端时g_y1=0
	g_x2, g_y2 右摇杆的x、y数值，摇杆不动时为2048，最大值为4096，摇杆在最左端时g_x1=0 最上端时g_y1=0
	g_b1, g_b2 顶部电位器，b1为左侧，b2为右侧，电位器越向中间滑动数值越大，向两侧滑动数值越小
	
	
	**********************************************************************************************
	g_key_result 是一个16位的整型 每一位表示按键是否被按下，当按下时对应的位即为1，具体每一位含义如下
	第0至3位：表示右侧四个按键，0-3位分别是下右上左
	第4至7位：表示左侧四个按键，4-7位分别是下右上左
	第9位和第10位分别为左侧和右侧的顶部按键
	第11位为三个开关中右侧的那个开关的状态(开关位于左侧为0 位于右侧为1)
	第12位为三个开关中左侧的那个开关的状态(开关位于左侧为0 位于右侧为1)
	第13位为三个开关中中间的那个开关的状态(开关位于左侧为0 位于右侧为1)
	
	获取第i位可以使用 d.g_key_result &(0x1<<i)
	
	
	**********************************************************************************************
	g_pos_x, g_pos_y 表示一个位于屏幕中心的质点，将mpu6050两个轴的数据看作速度时的移动情况，可以用于表示mpu6050的累计作用效果
	其数值为浮点类型  pos_x的范围为[420,850] pos_y的范围为[320, 610]
	
	g_x, g_y 表示当前mpu6050的读数，浮点类型，角度x的范围为(-50, +50) 角度y的范围为(-80, +80)
	
	
	*/
	
	// 下面简单示例，当左摇杆在上、左、右时会对应发送 w a d
	if(d.g_y1<1000)
		printf("w");
	else if(d.g_x1<1000)
		printf("a");
	else if(d.g_x1>3900)
		printf("d");
}

/*

另外，存在以下的宏可以用于LED显示，其中LED1和LED2仅在焊接上后才有效

*************板载LED控制*************

#define Board_LED_ON HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1)
#define Board_LED_OFF HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1)
#define Board_LED_Toggle HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin)

*************LED1控制*************

#define LED1_ON HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1)
#define LED1_OFF HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0)
#define LED1_Toggle HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)

*************LED2控制*************

#define LED2_ON HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1)
#define LED2_OFF HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 0)
#define LED2_Toggle HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin)
*/

