#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //获取用户输入
    string text = get_string("Text: ");
    printf("%s\n", text);

    int letters = count_letters(text);
    printf("%i letters\n", letters);

    int words = count_words(text);
    printf("%i words\n", words);

    int sentences = count_sentences(text);
    printf("%i sentences\n", sentences);

    // Coleman-Liau
    // L is the average number of letters per 100 words in the text.
    float L = letters * 100.0 / words;
    // S is the average number of sentences per 100 words in the text.
    float S = sentences * 100.0 / words;


    int index = (int)round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}


int count_letters(string text)
{
    int letters = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if(isalnum(text[i]))
        {
            letters++;
        }
    }
    return letters;

}

int count_words(string text)
{
    int words = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if(isspace(text[i]))
        {
            words++;
        }
    }
    return words + 1; // eg: 3个空格 == 4个词

}

int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if(text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    return sentences;

}

