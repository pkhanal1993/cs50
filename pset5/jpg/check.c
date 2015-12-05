 #include <stdio.h>
 #include <stdint.h>
 #include <stdlib.h>
 #include <cs50.h>
 
 int main(void)
 {
    FILE* infile = fopen("card.raw", "r");
/*    int filenum = 0;*/
/*    char* filename = malloc(sizeof(char)*2+4);*/
/*    */
    uint8_t* check_bytes = malloc(512);
    do
    {
        fread(check_bytes, 512, 1, infile);
        if (check_bytes[0] == 0xff && check_bytes[1] == 0xd8 && check_bytes[2] == 0xff && (check_bytes[3] == 0xe0 || check_bytes[3] == 0xe1))
        {  
            break;    
        }
    } while(!feof(infile));
    
    
    
    int filenum = 0;
    char* filename = malloc(7);
    
    do
    {
        filenum++;
        sprintf(filename, "%03d.jpg",filenum);
        FILE* outfile = fopen(filename, "a");
        
        int n = 0;
        do
        {
            char* write_bytes = malloc(512);
            fseek(infile, -512, SEEK_CUR);
            fread(write_bytes, 512, 1, infile);
            fwrite(write_bytes, 512, 1, outfile);
            free(write_bytes);
            
            
    /*        do*/
    /*        {*/
                fread(check_bytes, 512, 1, infile);
                if (check_bytes[0] == 0xff && check_bytes[1] == 0xd8 && check_bytes[2] == 0xff && (check_bytes[3] == 0xe0 || check_bytes[3] == 0xe1))
                {  
                    n = 1;
/*                    free(check_bytes);   */
                }
    /*        } while(!feof(infile));*/
        
        
        } while(n != 1 && feof(infile) == 0);
    }while (feof(infile) == 0);
}
