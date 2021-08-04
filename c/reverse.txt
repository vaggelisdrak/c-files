#include <stdio.h>
#include <string.h>
#define N 15

int reverse(char word[N]);

int main() {
    // Write C code here
    char word[N];
    printf("give a word: ");
    scanf("%s",word);
    printf("%d\n",strlen(word));
    printf("the word you gave is: %s\n",word);
    printf("the reverse one is: ");
    reverse(word);
    return 0;
}

int reverse(char word[N]){
    int i;
    for(i=1;i<=strlen(word);i++){
        printf("%c",word[strlen(word)-i]);
    }
    return 0;
}