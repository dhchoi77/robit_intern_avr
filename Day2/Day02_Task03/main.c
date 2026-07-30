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

int A=1;		//앞에 숫자
int B=1;		//뒤에 숫자
char circulate[4]={'+','-','*','/'};		//연산부호
int circul_count=0;		//연산부호의 인덱스
int result=2;		//결과값
int decimal=0;		//결과값의 소수점
char temp[6];		//숫자의 출력을 위한 숫자를 저장할 임시 문자열

int main(void)
{	DDRD = 0x00;		//입력설정(PD2,3)
	DDRE = 0x00;		//출력설정(PE0,1)
	PORTD = 0xFF;   // 풀업 활성화  
	PORTE = 0xFF;   // 풀업 활성화
	EIMSK=0b00111100;	//INT4,5,2,3을 인터럽트 설정
	EICRA = 0xA0;		//INT2,3을 falling edge로 설정
	EICRB = 0b00001010;	//INT4,5를 falling edge로 설정
	sei();
	i2c_lcd_init();
    /* Replace with your application code */
    while (1) 
    {	
		i2c_lcd_goto_XY(0,0);	//출력할 위치로 이동
		sprintf(temp,"%-3d",A);	//lcd에 출력 형식이 문자열 밖에 없어서 자료 형태 바꾸기
		i2c_lcd_write_string(temp);
		i2c_lcd_goto_XY(0,3);
		char op_str[2];		//lcd 출력에 문자열만 들어갈 수 있어서 연산부호를 담는 문자열
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
		if (decimal!=0){		//소수점에 숫자가 들어있다면 "."과 소수점을 출력하기
			i2c_lcd_goto_XY(0,11);
			i2c_lcd_write_string(".");
			i2c_lcd_goto_XY(0,12);
			sprintf(temp,"%-3d",decimal);
			i2c_lcd_write_string(temp);
		}
		else{					//소수점에 숫자가 0이라면 +,-,* 연산을 한 값이 들어있다는 것이기 때문에 lcd의 소수점이 출력되는 곳을 클리어 하기
			i2c_lcd_goto_XY(0,11);
			i2c_lcd_write_string("     ");
		}

		
    }
}
ISR(INT4_vect){
	A++;
}
ISR(INT5_vect){
	circul_count = (circul_count + 1) % 4;		//count가 5이상으로 가면 문자열 범위를 벗어나므로 초기화도 같이 
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
		case '/':		//소수점도 같이 구해 주기
			result=A/B;
			decimal=A%B;
			break;
		default:
			break;
	}

}

