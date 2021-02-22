#include <stdio.h>
#include <stdlib.h>

void B(int* p){
    p = realloc(p,5*sizeof(int));
    *(p+3) = 3;
    *(p+4) = 4;
}

int* A(){
    int* p = (int*) malloc(3*sizeof(int));
    *p = 0;
    *(p+1) = 1;
    *(p+2) = 2;
    B(p);
    return p;
}

int main(){
    int* p= A();
    for(int i=0; i<5; i++) printf("%d ",*(p+i));
    return 0;
}