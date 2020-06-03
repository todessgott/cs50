#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{

    if (argc != 2 || argc < 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string foo = argv[1];

    for (int i = 0; i < strlen(foo); i++)
    {
        if (isalpha(foo[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    string ptext = get_string("plaintext: ");
    string ctext = ptext;

    int k = atoi(foo);


    for (int i = 0; i < strlen(ptext); i++)
    {
        int trash = 0;
        if (isalpha(ptext[i]))
        {
            if (isupper(ptext[i]))
            {
                trash = (int)(ptext[i] + k - 65) % 26 + 65;
                ctext[i] = (char)trash;
            }
            if (islower(ptext[i]))
            {
                trash = (int)(ptext[i] + k - 97) % 26 + 97;
                ctext[i] = (char)trash;
            }
        }
        else if (ispunct(ptext[i]) || isblank(ptext[i]))
        {
            ctext[i] = ptext[i];
        }
    }

    printf("ciphertext: %s\n", ctext);
    return 0;
}
