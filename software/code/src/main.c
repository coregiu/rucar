/**
  ******************************************************************************
  *
  * main function
  * author: coregiu
  * 
  * 
  ******************************************************************************
**/

#include <controller.h>

/* 65536 - 15536 = 50000us = 50ms*/
const uint READ_PS2_INTVAL_TIME_MS_H = 0x3C;
const uint READ_PS2_INTVAL_TIME_MS_L = 0xB0;

void delay_time_ms(uint mil_sec)
{
	uint i, j;
	for (i = mil_sec; i > 0; i--)
		for (j = 70; j > 0; j--)
			;
}

/**
 * init timer 0.
 */
void init_timer_0(void)
{
	//ʹ��ģʽ1��16λ��ʱ����ʹ��"|"���ſ�����ʹ�ö����ʱ��ʱ����Ӱ��	
	TMOD |= 0x01;

	//������ֵ������ʹ�ö�ʱ�����ֵ��15536��ʼ����һֱ��65535���������50ms	     
	TH0 = READ_PS2_INTVAL_TIME_MS_H;
	TL0 = READ_PS2_INTVAL_TIME_MS_L;

	//���жϴ�
	EA = 1; 
	//��ʱ���жϴ�
	ET0 = 1; 
	//��ʱ�����ش�
	TR0 = 1; 
}

void main()
{
	delay_time_ms(500);

	init_timer_0();
	init_modules();

	while (1)
	{

	}
}

/**
 * timer 0 interrupt function.
 */
void timer_0_isr(void) __interrupt 1 //R1 R0    0/1  0/1  4
{
	// ���¸�ֵ����ʽ1��16λ������������Ӳ����װ��ʼֵ
	TH0 = READ_PS2_INTVAL_TIME_MS_H;
	TL0 = READ_PS2_INTVAL_TIME_MS_L;
	
	// read ps2 command and execute.
	receive_exe_cmd(); 
}