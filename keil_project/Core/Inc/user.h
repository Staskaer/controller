#ifndef __USER_H
#define __USER_H
#include "main.h"


struct Data
{
// ADC�������ݣ�x1��y1�����ֱ���x��yֵ��ҡ�����м�ʱ�����߾�Ϊ2048����
// x2��y2�����ֱ���x��yֵ��ҡ�����м�ʱ�����߾�Ϊ2048����
// b1 b2�Ƕ�������������λ������λ�����м���תʱ����ֵ������
uint16_t g_x1, g_x2, g_y1, g_y2, g_b1, g_b2;

// һ��8+2+3�Ķ�ȡ����16λ����ʾ����ʹ�ú�13λ
// ���λΪkey_left��key_right�ı�ʾ
// ǰ5λΪswitch�Ͷ���key�ı�ʾ
uint16_t g_key_result;

// ��ʾλ�ú͵�ǰ��x��y�����ϵĽǶ�
// pos_x�ķ�ΧΪ[420,850] pos_y�ķ�ΧΪ[320, 610]
// �Ƕ�x�ķ�ΧΪ(-50, +50) �Ƕ�y�ķ�ΧΪ(-80, +80)
float g_pos_x,g_pos_y;
float g_x,g_y;

};


// �������ó�ʼ������
void trans_init(void);

// ��ɷ��͹��ܵĺ���
void trans_func(struct Data d);

#endif
