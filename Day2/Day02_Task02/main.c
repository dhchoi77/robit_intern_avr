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
{	DDRF =0x00;
	DDRA = 0xFF;
	ADMUX = 0x40;
	ADCSRA = 0x87;
	
	SREG = 0x80;
	
	/* Replace with your application code */
	i2c_lcd_init();
	while (1)
	{	print_lcd();
		print_led();
		
	}
	
}

int print_lcd(){
	unsigned int adcValue =0;
	char adcValue_print[5];
	unsigned char chaneel =0x00;
	ADMUX = 0x40 | chaneel;
	ADCSRA |=0x40;
	while((ADCSRA&0x10)==0);
	adcValue =ADC;
	sprintf(adcValue_print,"%-4d",adcValue);
	i2c_lcd_goto_XY(0,0);
	i2c_lcd_write_string("21th CDH");
	i2c_lcd_goto_XY(1,0);
	i2c_lcd_write_string(adcValue_print);
	i2c_lcd_goto_XY(1,7);
	int adcValue_float=adcValue;
	adcValue_float=adcValue_float*5/1023;
	sprintf(adcValue_print,"%1d",adcValue_float);
	i2c_lcd_write_string(adcValue_print);
	i2c_lcd_goto_XY(1,8);
	i2c_lcd_write_string(".");
	i2c_lcd_goto_XY(1,9);
	long adcValue_float1=adcValue;
	adcValue_float1=adcValue_float1*5%1023;
	adcValue_float1=adcValue_float1*100/1023;
	adcValue_float=adcValue_float1;
	sprintf(adcValue_print,"%-2d",adcValue_float);
	i2c_lcd_write_string(adcValue_print);
	_delay_ms(100);
	
	return ADC;
}
void print_led(){
	int adc=ADC;
	adc/=127;
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

