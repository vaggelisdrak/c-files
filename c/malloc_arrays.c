#include <stdio.h>
#include <stdlib.h>


int main()
{
    int * datatable = NULL;
    int k= 0;

    int d;
    printf("dose arithmous:\n");
    while(scanf("%d",&d), d>0){
        k++;
        datatable = realloc(datatable, k * sizeof(int));
        datatable[k-1] = d;
    }

    printf("\n");
    for(int i=0;i<k;i++){
        printf("%d\n",datatable[i]);
    }

    free(datatable);
    return 0;
}