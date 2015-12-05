/* This is the caeser */

#include<stdio.h>
#include<cs50.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, string argv[])
{
    
    if(argc != 2)       //checks if the correct number of arguments is provided
    {
        printf("Please provide the key:a non-negative integer for cypher as an argument\n");
        return 1;
    }
    
    int key = atoi(argv[1]);        //converts the key which is stored as string to int
    if(key < 0)
    {
        printf("Please provide a non-negative integer as the key\n");
        return 1;
    }
    printf("Please enter the text to be encrypted\n");
    string text = GetString();      //takes input from the user: the text to be encrypted
    char encrypted_msg[strlen(text)];
    int letter_case;
    for(int i = 0, text_len = strlen(text); i < text_len ; i++)
    {
        
        if(isalpha(text[i]))
        {
        
            letter_case = (islower(text[i]))? 97 : 65;       //checks which case the letter is in, and assgins the appropirate value
            encrypted_msg[i] = (text[i]-letter_case+key)%26 + letter_case;
        }   
        else    
            encrypted_msg[i] = text[i];    
    } //end of for loop      
    
    for(int i = 0; i < strlen(text); i++)
        printf("%c",encrypted_msg[i]);
    printf("\n");          
}        
        
        
    
    
   
    
    
    
    


