
#include "fat16.h"
#include "sd.h"
#include "uart.h"

uint16_t FAT1_BASE_ADDRESS, ROOT_BASE_ADDRESS, DATA_BASE_ADDRESS, PART1_BASE_ADDRESS;
uint16_t SECTORS_PER_CLUSTER;
uint16_t CLUSTER;

uint8_t buffer[MAX_BUF_SIZE];

uint8_t fat16_init()
{
	uint8_t buffer[MAX_BUF_SIZE];
	boot_record_t *br=NULL;
	
	// read MBR, sector 0
    sd_read_sector(0,buffer);
	// MBR magic number
    if((buffer[0x1fe] == 0x55) && (buffer[0x1ff] == 0xAA ))
	{
		// the no of sectors to the partition 1 is a word calculated
		// from 2 bytes at the offset '0x1C6': 0x1C6, 0x1C7
		PART1_BASE_ADDRESS = buffer[0x1c6] + (buffer[0x1c7] << 8);
		
		// read fat16 boot sector record
		// the address in bytes so we must multiply with BYTES_PER_SECTOR
		sd_read_sector( PART1_BASE_ADDRESS, buffer );	
		//_delay_ms(DELAY_MS);
		// boot sector record is valid?
		if((buffer[0x1fe] == 0x55) && (buffer[0x1ff] == 0xAA ))
		{
			
			br = (boot_record_t*)buffer;
			
			FAT1_BASE_ADDRESS = br->reserved_sectors;
			ROOT_BASE_ADDRESS = PART1_BASE_ADDRESS + FAT1_BASE_ADDRESS + (2*br->sectors_per_fat); 
			DATA_BASE_ADDRESS = ROOT_BASE_ADDRESS + (br->max_roots * 32)/BYTES_PER_SECTOR;
			SECTORS_PER_CLUSTER = br->sectors_per_cluster;	
			
#if DBG			
			sput("==> FAT1_BASE_ADDRESS=%x \n", FAT1_BASE_ADDRESS);
			sput("==> PART1_BASE_ADDRESS=%x \n", PART1_BASE_ADDRESS );
			sput("==> ROOT_BASE_ADDRESS=%x \n", ROOT_BASE_ADDRESS);
			sput("==> DATA_BASE_ADDRESS=%x \n", DATA_BASE_ADDRESS);
			sput("==> SECTORS_PER_CLUSTER=%i \n", SECTORS_PER_CLUSTER);
#endif		
			
		}else{
			return M_ERR_BSR_NOT_FOUND;
		}			
	}		
    else {
        return M_ERR_MBR_NOT_FOUND;
    }
    
	return M_OK;
}
 
 
 
 
 
 
 
 
 uint16_t file_number( const char* ext )
 {
	 directory_entry_t* file = NULL;
	// start searching from root base address
	uint16_t sector = ROOT_BASE_ADDRESS;
	uint8_t tmp_name[9];
	uint16_t count = 0;
	while (sector < MAX_ROOT_ENTRIES)	{
	
		// read a sector (512 bytes) from root directory entries	
		sd_read_sector (sector,buffer);	
		
		// each directory entry  has 32 byte		
		for (uint16_t entry = 0; entry < MAX_ROOT_ENTRIES; entry = entry + 32)	{
			 // convert the buffer to directory_entry_t structure
			 // to handle the data easier
			 file = (directory_entry_t *)&buffer[entry]; 
		 	
			 file->name[11] = '\0';
			 tmp_name[0]='\0';
			 uint8_t j=0;
			 for( uint8_t k=0; k < 8; k++)
			 {
				 // eliminate the spaces from the file name 
				 if( file->name[k] != 0x20 ){
					tmp_name[j] = file->name[k];
					j++;
				 }					
			 }			
			 tmp_name[j]='\0';
			 
			 // search file if:
			 // - have not long names
			 // - the is not empty 
			 // - the desired file name and extension are matching 
			 if ((file->attributes != LONG_NAME) && (file->name[0] != ENTRY_IS_FREE && 
					strcasecmp((const char*)file->ext, ext) == 0 )) {
					count++;
				}
				
		}
		
		sector += 1;
	}
	 
	 return count;
 }

 



directory_entry_t* file_find( char *fname, const char* ext   )
{
	
	directory_entry_t* file = NULL;
	// start searching from root base address
	uint16_t sector = ROOT_BASE_ADDRESS;
	uint8_t tmp_name[9];
	
	while (sector < MAX_ROOT_ENTRIES)	{
	
		// read a sector (512 bytes) from root directory entries	
		sd_read_sector (sector,buffer);	
		
		// each directory entry  has 32 byte		
		for (uint16_t entry = 0; entry < MAX_ROOT_ENTRIES; entry = entry + 32)	{
			 // convert the buffer to directory_entry_t structure
			 // to handle the data easier
			 file = (directory_entry_t *)&buffer[entry]; 
		 	
			 file->name[11] = '\0';
			 tmp_name[0]='\0';
			 uint8_t j=0;
			 for( uint8_t k=0; k < 8; k++)
			 {
				 // eliminate the spaces from the file name 
				 if( file->name[k] != 0x20 ){
					tmp_name[j] = file->name[k];
					j++;
				 }					
			 }			
			 tmp_name[j]='\0';
			 
			 // search file if:
			 // - have not long names
			 // - the is not empty 
			 // - the desired file name and extension are matching 
			 if ((file->attributes != LONG_NAME) && (file->name[0] != ENTRY_IS_FREE && 
					strcasecmp((const char*)file->ext, ext) == 0 && 
					strcasecmp((const char*)tmp_name, fname) == 0) ) {
					return file;
				}
				
		}
		
		sector += 1;
	} 
	
	return NULL;
}

 
 


uint8_t file_read_block( directory_entry_t* file, uint8_t* read_buffer, uint32_t block_no)	
{
	uint32_t block = 0; 
	
	if( file == NULL)
		return M_ERR_INVALID_FILE;
	
	// new cluster so we get the address from FAT table	
	if( block_no % SECTORS_PER_CLUSTER == 0 && block_no > 0 )
	{
		sd_read_sector(((CLUSTER*2) / MAX_BUF_SIZE) + FAT1_BASE_ADDRESS + PART1_BASE_ADDRESS,buffer);
		uint16_t idx = (CLUSTER*2) % MAX_BUF_SIZE;
		CLUSTER = (buffer[idx + 1] << 8) + buffer[idx];	
	}		
	
	block = ((CLUSTER - 2) * SECTORS_PER_CLUSTER) + DATA_BASE_ADDRESS;
	block += (block_no % SECTORS_PER_CLUSTER);
	
	sd_read_sector(block, (uint8_t*)read_buffer);	
		
	return M_OK;
}




