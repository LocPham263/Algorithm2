#include <stdio.h>
#include <stdlib.h>

#define MAX_NEGATIVE -2147483648

void arrayPrint(int A[], int n);
void nodeSwap(int A[], int p, int i);
void IncreasKey(int A[], int p, int val);
void Insert(int A[], int n, int val);
int* HeapTopDown(int A[], int n);

int main(){
    int n;
    scanf("%d",&n);
    int *A = (int*) malloc((n+1)*sizeof(int));
    for(int i=1; i<=n; i++){
        scanf("%d",&A[i]);
    }
    
    A = HeapTopDown(A,n);
    arrayPrint(A,n);
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

void IncreasKey(int A[], int p, int val){
    // Assign new value to node p
    // new_val >= old_val(or A[p])
    A[p] = val;
    // Heapify
    while(p>1 && A[p/2]<A[p]){
        nodeSwap(A,p,p/2);
        p = p/2;
    }
}

void Insert(int A[], int n, int val){
    // Allocate memory for one more element 
    A = realloc(A,(n+2)*sizeof(int));
    A[n+1] = MAX_NEGATIVE;
    // Heapify
    IncreasKey(A,n+1,val);
}

int* HeapTopDown(int A[], int n){
    int p=0;
    int *buffer = (int*) malloc(p*sizeof(int));
    for(int i=1; i<=n; i++){
        // Insert(buffer, p, A[i]);

        buffer = realloc(buffer,(p+2)*sizeof(int));
        buffer[p+1] = MAX_NEGATIVE;
        IncreasKey(buffer,p+1,A[i]);


        p++;
    }
    free(A);
    return buffer;
}
