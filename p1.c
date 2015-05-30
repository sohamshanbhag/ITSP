/*
1 - * * - 2
3 - * * - 4
5 - * * - 6
*/

# include <avr/io.h>
# include <util/delay.h>



int main(){
	DDRD = 0b01111110;
	PORTD = 0b00000000;

	char chr[52], a;

	int i = 0;

	for(i = 0; i < 52; i++){
		if(i%2 == 0){
			chr[i] = 65+(i/2);
		}
		else chr[i] = ' '; 
	}

	int j = 0;

	while(1){

		a = chr[j%52];
		
		switch(a){
			case 'A' : PORTD = 0b01000000; break;
			case 'B' : PORTD = 0b01010000; break;
			case 'C' : PORTD = 0b01100000; break;
			case 'D' : PORTD = 0b01101000; break;
			case 'E' : PORTD = 0b01001000; break;
			case 'F' : PORTD = 0b01110000; break;
			case 'G' : PORTD = 0b01111000; break;
			case 'H' : PORTD = 0b01011000; break;
			case 'I' : PORTD = 0b00110000; break;
			case 'J' : PORTD = 0b00111000; break;
			case 'K' : PORTD = 0b01000100; break;
			case 'L' : PORTD = 0b01010100; break;
			case 'M' : PORTD = 0b01100100; break;
			case 'N' : PORTD = 0b01101100; break;
			case 'O' : PORTD = 0b01001100; break;
			case 'P' : PORTD = 0b01110100; break;
			case 'Q' : PORTD = 0b01111100; break;
			case 'R' : PORTD = 0b01011100; break;
			case 'S' : PORTD = 0b00110100; break;
			case 'T' : PORTD = 0b00111100; break;
			case 'U' : PORTD = 0b01000110; break;
			case 'V' : PORTD = 0b01010110; break;
			case 'W' : PORTD = 0b00111010; break;
			case 'X' : PORTD = 0b01100110; break;
			case 'Y' : PORTD = 0b01101110; break;
			case 'Z' : PORTD = 0b01001110; break;
			case ' ' : PORTD = 0b00000000; break;
		}
		j++;
		_delay_ms(500);
	}

}
