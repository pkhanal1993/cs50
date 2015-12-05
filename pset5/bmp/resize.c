/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize resize_factor infile outfile\n");
        return 1;
    }

    // remember filenames and resize factor
    int resize_factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // ensure proper resize factor
    if (resize_factor < 1 || resize_factor > 100)
    {
        printf("Please enter the resize factor between 1 and 100 inclusive");
        return -1;
    }
    

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // save infile's values
    LONG old_height = abs(bi.biHeight);
    LONG old_width = bi.biWidth; 
    
    
    // determine old padding for scanlines
    int old_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine new_padding for scanlines
    int new_padding =  (4 - (resize_factor * bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //change image sizes
    LONG new_pix = resize_factor * old_height * resize_factor * old_width;
    bi.biSizeImage = new_pix * 3 + new_padding * resize_factor * old_width;
    bf.bfSize = 54 + bi.biSizeImage;
    bi.biWidth *= resize_factor;
    bi.biHeight *= resize_factor;
/*    bi.biSize = bi.biSize + (new_pix - (old_height * old_width)) * 3;*/
    
    
    

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

   

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs((int)old_height); i < biHeight; i++)
    {
    
        // temporary storage
        RGBTRIPLE triple;

        
        for(int m = 0; m < resize_factor; m++)
        {            
            // iterate over pixels in scanline
            for (int j = 0; j < old_width; j++)
            {
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int k = 0; k < resize_factor ; k++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding, if any
            fseek(inptr, old_padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }
            
            // set the file pointer to the start of the line
            if (m != resize_factor -1)
                fseek(inptr, -3*old_width - old_padding, SEEK_CUR);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
