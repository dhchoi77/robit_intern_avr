#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main (void){
	
	DDRA = 0xFF;
	DDRD = 0x00;

	PORTA = 0xFF;
	
	EIMSK = 0b00001111;
	EICRA = 0x02;
	
	sei();
	
	while(1){
		if (PORTA==0x00){
			PORTA=0xFF;
			_delay_ms(100);
		}
		else{
			PORTA=PORTA-1;
			_delay_ms(100);
		}
	}
}
ISR (INT0_vect){
	int16_t temp=0b11100000;
	for (int i=0;i<6;i++){
		PORTA=~temp;
		temp=temp>>1;
		_delay_ms(300);
	}
}
ISR (INT1_vect){
	int16_t temp=0b00000111;
	for (int i=0;i<6;i++){
		PORTA=~temp;
		temp=temp<<1;
		_delay_ms(300);
	}
}
ISR(INT2_vect){
	int16_t temp=0b00000001;
	for (int i=0;i<8;i++){
		PORTA=~temp;
		temp=temp<<1;
		_delay_ms(100);
	}
	for (int i=0;i<8;i++){
		temp=temp>>1;
		PORTA=~temp;
		_delay_ms(100);
	}
}
ISR(INT3_vect){
	PORTA=0xFF;
}