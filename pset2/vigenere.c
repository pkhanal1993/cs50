/* This program uses the key to encrypt a text */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<cs50.h>
#include<string.h>

int main(int argc, string argv[])
{
    if(argc != 2)       //checks if key has been provided or not
    {
        printf("Please provide a non-numeric key as an argument\n");
        return 1;
    }
    
    string key = argv[1];
    for(int i = 0, length = strlen(key); i < length; i++)
    {    
        if (isdigit(key[i]))
        {
            printf("Please provide a non-numeric key as an argument\n");
            return 1;
        }
    }
    string text = GetString();
    int text_len = strlen(text);
    char encrypted_msg[text_len];
    int letter_case;
    for(int i = 0, j = 0, key_len = strlen(key), key_case, key_num; i < text_len; i++)
    {
        if(isalpha(text[i]))
        {
            key_case = islower(key[j])? 97 : 65;
            key_num = key[j]- key_case;
            letter_case = (islower(text[i]))? 97 : 65;
            encrypted_msg[i] = (text[i] - letter_case+ key_num)%26 + letter_case;
            j = (j+1) % key_len;
        
        }
        else
        {
            encrypted_msg[i] = text[i];
        }
    
    }
    for(int i = 0; i < text_len; i++)
        printf("%c", encrypted_msg[i]);
    printf("\n");
}    
