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
 File:   sd.c
 -----------------------------------------------------------------------------*/


#include "spi.h"
#include "sd.h"
#include "globals.h"
/*-------------------------------------------------------------------------
Sends a commend to sd card controller
command - command id
arg     - command arguments as dword
crc     - checksum byte 
--------------------------------------------------------------------------*/ 
void sd_command(uint8_t command, uint32_t arg, uint8_t crc)
{
    spi_tx(0xff);
    spi_tx(0b01000000 | command);
    spi_tx(arg >> 24);
	spi_tx(arg >> 16);
	spi_tx(arg >> 8);
	spi_tx(arg);
    spi_tx(crc);
    spi_rx();
}
 
 
/*-------------------------------------------------------------------------
Initialize the SD card controller
--------------------------------------------------------------------------*/ 
uint8_t sd_init()
{
    
    uint16_t count = 0; 
    SPI_PORT |= 1<<SPI_CS; // unselect chip
	
	// more than 75 clocks (50*8=400)?
    for ( uint8_t i = 0; i < 50; i++) {
        spi_tx(0xff);
    }
	
    SPI_PORT &= ~(1<<SPI_CS); // select chip
	
    _delay_ms(1);
	// send command 0 to sd card controller
    sd_command(CMD0_GO_IDLE_STATE, 0, 0x95);
    count = 0;
    while ((spi_rx() != 1) )
	{
		count++;	
		if (count >= NO_TRIES) 
	       return M_ERR_TIMEOUT_0;
    };		
    
    // send command 1 to sd card controller
    sd_command(CMD1_SEND_OP_COND, 0, 0xff);
    count = 0;
    while ((spi_rx() != 0)) {
        sd_command(CMD1_SEND_OP_COND, 0, 0xff);
        count++;
		if (count >= NO_TRIES)
			return M_ERR_TIMEOUT_1;
    }
    
	// send command 16 to sd card controller
    sd_command(CMD16_SET_BLOCKLEN, MAX_BUF_SIZE, 0xff);
    count = 0;
    while ((spi_rx() != 0))
	{
		count++;
		if (count >= NO_TRIES) 
			return M_ERR_TIMEOUT_16;
	
	}		
    
    _delay_ms(DELAY_MS);
    SPCR &= ~(1<<SPR1);  //increase SPI clock from f/32 to f/2
	
		
    return M_OK;
}
 
 
 
/*-------------------------------------------------------------------------
Reads a partition sector (512) into rx_buffer with CMD17
--------------------------------------------------------------------------*/ 
void sd_read_sector(uint32_t sector, uint8_t* rx_buffer)
{
    uint16_t i;
    sector *= BYTES_PER_SECTOR; // address in bytes
    sd_command(CMD17_READ_SINGLE_BLOCK, sector, 0xff);
    while (spi_rx() != 0);    // R1 response
    while (spi_rx() != 0xfe); // response data token for command 17 "read block"
    for(i = 0; i < MAX_BUF_SIZE; i++)  // data packet
		rx_buffer[i] = spi_rx();
    spi_tx(0xff);
    spi_tx(0xff);
}
 



