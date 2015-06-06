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
 Date:   02.04.2012
 Email:  me@noro24.de
 File:   spi.h
 -----------------------------------------------------------------------------*/



#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <inttypes.h>

/*-----------------------------------------

SPI pins configuration

-----------------------------------------*/
#define SPI_PORT		PORTB
#define SPI_DDR			DDRB

#define SPI_MOSI		PB5
#define SPI_MISO		PB6
#define SPI_SCK			PB7
#define SPI_CS			PB4

uint8_t spi_rx();
void spi_tx(uint8_t byte);
void spi_init();


#endif /* SPI_H_ */