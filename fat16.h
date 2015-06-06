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
 
 fat16.h
 -----------------------------------------------------------------------------*/



#ifndef FAT16_H_
#define FAT16_H_

#include <inttypes.h>

typedef struct S_FAT16_BOOT_RECORD
{
	uint8_t jum_code[3];					//3 Bytes, 0x00
	uint8_t oem_id[8];						//8 Bytes, 0x03
	uint16_t bytes_per_sector;				//1 Word, 0x0b
	uint8_t	sectors_per_cluster;			//1 Byte, 0x0d
	uint16_t reserved_sectors;				//1 Word	0Eh	
	uint8_t no_of_fat;						//1 Byte 10h	
	uint16_t max_roots;						//1 Word 11h	
	uint16_t total_sectors;					//1 Word 13h	
	uint8_t  media_type;					//1 Byte 15h (F8h for Hard Disks)	
	uint16_t sectors_per_fat;				//1 Word 16h	
	uint16_t sectors_per_track;				//1 Word 18h	
	uint16_t no_of_heads;					//1 Word 1Ah	
	uint32_t no_of_hidden_sectors;			//1 Double Word 1Ch	
	uint32_t no_of_sectors;					//1 Double Word 20h	
	uint16_t logical_drive_no;				//1 Word 24h	
	uint8_t  signature;						//1 Byte 26h	(29h)
	uint32_t serial_no;						//1 Double Word 27h	
	uint8_t volume[11];						//11 Bytes 2Bh	
	uint8_t fat_name[8];					//8 Bytes 36h	 (FAT16)
	uint8_t exe_code[448];					//448 Bytes 3Eh	
	uint8_t magic[2];						//2 Bytes 1FEh
}boot_record_t;								// -----------------
											// 512 Bytes
											
											
typedef struct S_DIRECTORY_ENTRY {
	uint8_t	name[8];				 //8 Bytes filename
	uint8_t	ext[3];				 //3 Bytes file extension
	uint8_t	attributes;				 //file attributes RSHA, Longname, Drive Label, Directory
	uint8_t	nt_case_info;			 //set to zero
	uint8_t	create_time_ms;			 //creation time part in milliseconds
	uint16_t create_time;			 //Create Time (Hrs/Mins/Secs)
	uint16_t create_date;			//creation date
	uint16_t last_access_date;		//last access date
	uint16_t first_cluster_hi;		//first cluster high word                 
	uint16_t last_mod_time;			//last write time
	uint16_t last_mod_date;			//last write date
	uint16_t first_cluster_lo;		// first cluster low word                 
	uint32_t size;				// dword	
} directory_entry_t ;											



#define MAX_ROOT_ENTRIES			512

#define LONG_NAME					0x0F
#define ENTRY_IS_FREE				0xE5

#define M_ERR_INVALID_FILE			20
#define M_ERR_BSR_NOT_FOUND			21
#define M_ERR_MBR_NOT_FOUND			22

uint8_t fat16_init();
directory_entry_t* file_find( char *fname, const char* ext   );
uint8_t file_read_block( directory_entry_t* file, uint8_t* read_buffer, uint32_t block_no);
uint16_t file_number( const char* ext );



#endif /* FAT16_H_ */