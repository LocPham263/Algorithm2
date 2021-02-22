#include <stdio.h>
#include <stdlib.h>
#define INF 100000
#define SIZE 8
void copyMatrix(int D[][SIZE], int W[][SIZE]){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            D[i][j] = W[i][j];
        }
    }
}

void printMatrix(int W[][SIZE]){
    for(int i=0; i< SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(W[i][j] == INF) printf("INF ");
            else printf("%d ",W[i][j]);
        }
        printf("\n");
    }
}

void Floyd(int W[][SIZE], int D[][SIZE]){
    int D1[SIZE][SIZE];
    copyMatrix(D1,W);

    for(int k=0; k<SIZE; k++){
        for(int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE; j++){
                int x = D1[i][k] + D1[k][j];
                if(D1[i][j] < x) D[i][j] = D1[i][j];
                else D[i][j] = x;
            }
        }
        copyMatrix(D1,D);
    }
}

int main(){
    int W[SIZE][SIZE] = {
        {0, 48 ,INF, 8, 20, INF, 20, INF},
        {INF, 0, 24, INF, 9, INF, 76, 29},
        {97, INF, 0, INF, INF, INF, 18, 1},
        {INF, 52, 34, 0, 29, INF, INF, INF},
        {INF, INF, INF, INF, 0, 10, INF, INF},
        {INF, 10, 85, 43, INF, 0, 41, 29},
        {INF, INF, INF, 76, 38, INF, 0, INF},
        {28, 42, INF, 77, 21, INF, 11, 0},
    };
    int D[SIZE][SIZE];
    
    Floyd(W,D);
    printMatrix(D);

    return 0;
}