#include <stdio.h>
#include <stdlib.h>
void print(int **p,int M,int N);

int main() {
    // Write C code here
    int **p;
    int N;
    int M;

    printf("dose ton arithmo ton sthlon toy pinaka: ");
    scanf("%d",&N);
    printf("dose ton arithmo ton grammon toy pinaka: ");
    scanf("%d",&M);

    p = malloc(sizeof(int*)*M);
    if(!p){
        exit(0);
    }

    int i,j;
    for(i=0;i<M;i++){
        p[i] = malloc(sizeof(int)*N);
    }
    if(!p[i]){
        exit(0);
    }

    for(i=0;i<M;i++){
        for(j=0;j<N;j++){
            p[i][j] = (i+1) * (j+1);
        }
    }

    printf("o xoros mnhmhs poy desmeythke einai %d+%d+%d = %d bytes\n",
           M*N*(sizeof(int)),M*(sizeof(int*)),(sizeof(int**)),
           M*N*(sizeof(int))+ M*(sizeof(int*))+ (sizeof(int**)));


    print(p,M,N);

    for(i=0;i<M;i++){
        free(p[i]);
    }
    free(p);
    return 0;
}

void print(int **p,int M,int N){
    int i,j;
    printf("\n");
    for(i=0;i<M;i++){
        for(j=0;j<N;j++){
            printf("%d ",p[i][j]);
        }
        printf("\n");
    }
}
