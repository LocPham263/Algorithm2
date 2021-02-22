#include <stdio.h>
#include <stdlib.h>
#define long_MAX 1111111
long MatrixChainOrder(long p[], long n) { 
    long m[n][n]; 
    long i, j, k, L, q; 
    for (i=1; i<n; i++) m[i][i] = 0; 
    for (L=2; L<n; L++) { 
        for (i=1; i<n-L+1; i++) { 
            j = i+L-1; 
            m[i][j] = long_MAX; 
            for (k=i; k<=j-1; k++) { 
                // q = cost/scalar multiplications 
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j]; 
                if (q < m[i][j]) 
                    m[i][j] = q; 
            } 
        } 
    } 
    return m[1][n-1]; 
} 
  
int main() 
{ 
    long arr[] = {100,10,100,1,1000,100};
    long size = sizeof(arr)/sizeof(arr[0]); 
    printf("%ld\n",size);
    printf("Minimum number of multiplications is %ld ", 
                       MatrixChainOrder(arr, size)); 
    
    getchar(); 
    return 0; 
} 