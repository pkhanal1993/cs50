/**
* This is a caesar cypher
*
*
*/

#include<cs50.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char* argv[])
{
    // checks if the correct number of arguments is provided
    if (argc != 2 || atoi(argv[1])< 0)
    {
        printf("Please provide the appropriate key in the command line");
        return 1;
    }
    
    // gets the key
    int key = atoi(argv[1]);
    
    string plain_msg = GetString();
    char encrypt_msg[strlen(plain_msg)+1];
    
    // encrypts the plain_msg
    for(int i = 0, length = strlen(plain_msg); i < length; i++)
    {
        if (isalpha(plain_msg[i]))
        {
            if(isupper(plain_msg[i]))
            {
                encrypt_msg[i] = (plain_msg[i] - 65 + key)%26 + 65;
            }
            else
            {
                encrypt_msg[i] = (plain_msg[i] - 97 + key)%26 + 97;
            }        
        }
        else
        {
            encrypt_msg[i] = plain_msg[i];
            
        }
    }
    encrypt_msg[strlen(plain_msg)] = '\0';
    // prints the encrypted msg
    for(int i = 0, length = strlen(encrypt_msg); i < length; i++)
    {
        printf("%c",encrypt_msg[i]);
    }
    printf("\n");
}
