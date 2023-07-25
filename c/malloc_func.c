#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHARS 100
int init_dynamic_array(char ***b);
int main()
{
    char **mytext = NULL;
    int i;
    int words = init_dynamic_array(&mytext);
    for (i = 0; i < words; i++)
        printf("%s\n", mytext[i]);
    free(mytext);
    return 0;
}

int init_dynamic_array(char ***b)
{
    char *WORD;
    int words = 0;
    while (scanf("%s", WORD = malloc(CHARS * sizeof(char))),
           strcmp(WORD, "TELOS"))
    {
        words++;
        *b = realloc(*b, words * sizeof(char *));
        (*b)[words - 1] = WORD;
    }
    free(WORD);
    return words;
}