#include <stdio.h>
#include <stdlib.h>
#define N 15

void reverse(char word[N]);
int count_char(char word[N]);

int main()
{
    // Initialize array
    char word[N];
    printf("dose mia lexh mexri 15 xarakthres: ");
    scanf("%s", word);
    reverse(word);
    return 0;
}

int count_char(char word[N])
{
    int i = 0;
    while (word[i] != '\0')
    {
        i++;
    }
    //printf("%d",i);
    return i;
}

void reverse(char word[N])
{
    int length = count_char(word);
    char reversed_word[length];
    for (int i = 0; i < length; i++)
    {
        printf("%c",word[length-1-i]);
        reversed_word[i] = word[length -1 - i];
    }
    reversed_word[length] = '\0';
    printf("\nthe reversed word is: %s", reversed_word);
}
