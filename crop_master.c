/**********************************************************
 * Name:		crop_master.c	
 * Description:	
 * Input:					
 * Outoput:		
 * Misc:		
 **********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	/* When executing we need to put .lab file as argument */
	if(argc != 3)
	{
		printf("Put .lab file as 1st argument and .wav file as 2nd argument!\n");
		return 1;
	}
	
	/* Open files in read mode */
	FILE *infile_lab = fopen(argv[1], "rb");
	FILE *infile_wav = fopen(argv[2], "rb");
	
	/* In case files can't be opened */
	if((!infile_lab) || (!infile_wav))
	{
		printf("Error opening files!!!\n");
		return 1;
	}
	
	/* Do until we pass whole .lab file */
	while(infile_lab)
	{
		
	}
	
	
	
	
	return 0;
}
