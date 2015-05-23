/*
1 - * * - 2
3 - * * - 4
5 - * * - 6
*/

# include <avr/io.h>
# include <util/delay.h>



int main(){
	DDRD = 0b00111111;
	PORTD = 0b00000000;

	char chr[52], a;

	for(int i = 0; i < 26; i++){
		if(i%2 == 0){
			chr[i] = 65+(i/2);
		}
		else chr[i] = " "; 
	}

	int i = 0;

	while(1){

		a = chr[i%52];
		
		switch(a){
			case "A" : PORTD = 0b00000001; break;
			case "B" : PORTD = 0b00000101; break;
			case "C" : PORTD = 0b00000011; break;
			case "D" : PORTD = 0b00001011; break;
			case "E" : PORTD = 0b00001001; break;
			case "F" : PORTD = 0b00000111; break;
			case "G" : PORTD = 0b00001111; break;
			case "H" : PORTD = 0b00001101; break;
			case "I" : PORTD = 0b00000110; break;
			case "J" : PORTD = 0b00001110; break;
			case "K" : PORTD = 0b00010001; break;
			case "L" : PORTD = 0b00010101; break;
			case "M" : PORTD = 0b00010011; break;
			case "N" : PORTD = 0b00011011; break;
			case "O" : PORTD = 0b00011001; break;
			case "P" : PORTD = 0b00010111; break;
			case "Q" : PORTD = 0b00011111; break;
			case "R" : PORTD = 0b00011101; break;
			case "S" : PORTD = 0b00010110; break;
			case "T" : PORTD = 0b00011110; break;
			case "U" : PORTD = 0b00110001; break;
			case "V" : PORTD = 0b00110101; break;
			case "W" : PORTD = 0b00101110; break;
			case "X" : PORTD = 0b00110011; break;
			case "Y" : PORTD = 0b00111011; break;
			case "Z" : PORTD = 0b00111001; break;
			case " " : PORTD = 0b00000000; break;
		}
		i++;
		_delay_ms(2000);
	}

}
