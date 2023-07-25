// Online C compiler to run C program online
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define size 150

int main()
{
    char string[size];
    int i;

    printf("Eisigage mia leksi me mikra:");
    gets(string);

    for(i=0; i<=strlen(string); i++)
    {
        if(string[i]>=97 && string[i]<=122)
            string[i]=string[i]-32;
    }
    printf("\nMe kefalaia: %s\n",string);
    return 0;
}