/*
 * robit_avr_day1.c
 *
 * Created: 2026-07-28 오전 11:18:08
 * Author : dhcho
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF;
	DDRD = 0x00;
	
	EIMSK = 0b00001100;
	EICRA = 0x02;
	
	
	sei();
	
	int count=0;
    while (1) {
		
		if ((!(PIND & (1<<PIND0)))&&(!(PIND & (1<<PIND1)))){
			PORTA=0x00;
		_delay_ms(500);}
		else if (!(PIND & (1<<PIND0))){
			PORTA=0x0F;
			_delay_ms(500);
		}
		else if (!(PIND & (1<<PIND1))){
			PORTA=0xF0;
			_delay_ms(500);
		}
		
		else{
			if (count==0){
				count=1;
				PORTA=0x00;
			}
			else if (count!=0){
				count=0;
				PORTA=0xFF;
			}
			_delay_ms(500);
		}
		
		
		
	}
}

ISR(INT2_vect){
	int16_t temp;
	for (temp =0x01;temp!=0b10000000;temp=temp<<1){
		PORTA=~temp;
		_delay_ms(500);
	}
	PORTA=~temp;
	_delay_ms(500);
	
}
ISR(INT3_vect){
	int16_t temp;
	for (temp =0b10000000;temp!=0b00000001;temp=temp>>1){
		PORTA=~temp;
		_delay_ms(500);
	}
	PORTA=~temp;
	_delay_ms(500);
}

