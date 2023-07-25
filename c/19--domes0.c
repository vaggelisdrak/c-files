#include <stdio.h>

struct elem{
    char name[20];
    int grade;
};

typedef struct elem student;
void readdata(student *x);
void printdata(student x);
void bestgrade(student a,student b);

int main() {
    // Write C code here
    student A,B;
    
    readdata(&A);
    printdata(A);
    
    readdata(&B);
    printdata(B);
    bestgrade(A,B);
        
    return 0;
}

void readdata(student *x){
    printf("dose to onoma tou mathiti: ");
    scanf("%s",x->name);
    printf("dose to vathmo tou mathiti: ");
    scanf("%d",&x->grade);
}

void printdata(student x){
    printf("o mathitis %s egrapse %d\n",x.name,x.grade);
}

void bestgrade(student a,student b){
    if(a.grade>b.grade){
        printf("o %s exei megalytero vathmo",a.name);
    }
    else if(a.grade == b.grade){
        printf("exoun ton idio vathmo");
    }
    else{
        printf("o %s exei megalytero vathmo",b.name);
    }
}