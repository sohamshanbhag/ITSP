# include <avr/io.h>
# include <util/delay.h>

int main(){
	DDRD = 0x40;
	PORTD = 0b00000000;

	while(1){
		PORTD = PIND^(1<<PIND6);
		_delay_ms(1000);
	}
}