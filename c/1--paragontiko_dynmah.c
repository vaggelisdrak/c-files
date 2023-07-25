// Online C compiler to run C program online
#include <stdio.h>

int paragontiko(int i);
int dymanh(int i,int e);

int main() {
    // Write C code here
    int i,e;
    printf("dose th bash: ");
    scanf("%d",&i);
    printf("dose ton ekueth: ");
    scanf("%d",&e);
    dynamh(i,e);
    
    int a;
    printf("\ndose enan akeraio: ");
    scanf("%d",&a);
    paragontiko(a);
    return 0;
}

int dynamh(int i,int e){
    //to i einai h bash, to e o ekueths
    int j=0;
    int total=1;
    for(j=1;j<=e;j++){
        total = i*total;
    }
    printf(" %d ^ %d = %d\n",i,e,total);
    return 0;
}

int paragontiko(int i){
    int j;
    int total =1;
    for(j=0;j<i;j++){
        total = total * (i-j);
    }
    printf(" %d ! = %d",i,total);
    return 0;
}