/*----------------------------------------------------------------------------
Copyright (c) 2012, noro24.de
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the noro24.de.
4. Neither the name of the noro24.de nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY noro24.de ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL noro24.de BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------*/ 
/*-----------------------------------------------------------------------------
 BSD License
 Author: noro24.de
 Date:   22.03.2012
 Email:  me@noro24.de
 File:   player.c
 -----------------------------------------------------------------------------*/


#include "player.h"
#include "fat16.h"
#include "uart.h"


volatile unsigned char is_buf1_empty, is_buf2_empty = 0;
register int sample_count asm("r2");
register char switch_buffer asm("r5");

// play buffer and back buffer
uint8_t buffer1[PLAY_BUFFER_SIZE], buffer2[PLAY_BUFFER_SIZE];

extern uint16_t CLUSTER;


uint8_t lock = 0;

#define DBG 1




/*-------------------------------------------------------------------------
Timer 1 interrupt with sampling frequency e.g. 22050 Hz)
--------------------------------------------------------------------------*/ 
ISR(TIMER1_COMPA_vect)
{
	
 #if defined (__AVR_ATmega32__)
   if(switch_buffer == 1)
		OCR2 = buffer1[sample_count++];
   else
		OCR2 = buffer2[sample_count++];
   if(sample_count >= PLAY_BUFFER_SIZE) {
		if(switch_buffer)
			is_buf1_empty = 1;
		else
			is_buf2_empty = 1;
	switch_buffer ^= 1;
	sample_count = 0;
   }
 #endif
 
}


/*-------------------------------------------------------------------------
Plays a raw PCM-file with name 'name' and extention 'ext'
name    - name of the audio file
ext     - extention e.g. 'raw'
--------------------------------------------------------------------------*/ 
void play_file(char *name, char* ext) 
{
	directory_entry_t* file = NULL;
	switch_buffer = 0; sample_count = 0;
	
	file = file_find(name,ext);
		
	if( file != NULL ){
		
		CLUSTER = file->first_cluster_lo;
		uint16_t block_no = file->size >> 9; 
		
		// start timers and sets the output, play
		audio_on();
		
		lock = 1;
		
		for( uint16_t i=0; i < block_no + 1; i++) {
			
			while((!is_buf1_empty) && (!is_buf2_empty));
			if(is_buf1_empty) {
				file_read_block(file, buffer1, i);
				is_buf1_empty = 0;
			} else if(is_buf2_empty) {
				file_read_block(file, buffer2, i);
				is_buf2_empty = 0;
			}
		}			
			
		// stops the timers , stop 
		audio_off();
		lock = 0;
	}else
		sput("%s","file not found!\n");		
			
	
}	


/*-------------------------------------------------------------------------
Initialize the timer2 for PWM and seet the speaker/amp output
--------------------------------------------------------------------------*/ 
void init_pwm()
{
	// Fast PWM, no prescaler
	// timer 2 is used to generate the PWM frequency of the sample  
	TCCR2|=(1<<WGM20)|(1<<WGM21)|(1<<COM21)|(1<<CS20);
    
	SPEAKER_DDR |=(1<<SPEAKER);
	SPEAKER_OFF;
	
}



/*-------------------------------------------------------------------------
Set the timer1 with the sample frecvency e.g. 22050 Hz
--------------------------------------------------------------------------*/ 
void audio_on(void)
{
 // CTC Mode, prescaler 8 
 // timer 1 is used to play at the sample rate e.g. 22050 Hz
 TCCR1A = (0<<COM1A1) | (0<<COM1A0) | (0<<WGM11) | (0<<WGM10);
 TCCR1B = (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
 OCR1A = SAMPLE_OCR_COUNTER-2;
  
	
 SPEAKER_DDR |= (1<<SPEAKER);
 SPEAKER_ON;


#if defined (__AVR_ATmega32__)
 TIMSK |= (1<<OCIE1A);
 TIFR  |= (1<<OCF1A); 
#endif
}


/*-------------------------------------------------------------------------
Set the speaker output and timer 1 off
--------------------------------------------------------------------------*/ 
void audio_off(void)
{
	
	SPEAKER_OFF;
	OCR2 = 255; // PWM to null
#if defined (__AVR_ATmega32__)
 TIMSK &= ~(1<<OCIE1A);
#endif
}


