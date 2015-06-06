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
 File:   player.h
 -----------------------------------------------------------------------------*/




#ifndef PLAYER_H_
#define PLAYER_H_


#include "globals.h"


#define SAMPLE_RATE				22050
#define PRESCALER				8

#define SAMPLE_OCR_COUNTER		((F_CPU / PRESCALER) / SAMPLE_RATE) - 1


#define PLAY_BUFFER_SIZE		512

// configure the pins for speaker
#define SPEAKER_DDR				DDRD
#define SPEAKER					PD7 // PD7
#define SPEAKER_PORT			PORTD


#define SPEAKER_ON				SPEAKER_PORT |= (1<<SPEAKER); 
#define SPEAKER_OFF				SPEAKER_PORT &= ~(1<<SPEAKER); 





// prototypes
void play_file(char *name, char* ext); 
void audio_on(void);
void audio_off(void);
void init_pwm();



#endif /* PLAYER_H_ */