/**********************************************************
 * Name:		1Zadatak.c	
 * Description:	Reading first 44bytes of .wav file
 * Input:		Building: 			gcc -w -o zadatak1 1Zadatak.c
 * 				Starting program: 	./zadatak1 [argument -> .wav]
 * Outoput:		output_header.txt and output_data.txt
 * Misc:		-
 **********************************************************/

/* Includes */
#include <stdio.h>
#include <malloc.h>

//#define BUFFER 16000

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

int main(int argc, char *argv[])
{
	/* When executing we need to put .wav file as argument */
	if(argc != 2)
	{
		printf("Put .wav file as argument!\n");
		return 1;
	}
	
	int i;	
	
	/* Open .wav file in read mode */
	FILE *infile = fopen(argv[1], "rb");
	
	/* Create outputs in write mode */
	FILE *outfile = fopen("output_header.txt","wb");
	
	/* output_data.txt is empty, will be changed! */
	FILE *outfile1 = fopen("output_data.txt","wb");
	
	/* In case files can't be opened */
	if((!outfile) || (!outfile1))
	{
		printf("Error opening files!!!\n");
		return 1;
	}
	
	/* Creating pointer to our structure */
	header *header_one_used;
	
	/* Allocation of space */
	header_one_used = (header *) malloc(sizeof(header));
	
	/* If file is opened */
	if(infile)
	{
		/* Reads data from infile (.wav file) to array pointed by header_one_used */
		fread(header_one_used, 1, sizeof(header), infile);
		
		
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
	
	fclose(outfile);
	return 0;
}
