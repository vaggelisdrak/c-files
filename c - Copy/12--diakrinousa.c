#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int rizes(float a,float b,float c,float* x1,float* x2);

int main() {
    // Write C code here
    float a,b,c,riza1,riza2;
    int plithos;
    printf("dose to a to b kai to c ths deyterobathmias\n");
    scanf("%f\n",&a);
    scanf("%f\n",&b);
    scanf("%f",&c);
    plithos = rizes(a,b,c,&riza1,&riza2);
    switch(plithos){
        case 0:
            printf("den exei kamia riza");
            break;
        case 1:
            printf("exei 1 riza, thn %f",riza1);
            break;
        case 2:
            printf("exei 2 rizes, thn %f kai thn %f",riza1, riza2);
            break;
    }
    return 0;
}

int rizes(float a,float b,float c,float* x1,float* x2){
    float D;
    D = b*b-4*a*c;
    if(D>0){
        *x1 = (-b + sqrt(D))/(2*a);
        *x2 = (-b - sqrt(D))/(2*a);
        return 2;
    }
    else if(D==0){
        *x1 = (-b)/(2*a);
        return 1;
    }
    else{
        return 0;
    }
}