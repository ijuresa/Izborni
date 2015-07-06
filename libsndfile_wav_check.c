/**********************************************************
 * Name:		libsndfile_wav_check.c	
 * Description:	Reading file from .wav file using libsndfile library.
 * Input:		Building: 			gcc -w -o wav_check libsndfile_wav_check.c -lsndfile
 * 				Starting program: 	./wav_check
 * Outoput:		Number of frames, samplerate, number of channels, number of items (channels * frames)
 * Misc:		Creates output_collection.out which contains the data from .wav file
 **********************************************************/

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>

int main()
{
	 /* SNDFILE is very much like a FILE in the Standard C library */
    SNDFILE *sf;
    
    /*****************************************************
    * Pointer to SF_INFO struct is passed to sf_open
    * On read, the library fills this struct with information about the file
    * On write, the struct must be filled in before calling sf_open 
    *****************************************************/
    SF_INFO info;
    
    int number, numberof_items;
    /* Buffer for space allocation */
    int *buffer;
    /* Variables to hold the data */
    int frames, samplerate, channels, format, sections;
    int i,j;
    
    FILE *out = fopen("output_collection.out","w");
    
    /* Opening the .wav file */
    info.format = 0;
    sf = sf_open("sm04010103101.wav", SFM_READ, &info);
    
    if (sf == NULL)
    {
        printf("Failed to open the file.\n");
        exit(-1);
    }
        
    /* Reading info about our .wav file */
    frames = info.frames;
    samplerate = info.samplerate;
    channels = info.channels;
    format = info.format;
    sections = info.sections;
    
    /* Printing information from SF_INFO structure */
    printf("Frames = %d\n", frames);
    printf("Sample rate = %d\n", samplerate);
    printf("Channels = %d\n", channels);
    printf("Bit size = %d\n", format);
    printf("Sections = %d\n", sections);
    numberof_items = frames*channels;
    printf("Number of items = %d\n", numberof_items);
    
   /* Allocation of space for our data */
    buffer = (int *) malloc(numberof_items * sizeof(int));
    
    /* Reading data */
    number = sf_read_int(sf, buffer, numberof_items);
    sf_close(sf);
    
    printf("Read %d items\n", number);
    
    /* Write data to output_collection.out */
    for (i = 0; i < number; i += channels)
    {
        for (j = 0; j < channels; ++j)
		{
            fprintf(out,"%d ", buffer[i+j]);
         }
         
        fprintf(out,"\n");
    }
    fclose(out);
    free(buffer);
    
    return 0;
}
