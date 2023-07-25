#include <stdio.h>
#define N 10
#define M 5

int load(double x[N][M]) ;
int print(double x[N][M]) ;

int loadT(double x[N][M]) ;
int printT(double x[N][M]) ;

double computesum(double x[N][M]);
int printsum(double sum);

int main( ) {
    double data[N][M];
    double sum;

    load(data);
    print(data);
    printf("\nO anastrofos toy einai o:\n\n");

    loadT(data);
    printT(data);

    sum = computesum(data);
    printsum(sum);
    printf("\n%g\n", sum);

    return 0;
}

int print(double x[N][M]) {
    int i,j;
    for (i=0; i<N; i++) {
        for(j = 0; j < M;  j++){
            printf(" %g ", x[i][j]);
        }
        printf("\n");
    }
    return 0;
}
int load(double x[N][M]) {
    int i,j;
    for (i=0; i<N; i++) {
        for(j = 0; j < M;  j++){
            x[i][j] = ((double) i+j) / N ;
        }
    }
    return 0;
}

double computesum(double x[N][M]) {
    int i,j;
    double sum = 0.0;
    for(i = 0; i < N; i++) {
        for(j = 0; j < M; j++){
           sum = sum + x[i][j];
        }
    }
    return sum;
}

int printsum(double sum) {
    printf("\n%g\n", sum);
    return 0;
}

int printT(double x[N][M]) {
    int i,j;
    for (i=0; i<M; i++) {
        for(j = 0; j < N;  j++){
            printf(" %g ", x[j][i]);
        }
        printf("\n");
    }
    return 0;
}
int loadT(double x[N][M]) {
    int i,j;
    for (i=0; i<M; i++) {
        for(j = 0; j < N;  j++){
            x[j][i] = ((double) i+j) / N ;
        }
    }
    return 0;
}

