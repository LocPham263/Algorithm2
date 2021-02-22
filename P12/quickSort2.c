// Randomized quickSort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 1000000

void quickSort(int S[], int N){
    if(N == 0) return;
    
    int ranID = rand()%N;
    int pivot = S[ranID];
    int S1[N-1], S2[N-1];
    int x=0, y=0;
    for(int i=0; i<N; i++){
        if(S[i] < pivot || (S[i] == pivot && i!=ranID)){
            S1[x] = S[i];
            x++;
        }else if(S[i] > pivot){
            S2[y] = S[i];
            y++;
        }
    }

    quickSort(S1,x);
    // printf("%d ",pivot);
    quickSort(S2,y);
}

void printS(int S[]){
    for(int i=0; i<size; i++)
        printf("%d ",S[i]);
    printf("\n");
}

int main(){
    int S[size];
    double total_time;
    clock_t start, mid, end;
    start = clock();
    srand(time(0));
    for(int j=1; j<=100; j++){
        for(int i=0; i<size; i++)
            S[i] = rand()%size + 1;
        // printS(S);
        mid = clock();
        quickSort(S,size);
        end = clock();

        total_time += ((double)(end-mid)) / CLOCKS_PER_SEC;
    }
    printf("%lf \n",total_time/100);

    return 0;    
}