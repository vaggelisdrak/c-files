// Online C compiler to run C program online
// Online C compiler to run C program online
#include <stdio.h>

int main() {
    // Write C code here
    double s = 0;
    int i;
    for(i=1;i<=50;i++){
        s = s + (float)1/i;
    }
    printf("%f",s);
    
    int num,x,r_num=0;
    printf("\nInput a number: ");
    scanf("%d",&num);
    printf("\nThe original number = %d",num);
    while(num>=1)
    {
    x=num%10;
    r_num=r_num*10+x;
    num=num/10;
    }
    printf("\nThe reverse of the said number = %d",r_num);
    return 0;
}