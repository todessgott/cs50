#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    string text = get_string("Text:");
    int count;
    count = strlen(text);

    int letter = 0, word = 1, sentence = 1;
    int total_character = 0;
    
    
    for (int i = 0; i < count; i++)
    {
        total_character++;
        if (isalpha(text[i]))
        {
            letter++;
        }
        else if (isblank(text[i]))
        {
            if (isalpha(text[i + 1]) || text[i + 1] == '"')
            {
                word++;
            }
        }
        else if (ispunct(text[i]))
        {
            if (isblank(text[i + 1]) && (text[i] == '.' || text[i] == '?'))
            {
                sentence++;
            }
        }
    }
    if (letter == 0)
    {
        sentence = 0;
        word = 0;
    }

    float average_num_of_letter_per_words = (letter / (float)word) * 100;
    float average_num_of_sentence_per_words = (sentence / (float)word) * 100;
    int index = round((0.0588 * average_num_of_letter_per_words) - (0.296 * average_num_of_sentence_per_words) - (15.8));
    if (index < 1 || index >= 16)
    {
        (index < 1) ? printf("Before Grade 1\n") : printf("Grade 16+\n");
    }
    else
    {
        switch (index)
        {
            case 1:
                printf("Grade 1\n");
                break;
            case 2:
                printf("Grade 2\n");
                break;
            case 3:
                printf("Grade 3\n");
                break;
            case 4:
                printf("Grade 4\n");
                break;
            case 5:
                printf("Grade 5\n");
                break;
            case 6:
                printf("Grade 6\n");
                break;
            case 7:
                printf("Grade 7\n");
                break;
            case 8:
                printf("Grade 8\n");
                break;
            case 9:
                printf("Grade 9\n");
                break;
            case 10:
                printf("Grade 10\n");
                break;
            case 11:
                printf("Grade 11\n");
                break;
            case 12:
                printf("Grade 12\n");
                break;
            case 13:
                printf("Grade 13\n");
                break;
            case 14:
                printf("Grade 14\n");
                break;
            case 15:
                printf("Grade 15\n");
                break;
        }
    }
    return 0;
}
