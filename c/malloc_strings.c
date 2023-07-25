#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10

int main()
{
    char ** mytext = NULL;
    char * word;
    int words = 0;
    while(scanf("%s",word = malloc(N * sizeof(char))), strcmp(word,"TELOS")!=0){
        words++;
        mytext = realloc(mytext, words * sizeof(char *));
        mytext[words-1] = word;

    }
    free(word);

    for(int i=0;i<words;i++){
        printf("%s\n",mytext[i]);
    }
    return 0;
}