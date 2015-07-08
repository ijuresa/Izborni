/**********************************************************
 * Name:		cropping_nd_header.c	
 * Description:	Reading header and saving it to output_header.txt
 * 				
 * Input:		Compiling: gcc -w -o cropp cropping_nd_header.c -lsndfile
				Running:   ./cropp sm04010103101.lab sm04010103101.wav
 * Outoput:		Creates output_header.txt
 * Misc:		-
 **********************************************************/


/* Structure for header */
typedef struct header_info
{	/* Positions*/
	
	/* 1-4   */ char sample_id[4]; 
	/* 5-8   */ int file_size; 
	/* 9-12  */	char format[4];
	/* 13-16 */	char format_chunk_marker[4];
	/* 17-20 */	int chunk_size;
	/* 21-22 */	short int type_format;
	/* 23-24 */	short int number_of_channels;
	/* 25-28 */	int sample_rate;
	/* 29-32 */	int byte_rate;
	/* 33-34 */	short int block_allign;
	/* 35-36 */	short int bits_per_sample;
	/* 37-40 */	char data_chunk_header[4];
	/* 41-44 */	short int size_chunk_header;
	
}header;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sndfile.h>
#include <assert.h>

int main(int argc, char *argv[])
{
	int state = 0;
	int i, integer_duration, counter = 0;
	float float_duration;
	float buffer1, buffer2, buffer;
	char buffer3[5];
	int sample_rate, number_of_frames;
	
	SF_INFO info;
	SNDFILE *sf;
	/* When executing we need to put .lab file as argument */
	if(argc != 3)
	{
		printf("Put .lab file as 1st argument and .wav file as 2nd argument!\n");
		return 1;
	}
	
	/* Open files in read mode */
	FILE *infile_lab = fopen(argv[1], "rb");
	
	/* Couldn't solve this different. It's the same argument but used different */
	FILE *infile_wav = fopen(argv[2], "rb");
	sf = sf_open(argv[2], SFM_READ, &info);
	
	/* Create outputs in write mode */
	FILE *outfile = fopen("output_header.txt","wb");
	
	/* In case files can't be opened */
	if((!infile_lab) || (!sf) || (!outfile))
	{
		printf("Error opening files!!!\n");
		return 1;
	}
	
	number_of_frames = info.frames;
    sample_rate = info.samplerate;
    
	/* Creating pointer to our structure */
	header *header_one_used;
	
	/* Allocation of space */
	header_one_used = (header *) malloc(sizeof(header));
	
	if(infile_lab !=NULL)
	{
		/* Reads data from infile (.wav file) to array pointed by header_one_used */
		fread(header_one_used, 1, sizeof(header), infile_wav);
		
		/* Puts data into structure */
		for(i = 0; i < 4; i++)
		{
			fprintf(outfile, "%c", header_one_used->sample_id[i]);
		}
		fprintf(outfile, "\nFilesize = %d bytes\n", header_one_used->file_size);
		
		for(i = 0; i < 4; i++)
		{
			fprintf(outfile, "%c",header_one_used->format[i]);
		}fprintf(outfile, "\n");
		
		for(i = 0; i < 4; i++)
		{
			fprintf(outfile, "%c", header_one_used->format_chunk_marker[i]);
		}
		fprintf(outfile, "\nLenght of format data = %d\n", header_one_used->chunk_size);
		
		/* PCM is type of format = 1 */
		if(header_one_used->type_format == 1) fprintf(outfile, "Type of format is PCM\n");
		else fprintf(outfile, "Type of format = %d\n", header_one_used->type_format);
		
		fprintf(outfile, "Number of channels = %d\n", header_one_used->number_of_channels);
		fprintf(outfile, "Sample rate = %d\n", header_one_used->sample_rate);
		fprintf(outfile, "Byte rate = %d\n", header_one_used->byte_rate);
		fprintf(outfile, "Block allign = %d\n", header_one_used->block_allign);
		fprintf(outfile, "Bits per sample = %d\n", header_one_used->bits_per_sample);
		
		for(i = 0; i < 4; i++)
		{
			fprintf(outfile, "%d", header_one_used->data_chunk_header[i]);
		}
		
		fprintf(outfile, "\nSize of data section = %d\n", header_one_used->size_chunk_header);
	}
	
	/* Other way of calculating duration */
	float_duration = (float)number_of_frames/sample_rate;
	
	/* Calculating duration of .wav file */
	float_duration = (float)header_one_used->file_size/header_one_used->byte_rate;
	
	/* Duration in seconds */
	printf("%f\n", float_duration);
	
	/* Duration in microseconds */
	integer_duration = float_duration * 1000000;
	printf("%d\n", integer_duration);
		
	while(fscanf(infile_lab, "%f %f %s", &buffer1, &buffer2, buffer3) != EOF)
	{	
		/* Converting to seconds */
		buffer1 = (float)buffer1/10000000;
		buffer2 = (float)buffer2/10000000;
		
		/* Reading 1 line and saving in buffers */
		printf("Buffer1 = %f\t", buffer1);
		printf("Buffer2 = %f\t", buffer2);
		printf("Buffer3 = %s\n", buffer3);
		counter = 1;
		
		if(counter == 1)
		{
			/* Buffer is duration of current sound */
			buffer = buffer2 - buffer1;
			
			/* If we have duration and samplerate we can calculate number of frames */
			/* Then probably with function sf_count_t sf_readf_int we can read wanted frames */
			
			/* Calculating frames needed to be read with each sound. +1 used because of rounding with float */
			int numFrames = buffer * sample_rate;
			
			/* Allocation of space for each frame */
			int *spaceFrame = (int *) malloc(numFrames * sizeof(int));
			if(spaceFrame == NULL)
			{
				printf("Allocation of space failed\n");
			}
			
			/* I am reading frames. Could also read items because on 1 CHANNEL file frames=items */
			int data[numFrames];
			
			/* Reading data */
			sf_count_t frames_read = sf_readf_int(sf, data, numFrames);
			/* Macro to check if my condition is true. If not program is terminated */
			assert(frames_read == numFrames);
		
			
			char string[50];
			sprintf(string, "%d.raw", state);

			/* Opening file in which we will write */
			SNDFILE *sndFile = sf_open(string, SFM_WRITE, &info);
			if(sndFile == NULL)
			{
				printf("Error opening file\n");
				free(spaceFrame);
				return -1;
			}
			
			int writtenFrames = sf_writef_int(sndFile, spaceFrame, frames_read);
			assert(writtenFrames == numFrames);
			//sf_count_t frames_written = sf_writef_int(sndFile, spaceFrame, numFrames);
			/*if(writtenFrames != numFrames)
			{
				printf("Can't write enough frames for the source\n");
				sf_close(sndFile);
				free(spaceFrame);
				return -1;
			}
			*/
			
			state++;
		}	
	}
	
	fclose(infile_lab);
	return 0;
}
