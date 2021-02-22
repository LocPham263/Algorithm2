#include <stdio.h>
#include <stdlib.h>

void arrayPrint(int A[], int n);
void nodeSwap(int A[], int p, int i);
void Heapify(int A[], int n, int i);
void HeapBottomUp(int A[], int n);

int main(int argc, char *argv[]){
    int n;
    scanf("%d",&n);
    int A[n+1];
    for(int i=1; i<=n; i++){
        scanf("%d",&A[i]);
    }

    HeapBottomUp(A,n);
    return 0;
}

void arrayPrint(int A[], int n){
    for(int i=1; i<=n; i++){
        printf("%d ",A[i]);
    }
    printf("\n");
}

void nodeSwap(int A[], int p, int i){
    int buffer = A[p];
    A[p] = A[i];
    A[i] = buffer;
}

void Heapify(int A[], int n, int p){
    // Left child and right child, p is parent node
    int l = 2*p;
    int r = 2*p+1;

    // Heapify
    int max = p;
    //If left child exists and > parent node
    if(l<=n && A[p]<A[l])   max = l;
    if(r<=n && A[max]<A[r]) max = r;
    if(max != p){
        nodeSwap(A,p,max);
        Heapify(A,n,max);
    }
}

void HeapBottomUp(int A[], int n){
    // From the last parent node 
    for(int i=n/2; i>0; i--) Heapify(A,n,i);
    // print array
    arrayPrint(A,n);
}