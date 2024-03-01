
#ifndef __USER_H
#define __USER_H

#include "main.h"

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

} ;


void trans_func(struct Data d);
void trans_init(void);

#endif 
