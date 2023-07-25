// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct node{
    int AM;
    char surname[50];
};

typedef struct node STUDENT;

void setStudent(STUDENT *x);

int main(void){
    STUDENT studentA;
    studentA.AM = 20;
    setStudent(&studentA);
    printf("%d %s",studentA.AM, studentA.surname);
    return 0;
}

void setStudent(STUDENT *x){
    x->AM = 10;
    strcpy(x->surname,"ben");
    return;
}