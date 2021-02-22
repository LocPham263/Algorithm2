#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 100000
const int M = 2147483647;

void Rand(int seed, double rand_seq[]){
    const int A = 48271;
    int x = seed;
    int Q = M/A;
    int R = M%A;

    for(int i=0; i<2*size; i++){
        x = A*(x%Q) - R*(x/Q);
        if(x<0) x += M;
        rand_seq[i] = x;
    }
}

void inRange(double rand_seq[]){
    for(int i=0; i<2*size; i++)
        rand_seq[i] = rand_seq[i] / (double)M;
}

void printSeq(double rand_seq[]){
    for(int i=0; i<2*size; i++)
        printf("%lf ",rand_seq[i]);
    printf("\n");
}

double PI(){
    int inCircle = 0;
    double rand_seq[2*size];
    time_t t;
    Rand((unsigned) time(&t),rand_seq);
    inRange(rand_seq);
    // printSeq(rand_seq);

    double x,y;
    int i=0;
    while(i < 2*size){
        x = rand_seq[i];
        i++;
        y = rand_seq[i];
        i++;
        double d = (x-0.5)*(x-0.5) + (y-0.5)*(y-0.5);
        if(d < 0.25) inCircle++;
    }

    return (double)(4*inCircle)/size;
}

int main(){
    double pi = PI();
    printf("%4lf\n",pi);
    
    return 0;
}