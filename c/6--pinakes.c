// Online C compiler to run C program online
// Online C compiler to run C program online
#include <stdio.h>
#define N 10

int mo(int pin[N]);
int bestworst(int pin[N]);

int main() {
    // sum ,mo , best , worst 
    int pin[N];
    int i;
    for(i=0;i<N;i++){
        printf("give a number");
        scanf("%d",&pin[i]);
    }
    mo(pin);
    bestworst(pin);
    return 0;
}

int mo(int pin[N]){
    int i,sum;
    float mo;
    mo = 0;
    sum = 0;
    for(i=0;i<N;i++){
        sum += pin[i];
    }
    mo = (float)sum/N;
    printf("to sum einai %d kai to meso oro einai %f",sum,mo);
    return 0; 
}

int bestworst(int pin[N]){
    int max = pin[0];
    int min = pin[0];
    int i;
    for(i=0;i<N;i++){
        if(pin[i]>max){
            max = pin[i];
        }
        if(pin[i]< min){
            min = pin[i];
        }
    }
    printf("o megistos arithmos einai: %d kai o elaxistos einai: %d",max,min);
}