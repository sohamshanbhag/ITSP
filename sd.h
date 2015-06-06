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
 File:   sd.h
 -----------------------------------------------------------------------------*/



#ifndef SD_H_
#define SD_H_

#define M_OK					0
#define M_ERR_TIMEOUT_0			1
#define M_ERR_TIMEOUT_1			2
#define M_ERR_TIMEOUT_16		3
#define M_ERR_NOT_FAT16			4

/*  sd command structure
	----------------------
	
	idx  | Arg3 Arg2 Arg1 Arg0			| crc
	-------------------------------------------
	0    |  0    0    0    0			| 0x95
	-------------------------------------------
	1    |  0    0    0    0			| 0xff
	-------------------------------------------
	16   |  block len (4 bytes)			| 0xff
	-------------------------------------------
	17   |  block address (4 bytes = )	| 0xff
	-------------------------------------------
*/

#define CMD0_GO_IDLE_STATE			0 // software reset
#define CMD1_SEND_OP_COND			1 // init
#define CMD16_SET_BLOCKLEN			16 // change block size 
#define CMD17_READ_SINGLE_BLOCK		17 // read single block

#define DELAY_MS				10
#define NO_TRIES				1000

#define MAX_BUF_SIZE			512


#define BYTES_PER_SECTOR			512	

uint8_t sd_init();
void sd_read_sector(uint32_t sector, uint8_t* rx_buffer);


#endif /* SD_H_ */