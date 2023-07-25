#include <stdio.h>

void swap(int *a, int *b);

int main() {
    // Write C code here
    int x=5;
    int y=15;
    
    printf("x = %d and y = %d\n",x,y);
    swap(&x,&y);
    printf("x = %d and y = %d",x,y);

    return 0;
}

void swap(int *a, int *b){
    
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return ;
}