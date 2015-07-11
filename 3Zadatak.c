/**********************************************************
 * Name:		3Zadatak.c	
 * Description:	Not finished		
 * Input:		Compiling: gcc -w -o zadatak3 3Zadatak.c -lsndfile			
 * 				Running:   ./3zadatak sm04010103101.lab sm04010103101.wav
 * Outoput:		
 * Misc:		-
 **********************************************************/


/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sndfile.h>
#include <assert.h>

struct lab_info
{
	int position;
	float start_time;
	float finish_time;
	float Csound_duration;
	char voice[5];
	
};

int main(int argc, char *argv[])
{
	int nRows = 0, character = 0;
	SF_INFO info;
	SNDFILE *sf;

    
	/* When executing we need to put .lab as 1st and .wav file as 2nd argument */
	if(argc != 3)
	{
		printf("Put .lab file as 1st argument and .wav file as 2nd argument!\n");
		return 1;
	}
	
	/* Open .lab and .wav file in read mode */
	FILE *infile_lab = fopen(argv[1], "rb");;
	sf = sf_open(argv[2], SFM_READ, &info);
	
	/* In case any of the files can't be opened */
	if((!infile_lab) || (!sf))
	{
		printf("Error opening files!!!\n");
		return 1;
	}
	
	/* Creating pointer to our structure */
	struct lab_info currentData;

	/* Calculating numbers of rows */
	while(!feof(infile_lab))
	{
		character = fgetc(infile_lab);
		
		if(character == '\n')
		{
			nRows++;
		}
	}
	rewind(infile_lab);
	
	float data_voice[nRows];
	char char_voice[nRows];

	if(infile_lab !=NULL)
	{
		int i = 0;
		/* Reading line by line from our .lab file until it's EOF */
		while(fscanf(infile_lab, "%f %f %s", &currentData.start_time, &currentData.finish_time, currentData.voice) != EOF)
		{	
			
			printf("Pozicija = %d\n", currentData.position);
			/* Converting to seconds -> Because times in .lab file are in microseconds */
			currentData.start_time = (float)currentData.start_time/10000000;
			currentData.finish_time = (float)currentData.finish_time/10000000;
			
			/* Duration of current sound */
			currentData.Csound_duration = currentData.finish_time - currentData.start_time;	
			
			/* Saving array of characters and duration */	
			char_voice[i] = *currentData.voice;
			data_voice[i] = currentData.Csound_duration;
			

			i++;
			
		}
		
		/* Checking */
		for(i = 0; i < nRows; i++)
		{		
			printf("%d = %c = %f\n", i, char_voice[i], data_voice[i]);		
		}
			
		
	
		
	}
	
	
	return 0;
}
