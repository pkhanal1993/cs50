/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <stdint.h>
 #include <stdlib.h>
 #include <cs50.h>
 
 int jpg_start(FILE* file);
 void write_new(FILE* infile, int* filenum, char* filename);
 int main(void)
 {
    // opens the input file and declares some useful variables
    FILE* infile = fopen("card.raw", "r");
    int* filenum = malloc(sizeof(int));
    char* filename = malloc(sizeof(char)*2+4);
    uint8_t* check_bytes = malloc(512);
    
    // finds the start of the first jpeg
    do
    {
        fread(check_bytes, 512, 1, infile);
        if (check_bytes[0] == 0xff && check_bytes[1] == 0xd8 && check_bytes[2] == 0xff && (check_bytes[3] == 0xe0 || check_bytes[3] == 0xe1))
        {  
            break;    
        }
    } while(feof(infile)== 0);
    
    free(check_bytes);
    
    // creates as many jpeg image files as there are in the drive 
    do
    {
        write_new(infile, filenum, filename);
        
    } while(feof(infile) == 0);
 }
    
    
    
    
 
 /***
  ** checks is the infile stream is pointing to a start of a jpeg
 **/
 
 int jpg_start(FILE* infile)
 {
    uint8_t* check_bytes = malloc(512);
    
    // reads the bytes
    fread(check_bytes, 512, 1, infile);
    
    // checks if the first four bytes denote the start of a jpeg
    if (check_bytes[0] == 0xff && check_bytes[1] == 0xd8 && check_bytes[2] == 0xff && (check_bytes[3] == 0xe0 || check_bytes[3] == 0xe1))
    { 
        free(check_bytes);  
        return 1;    
    }
    free(check_bytes);
    return 0;
 }

     
 /***
  * does the writing of a jpeg image
 **/
 
 void write_new(FILE* infile, int* filenum, char* filename)
 {
    
    // gives the jpeg image a name (each time increased by 1 as 001, 002)
    *filenum = *filenum + 1;
    sprintf(filename, "%03d.jpg",*filenum);
    
    // open a new file
    FILE* outfile = fopen(filename, "w");
    int end = 1;
    
    // does the writing until the end of an image is reached
    do
    {
        char* write_bytes = malloc(512);
        fseek(infile, -512, SEEK_CUR);
        fread(write_bytes, 512, 1, infile);
        
        fwrite(write_bytes, 512, 1, outfile);
        
        free(write_bytes);
        end = jpg_start(infile);
    
    
    } while(end == 0 && feof(infile)== 0);
    
 }
