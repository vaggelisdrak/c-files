#include <stdio.h>

void change_pointer(int **px, int *y);

int main(void)
{
    // Write C code here
    int x = 10;
    int y = 20;
    int *ptr;
    int **pptr;

    ptr = &x;
    pptr = &ptr;

    change_pointer(pptr,&y);

    printf("x = %d and y = %d  and ptr value = %d\n" , x, y,*ptr);

    return 0;
}

void change_pointer(int **px, int *y){
    *px = y;
    return;
}