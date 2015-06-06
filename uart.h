
#include "globals.h"

//#define	BAUD	19200
#define	BAUD	38400
#define BAUDDIVIDER (unsigned int)(F_CPU / BAUD / 16 - 0.5)


void putch( char c );
void putstr( char *s );		
void init_uart();	
void sput(char *fmt, ... );


