#include "shell.h"
#include <stdio.h>

int isjpeg(int fileDescriptor)
{
	/* ficheiro tem que estar aberto */
    unsigned char b[4];
    int n = read(fileDescriptor,b,4);
    if (n == -1)
        lseek(fileDescriptor, 0, SEEK_SET);
	if ( b[0]==0xff && b[1]==0xd8 && b[2]==0xff && b[3]==0xe0) 
        return 1;
	return 0;
}
