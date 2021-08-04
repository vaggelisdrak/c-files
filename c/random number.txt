#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    int number, input;
	/* initialize random seed: */
	srand ( time(NULL) );
	/* Generate a random number: */
	number = rand() % 10 + 1; /*apo to 1 eos to 10*/
    do{
        printf("mantepse ton arithmo apo 1-10: ");
        scanf("%d",&input);
        if(number>input){
            printf("o arithmos einai megalyteros apo to %d\n",input);
        }
        else if(number<input){
            printf("o arithmos einai mikroteros apo to %d\n",input);
        }
    }while(input!=number);
    printf("\nmprabo!");
    
}