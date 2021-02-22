#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){
    int buffer = *a;
    *a = *b;
    *b = buffer;
}

void SelectionSort(int A[], int n){
    int* min;
    for(int i=0; i<n-1; i++){
        min = A+i;
        for(int j=i+1; j<n; j++){
            if(A[j] < *min) min = A+j;
        }
        swap(A+i,min);
    }
}

void arrayPrint(int A[], int n){
    for(int i=0; i<n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d",&n);
    int A[n];
    for(int i=0; i<n; i++){
        scanf("%d",&A[i]);
    }

    SelectionSort(A,n);
    arrayPrint(A,n);

    return 0;
}