#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 8
bool chess[N][N];
static int counter = 0;

void printChess(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(chess[i][j] == 0) printf("_ ");
            else printf("Q ");
        }
        printf("\n");
    }
}

bool isAttacked(int row, int column){
    int i,j;
    // Check whether column is clear
    for(i=row+1; i<N; i++)
        if(chess[i][column] == 1) return 1;

    // Check whether left diagonal "/" is clear
    for(i=row+1, j=column-1; i<N && j>=0; i++,j--)
        if(chess[i][j] == 1) return 1;

    // Check whether right diagonal "\" is clear
    for(i=row+1, j=column+1; i<N && j<N; i++, j++)
        if(chess[i][j] == 1) return 1;
    
    return 0;
}

void putQueen(int row){
    if(row == -1){
        counter = counter + 1;
        if(counter == 1){
            printChess();
            printf("\n");
        }
        return;
    }

    for(int i=0; i<N; i++){
        if(!isAttacked(row,i)){
            chess[row][i] = 1;
            putQueen(row-1);
            chess[row][i] = 0;
        }
    } 
}

int main(){
    printf("1 of the solutions: \n");
    putQueen(N-1);
    printf("There are %d solutions in total!\n",counter);
    return 0;
}