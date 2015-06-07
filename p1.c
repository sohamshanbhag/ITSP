/*
1 - * * - 2
3 - * * - 4
5 - * * - 6
*/

#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"
#include "sd.h"
#include "fat16.h"
#include "player.h"
#include "uart.h"



int main(){

	init_uart();
	spi_init();
	
	
	INPUT_CFG;
	INPUT_ON;
	
	init_pwm();
	
	sei();

	sd_init();

	fat16_init();

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
			case 'A' : PORTD = 0b01000000; play_file(a,"raw"); break;
			case 'B' : PORTD = 0b01010000; play_file(a,"raw"); break;
			case 'C' : PORTD = 0b01100000; play_file(a,"raw"); break;
			case 'D' : PORTD = 0b01101000; play_file(a,"raw"); break;
			case 'E' : PORTD = 0b01001000; play_file(a,"raw"); break;
			case 'F' : PORTD = 0b01110000; play_file(a,"raw"); break;
			case 'G' : PORTD = 0b01111000; play_file(a,"raw"); break;
			case 'H' : PORTD = 0b01011000; play_file(a,"raw"); break;
			case 'I' : PORTD = 0b00110000; play_file(a,"raw"); break;
			case 'J' : PORTD = 0b00111000; play_file(a,"raw"); break;
			case 'K' : PORTD = 0b01000100; play_file(a,"raw"); break;
			case 'L' : PORTD = 0b01010100; play_file(a,"raw"); break;
			case 'M' : PORTD = 0b01100100; play_file(a,"raw"); break;
			case 'N' : PORTD = 0b01101100; play_file(a,"raw"); break;
			case 'O' : PORTD = 0b01001100; play_file(a,"raw"); break;
			case 'P' : PORTD = 0b01110100; play_file(a,"raw"); break;
			case 'Q' : PORTD = 0b01111100; play_file(a,"raw"); break;
			case 'R' : PORTD = 0b01011100; play_file(a,"raw"); break;
			case 'S' : PORTD = 0b00110100; play_file(a,"raw"); break;
			case 'T' : PORTD = 0b00111100; play_file(a,"raw"); break;
			case 'U' : PORTD = 0b01000110; play_file(a,"raw"); break;
			case 'V' : PORTD = 0b01010110; play_file(a,"raw"); break;
			case 'W' : PORTD = 0b00111010; play_file(a,"raw"); break;
			case 'X' : PORTD = 0b01100110; play_file(a,"raw"); break;
			case 'Y' : PORTD = 0b01101110; play_file(a,"raw"); break;
			case 'Z' : PORTD = 0b01001110; play_file(a,"raw"); break;
			case ' ' : PORTD = 0b00000000; play_file(a,"raw"); break;
		}
		j++;
		_delay_ms(500);
	}

}
