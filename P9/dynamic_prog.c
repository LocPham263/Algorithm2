#include <stdio.h>
#include <stdlib.h>
#define N 7
#define Inf 113000

void initMatrix(int M[][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            M[i][j] = -1;
        }
    }
}

void Matrix_Chain_Order(int r[], int M[][N], int S[][N]){
    for(int i=1; i<N; i++) 
        M[i][i] = 0;
    for(int l=2; l<N; l++){
        for(int i=1; i<N-l+1; i++){
            int j = i+l-1;
            M[i][j] = Inf;
            for(int k=i; k<j; k++){
                int q = M[i][k] + M[k+1][j] + r[i-1]*r[k]*r[j];
                if(q < M[i][j]){
                    M[i][j] = q;
                    S[i][j] = k;
                }
            } 
        }
    }
}

void Print_Optimal_Parens(int S[][N], int i, int j){
    if(i==j) printf("%d",i);
    else{
        printf("[");
        Print_Optimal_Parens(S,i,S[i][j]);
        Print_Optimal_Parens(S,S[i][j]+1,j);
        printf("]");
    }
}

void print_S(int S[][N]){
    for(int i=1; i<N; i++){
        for(int j=1; j<N; j++){
            if(S[i][j] == -1) printf("");
            else{
                Print_Optimal_Parens(S,i,j);
                printf(" || ");
            }
        }
        printf("\n");
    }
}

void print_M(int M[][N]){
    for(int i=1; i<N; i++){
        for(int j=1; j<N; j++){
            if(M[i][j] == -1) printf("       ");
            else printf("%6d ",M[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int r[N] = {5,10,3,12,5,50,6};
    // int r[N] = {30,35,15,5,10,20,25};
    // int r[N] = {10,20,10,15,20,10};
    // int r[N] = {100,10,100,1,1000,100};
    int M[N][N], S[N][N];
    initMatrix(M);
    initMatrix(S);
    
    printf("\nCost matrix M: \n");
    Matrix_Chain_Order(r,M,S);
    print_M(M);
    printf("\n");

    printf("\nParens index matrix S: \n");
    print_S(S);
    printf("\n");

    return 0;
}