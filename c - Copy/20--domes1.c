// Online C compiler to run C program online
#include <stdio.h>

struct point{
    float x;
    float y;
};

void readpoint(struct point *p);
float apostash(struct point A,struct point B);

int main() {
    // Write C code here
    struct point A,B;
    printf("gia to proto shmeio:\n");
    readpoint(&A);
    printf("\n");
    printf("gia to deytero shmeio:\n");
    readpoint(&B);

    printf("h apostash ton dyo shmeion einai %.3f",apostash(A,B));
    return 0;
}

void readpoint(struct point *p){
    printf("dose thn syntetagmenh x: ");
    scanf("%f",&p->x);

    printf("dose thn syntetagmenh y: ");
    scanf("%f",&p->y);
}

float apostash(struct point A,struct point B){
    float dis;
    dis = sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
    return dis;
}
