#include <stdio.h>
#include <string.h>
#define N 1024

void inverse(char *s, char *invs);
int count_words(char *s);

int main(void){
    
 char text[N+1];
 char inversetext[N+1];
 
 printf("Please enter text:" );
 scanf("%1024[^\n]",text);
 
 inverse(text, inversetext);
 printf("\n");
 
 printf("Inverse text:%s \n ",inversetext);
 printf("words:%d \n",count_words(text));
}

void inverse(char *s, char *invs){ 
    int total;
    total = count_words(s);
    invs += total; //o deikths invs deixnei sthn thesi a[total] --> invs = total
    for(int i=0; i<=total; i++){
       //printf("%c",*s);
       invs--;
       *invs  = *s;
       s++;

    }
}

int count_words(char *s){
    int i=0;
    while (*s != '\0'){
        i++;
        s++;
    }
    return i;
}
