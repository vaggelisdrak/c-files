#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int AM;
    char surname[50];
};

typedef struct node STUDENT;
typedef STUDENT * STUDENT_ptr;

int main(){
    STUDENT_ptr student = NULL;
    student = (STUDENT_ptr) malloc(sizeof(STUDENT));
    student->AM = 100;
    strcpy(student->surname,"ben");
    printf("%d %s",student->AM, student->surname);
    free(student);

    return 0;
}