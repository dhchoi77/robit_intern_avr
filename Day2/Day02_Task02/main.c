/*
 * avr_day2_task2.c
 *
 * Created: 2026-07-29 오후 2:12:52
 * Author : dhcho
 */ 
#define F_CPU 16000000
#include <stdio.h>
#include <avr/io.h>
#include "i2c.h"
#include "clcd.h"
#include <avr/interrupt.h>
#include <util/delay.h>

int print_lcd();
void print_led();

int main(void)
{	DDRF =0x00;				//입력설정
	DDRA = 0xFF;			//출력설정
	ADMUX = 0x40;			//PF0의 전압 측정과 avcc를 기준으로 하겠다.
	ADCSRA = 0x87;			//adc활성화 및 분주비 128로 설정
	
	SREG = 0x80;
	
	/* Replace with your application code */
	i2c_lcd_init();
	while (1)
	{	print_lcd();
		print_led();
		
	}
	
}

int print_lcd(){
	unsigned int adcValue =0;		//adc값을 받아올 변수(0~1023)
	char adcValue_print[5];			//읽어온 adc값을 lcd에 출력할 문자열
	unsigned char chaneel =0x00;
	ADMUX = 0x40 | chaneel;
	ADCSRA |=0x40;
	while((ADCSRA&0x10)==0);		//변환완료될때까지 기다리기
	adcValue =ADC;
	sprintf(adcValue_print,"%-4d",adcValue);		
	i2c_lcd_goto_XY(0,0);
	i2c_lcd_write_string("21th CDH");		//이니셜 출력
	i2c_lcd_goto_XY(1,0);
	i2c_lcd_write_string(adcValue_print);	//adc값 출력(0~1023)
	i2c_lcd_goto_XY(1,7);
	int adcValue_float=adcValue;
	adcValue_float=adcValue_float*5/1023;	//adc값을 전압으로 변경하기
	sprintf(adcValue_print,"%1d",adcValue_float);
	i2c_lcd_write_string(adcValue_print); //출력하기(소수점 위)
	i2c_lcd_goto_XY(1,8);
	i2c_lcd_write_string(".");
	i2c_lcd_goto_XY(1,9);
	long adcValue_float1=adcValue;
	adcValue_float1=adcValue_float1*5%1023;		//소수점 아래를 구하기 위해서 나머지 구하기
	adcValue_float1=adcValue_float1*100/1023;	//나머지 값이 0~1022사이이기 때문에 0~99사이로 변환해주기
	adcValue_float=adcValue_float1;
	sprintf(adcValue_print,"%-2d",adcValue_float);
	i2c_lcd_write_string(adcValue_print);		//출력하기 (소수점 아래)
	_delay_ms(100);
	
	return ADC;
}
//전압에 따라 led 출력해주기
void print_led(){
	int adc=ADC;
	adc/=127;		//adc값을 0~8사이로 만들어 주기
	switch (adc){
		case 8:
			PORTA=0x00;
			break;
		case 7:
			PORTA=0b10000000;
			break;
		case 6:
			PORTA=0b11000000;
			break;
		case 5:
			PORTA=0b11100000;
			break;
		case 4:
			PORTA=0b11110000;
			break;
		case 3:
			PORTA=0b11111000;
			break;
		case 2:
			PORTA=0b11111100;
			break;
		case 1:
			PORTA=0b11111110;
			break;
		case 0:
			PORTA=0b11111111;
			break;
		default:
			break;
			
	}
	_delay_ms(100);
}

