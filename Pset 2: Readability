// Computes US school grade reading level, based on the Coleman-Liau Index. C-L Index is based on letters per word and sentences per given text.

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Functions to be used
float count_letters(string text);
float count_words(string text);
float count_punct(string text);


int main(void)
{
    // Get sample text
    string text = get_string("Text: ");

    // Count letters, words, sentences
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_punct(text);

    // Coleman-Liau that shiz
    int grade = round(((0.0588 * (letters / words) * 100)) - (0.296 * (sentences / words) * 100) - 15.8);


    // Let 'em know.
    if (grade > 16)
    {
        printf("Grade 16+\n");
    }

    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", grade);
    }
}


// Computes the number of alphabetic characters in a given text.
float count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            count++;
        }
    }
    return count;
}

// Computes the number of words in a given text. Hyphenated words count as one.
float count_words(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]) != 0)
        {
            count++;
        }
    }
    count++;
    return count;
}

// Computes the number of sentences in a given text. Does not account for punct. abbreviating words but not ending sentences.
float count_punct(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (ispunct(text[i]) != 0)
        {
            if (text[i] == '.' || text[i] == '?' || text [i] == '!')
            {
                count++;
            }
        }
    }
    return count;
}
