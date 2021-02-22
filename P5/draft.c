#include <stdio.h>
#include <stdlib.h>

typedef struct Cat{
    int tail;
    int haed;
} cat;

void test(cat* c){
    c->tail = 10;
    (c+1)->tail = 20;
}

int main(){
    // cat Cat[2];
    // Cat->tail = 1;
    // (Cat+1)->tail = 2;
    // printf("%d %d\n",Cat->tail, (Cat+1)->tail);
    // test(Cat);
    // printf("%d %d\n",Cat->tail, (Cat+1)->tail);

    cat* c = (cat*) malloc(2*sizeof(cat));
    c->tail = 1;
    (c+1)->tail = 2;
    printf("%d %d\n",c->tail, (c+1)->tail);
    test(c);
    printf("%d %d\n",c->tail, (c+1)->tail);
    return 0;
}