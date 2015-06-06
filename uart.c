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
 Date:   09.04.2012
 Email:  me@noro24.de
 File:   uart.c
 -----------------------------------------------------------------------------*/

#include "uart.h"

/*-----------------------------------------------------
Sends a char to serial
-----------------------------------------------------*/
void putch( char c )
{
  while( (UCSRA & 1<<UDRE) == 0 );
  UDR = c;
}

/*-----------------------------------------------------
Sends a string 's' to serial
-----------------------------------------------------*/
void putstr( char *s )
{
  while( *s )
    putch( *s++ );
}


/*-----------------------------------------------------
Initialize the serial interface
-----------------------------------------------------*/
void init_uart()
{
  
  	//Enable TXEN im Register UCR TX-Data Enable
	UCSRB =(1 << TXEN);
	UBRRL=(F_CPU / (BAUD * 16L) - 1);
  
}  

/*-----------------------------------------------------
Send a fromatted string to serial
fmt - format,
... - arguments (printf alike)
-----------------------------------------------------*/
void sput(char *fmt, ... )
{
        char buf[128]; // a string of max 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 127, fmt, args);
        va_end (args);
        putstr(buf);
}


	