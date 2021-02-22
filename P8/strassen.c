#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1024

typedef struct Block{
    int r1, r2;
    int c1, c2;
} block;

void printMatrix(short A[][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) 
            printf("%d ",A[i][j]);
        printf("\n");
    }
    printf("\n");
}

void initMatrix(short A[][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++)
            A[i][j] = rand() % 5;
    }
}

void setMatrix(short A[][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++)
            A[i][j] = 0;
    }
}

void initBlock(block* a){
    a->c1 = a->r1 = 0;
    a->c2 = a->r2 = N-1;
}

void setBlock(block A, block* a){
    for(int i=0; i<4; i++){
        a->c1 = A.c1;
        a->c2 = A.c2;
        a->r1 = A.r1;
        a->r2 = A.r2;
        a = a+1;
    }
}

void divide(block a, int index, block* new){
    int new_r = a.r1 + (a.r2 - a.r1)/2;
    int new_c = a.c1 + (a.c2 - a.c1)/2;

    switch (index){
        case 0:
            new->r2 = new_r;
            new->c2 = new_c;
            break;
        case 1:
            new->r2 = new_r;
            new->c1 = new_c + 1;
            break;
        case 2:
            new->r1 = new_r + 1;
            new->c2 = new_c;
            break;
        case 3:
            new->r1 = new_r + 1;
            new->c1 = new_c + 1;
            break;
        default: break;
    }
}

void MAT_MULT(short* A, short* B, short C[][N], block c){
    block new_a[4], new_b[4], new_c[4];
    setBlock(c,new_c);
    
    // Stop condition 1x1 matrix (r1=r2=c1=c2)
    if(c.c1 == c.c2 && c.r1 == c.r2){
        C[c.r1][c.c1] = (*A)*(*B);
        return;

        int S[10];
        S[0] = B[0][1] - B[1][1];
        S[1] = A[0][0] + A[0][1];
        S[2] = A[1][0] + A[1][1];
        S[3] = B[1][0] - B[0][0];
        S[4] = A[0][0] + A[1][1];
        S[5] = B[0][0] + B[1][1];
        S[6] = A[0][1] - A[1][1];
        S[7] = B[1][0] + B[1][1];
        S[8] = A[0][0] - A[1][0];
        S[9] = B[0][0] + B[0][1];

        int P[7];
        P[0] = A[0][0]*S[0];
        P[1] = S[1]*B[1][1];
        P[2] = S[2]*B[0][0];
        P[3] = A[1][1]*S[3];
        P[4] = S[4]*S[5];
        P[5] = S[6]*S[7];
        P[6] = S[8]*S[9];

        C[c.r1][c.c1] = P[4] + P[3] - P[1] + P[5];
    }
    // Recursion
    else{
        // Divide
        for(int i=0; i<4; i++){
            divide(c,i,new_c+i);
        }
        // Conquer
        // C0 = A0xB0 + A1xB2
        MAT_MULT(A,B,C,new_a[0],new_b[0],new_c[0]);
        MAT_MULT(A,B,C,new_a[1],new_b[2],new_c[0]);
        // C1 = A0XB1 + A1xB3
        MAT_MULT(A,B,C,new_a[0],new_b[1],new_c[1]);
        MAT_MULT(A,B,C,new_a[1],new_b[3],new_c[1]);
        // C2 = A2xB0 + A3xB2
        MAT_MULT(A,B,C,new_a[2],new_b[0],new_c[2]);
        MAT_MULT(A,B,C,new_a[3],new_b[2],new_c[2]);
        // C3 = A2xB1 + A3xB3
        MAT_MULT(A,B,C,new_a[2],new_b[1],new_c[3]);
        MAT_MULT(A,B,C,new_a[3],new_b[3],new_c[3]);
    }
}

int main(){
    short A[N][N], B[N][N], C[N][N];
    block a,b,c;
    srand(time(0));

    initMatrix(A);
    initBlock(&a);
    initMatrix(B);
    initBlock(&b);
    setMatrix(C);
    initBlock(&c);

    // printMatrix(A);
    // printMatrix(B);
    
    clock_t t;
    t = clock();
    MAT_MULT(A,B,C,a,b,c);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    // printf("\n");
    // printMatrix(C);
    printf("%f (s)\n",time_taken);

    return 0;
}