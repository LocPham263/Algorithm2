#include <stdio.h>
#include <stdlib.h>

void Rand(int seed, int A, int rand_seq[]){
    int x = seed;
    const int M = 7;
    printf("[A]=%d: ",A);
    for(int i=0; i<M-1; i++){
        x = (x * A) % M;
        rand_seq[i] = x;
        printf("%d ",x);
    }
}

int main(){
    int rand_seq[6];
    for(int i=1; i<=6; i++){
        Rand(2,i,rand_seq);
        printf("\n");
    }

    return 0;
}