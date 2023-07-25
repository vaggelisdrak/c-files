#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // Write C code here
    char pass[30] = "hello";
    while (1){
        printf("Input the password: ");
        char x[30];
	    scanf("%s",x);
	    if (strcmp(x,pass) == 0){
	        break;
	    }
    }
    printf("sostos kodikos!");
    return 0;
}