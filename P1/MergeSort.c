#include <stdlib.h>
#include <stdio.h>

void Merge(int A[], int left, int right);
void mergeSort(int A[], int left, int right);
void arrayPrint(int A[], int n);

int main(){
    int n;
    scanf("%d",&n);
    int A[n];
    for(int i=0; i<n; i++){
        scanf("%d",&A[i]);
    }

    mergeSort(A,0,n-1);
    arrayPrint(A,n);

    return 0;
}

void Merge(int A[], int left, int right){
    int mid = (left+right)/2;
    int len1 = mid - left + 1;
    int len2 = right - mid;
    
    // Create 2 temporary arrays to store 2 halves of A[]
    int temp1[len1], temp2[len2];
    for(int i=0; i<len2; i++){
        temp1[i] = A[left+i];
        temp2[i] = A[left+len1+i];
    }
    if(len1 > len2) temp1[len1-1] = A[left+len1-1];

    // Merge sort
    int i=0, j=0, k=left;
    while(i<len1 && j<len2){
        if(temp1[i] <= temp2[j]){
            A[k] = temp1[i];
            i++;
        }else{
            A[k] = temp2[j];
            j++;
        }
        k++;
    }

    //Store the remaining of either temp1 or temp2 in A[]
    if(i>=len1){
        for(;j<len2;j++){
            A[k] = temp2[j];
            k++;
        }
    }else{
        for(;i<len1;i++){
            A[k] = temp1[i];
            k++;
        }
    }
}

void mergeSort(int A[], int left, int right){
    if(left < right){
        int mid = (left+right)/2;
        // Keep dividing into smaller halves
        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
       // Merge smaller halves 
        Merge(A,left,right);
    }
}

void arrayPrint(int A[], int n){
    for(int i=0; i<n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}