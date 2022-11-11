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
void init_timer(void)
{
	/*ʹ��ģʽ1��16λ��ʱ����ʹ��"|"���ſ�����ʹ�ö����ʱ��ʱ����Ӱ��*/
	TMOD |= 0x11;

	/*������ֵ������ʹ�ö�ʱ�����ֵ��15536��ʼ����һֱ��65535���������50ms*/
	TH0 = READ_PS2_INTVAL_TIME_MS_H;
	TL0 = READ_PS2_INTVAL_TIME_MS_L;

	TH1 = READ_PS2_INTVAL_TIME_MS_H;
 	TL1 = READ_PS2_INTVAL_TIME_MS_L;

	//���жϴ�
	EA = 1; 
	/* enable timer0 interrupt */
	ET0 = 1; 
	TR0 = 1; 
	/* enable timer1 interrupt */
	ET1=1; 
	TR1=1;  
}

void main()
{
	delay_time_ms(500);

	init_timer();
	init_modules();

	uart_log_start_info();
	while (1)
	{

	}
}

/**
 * timer 0 interrupt function.
 * read ps2 command and execute it by 50ms interval.
 */
void timer_0_isr(void) __interrupt 1 //R1 R0    0/1  0/1  4
{
	// ���¸�ֵ����ʽ1��16λ������������Ӳ����װ��ʼֵ
	TH0 = READ_PS2_INTVAL_TIME_MS_H;
	TL0 = READ_PS2_INTVAL_TIME_MS_L;
	
	// read ps2 command and execute.
	receive_exe_cmd(); 
}

/**
 * timer 1 interrupt function.
 * check motor status, if no motor command after 10 interval(500ms), stop the car.
 */
void timer_1_isr(void) __interrupt 3 //R1 R0    0/1  0/1  4
{
	TH1 = READ_PS2_INTVAL_TIME_MS_H;
	TL1 = READ_PS2_INTVAL_TIME_MS_L;

	// inspect motor status.
	inspect_motor_cmd(); 
}