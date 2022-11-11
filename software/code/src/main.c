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
	//使用模式1，16位定时器，使用"|"符号可以在使用多个定时器时不受影响	
	TMOD |= 0x01;

	//给定初值，这里使用定时器最大值从15536开始计数一直到65535溢出，周期50ms	     
	TH0 = READ_PS2_INTVAL_TIME_MS_H;
	TL0 = READ_PS2_INTVAL_TIME_MS_L;

	//总中断打开
	EA = 1; 
	//定时器中断打开
	ET0 = 1; 
	//定时器开关打开
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
	// 重新赋值，方式1是16位计数器，不能硬件重装初始值
	TH0 = READ_PS2_INTVAL_TIME_MS_H;
	TL0 = READ_PS2_INTVAL_TIME_MS_L;
	
	// read ps2 command and execute.
	receive_exe_cmd(); 
}