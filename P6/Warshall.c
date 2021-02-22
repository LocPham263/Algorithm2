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

void Warshall(int W[][SIZE], int D[][SIZE]){
    int D1[SIZE][SIZE];
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(i==j || W[i][j] != INF) D1[i][j] = 1;
            else D1[i][j] = 0;
        }
    }

    for(int k=0; k<SIZE; k++){
        for(int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE; j++){
                D[i][j] = D1[i][j] || (D1[i][k] && D1[k][j]);
            }
        }
        copyMatrix(D1,D);
    }
}

int main(){
    int W[SIZE][SIZE] = {
        {1, 1, INF, INF, 1, 1, INF, 1},
        {INF, 1, 1, INF, INF, INF, 1, INF},
        {INF, INF, 1, 1, INF, INF, 1, INF},
        {INF, INF, INF, 1, INF, 1, INF, INF},
        {INF, INF, INF, INF, 1, 1, INF, INF},
        {INF, INF, INF, INF, INF, 1, 1, INF},
        {INF, INF, INF, INF, INF, INF, 1, 1},
        {INF, INF, INF, INF, INF, 1, 1, 1},
    };

    int D[SIZE][SIZE];
    
    Warshall(W,D);
    printMatrix(D);

    return 0;
}