/*
 * Day2_Task03.c
 *
 * Created: 2026-07-29 오후 7:12:28
 * Author : dhcho
 */ 
#define F_CPU 16000000
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "clcd.h"
#include "i2c.h"

int A=1;
int B=1;
char circulate[4]={'+','-','*','/'};
int circul_count=0;
int result=2;
int decimal=0;
char temp[6];

int main(void)
{	DDRD = 0x00;
	DDRE = 0x00;
	PORTD = 0xFF;   // 풀업 활성화
	PORTE = 0xFF;   // 풀업 활성화
	EIMSK=0b00111100;
	EICRA = 0xA0;
	EICRB = 0b00001010;
	sei();
	i2c_lcd_init();
    /* Replace with your application code */
    while (1) 
    {	
		i2c_lcd_goto_XY(0,0);
		sprintf(temp,"%-3d",A);
		i2c_lcd_write_string(temp);
		i2c_lcd_goto_XY(0,3);
		char op_str[2];
		op_str[0] = circulate[circul_count];
		op_str[1] = '\0';
		i2c_lcd_write_string(op_str);
		i2c_lcd_goto_XY(0,4);
		sprintf(temp,"%-3d",B);
		i2c_lcd_write_string(temp);
		i2c_lcd_goto_XY(0,7);
		i2c_lcd_write_string("=");
		_delay_ms(100);
		i2c_lcd_goto_XY(0,8);
		sprintf(temp,"%-3d",result);
		i2c_lcd_write_string(temp);
		if (decimal!=0){
			i2c_lcd_goto_XY(0,11);
			i2c_lcd_write_string(".");
			i2c_lcd_goto_XY(0,12);
			sprintf(temp,"%-3d",decimal);
			i2c_lcd_write_string(temp);
		}
		else{
			i2c_lcd_goto_XY(0,11);
			i2c_lcd_write_string("     ");
		}

		
    }
}
ISR(INT4_vect){
	A++;
}
ISR(INT5_vect){
	circul_count = (circul_count + 1) % 4;
}
ISR(INT2_vect){
	B++;
}
ISR(INT3_vect){
	switch (circulate[circul_count]){
		case '+':
			result=A+B;
			decimal=0;
			break;
		case '-':
			result=A-B;
			decimal=0;
			break;
		case '*':
			result=A*B;
			decimal=0;
			break;
		case '/':
			result=A/B;
			decimal=A%B;
			break;
		default:
			break;
	}

}

