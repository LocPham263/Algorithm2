#include <stdio.h>
#include <stdlib.h>
#define size 1000
const int M = 2147483647;

void Rand1(int seed, double rand_seq[]){
    int x = seed;
    const int A = 65539;
    const int C = 125654;

    for(int i=0; i<size; i++){
        x = A*x + C;
        // Overflow detection
        if(x<0){
            x += M;
            x += 1;
        }
        rand_seq[i] = x;
    }
}

void Rand2(int seed, double rand_seq[]){
    const int A = 48271;
    int x = seed;
    int Q = M/A;
    int R = M%A;

    for(int i=0; i<size; i++){
        x = A*(x%Q) - R*(x/Q);
        if(x<0) x += M;
        rand_seq[i] = x;
    }
}

void Rand3(int seed, double rand_seq[]){
    int next = 0, x = seed;
    double A[size];
    Rand2(1,A);

    for(int i=0; i<size; i++){
        int j = (next+31)%55;
        x = A[j] - A[next];
        if(x<0){
            x += M;
            x += 1;
        } 
        A[next] = x;
        next = (next+1)%55;
        rand_seq[i] = x;
    }
}

void histogram(double histo[], double rand_seq[]){
    for(int i=0; i<size; i++){
        if(rand_seq[i] <= 0.1) 
            histo[0]++;
        else if(rand_seq[i] > 0.1 && rand_seq[i] <= 0.2)
            histo[1]++;
        else if(rand_seq[i] > 0.2 && rand_seq[i] <= 0.3)
            histo[2]++;
        else if(rand_seq[i] > 0.3 && rand_seq[i] <= 0.4)
            histo[3]++;
        else if(rand_seq[i] > 0.4 && rand_seq[i] <= 0.5)
            histo[4]++;
        else if(rand_seq[i] > 0.5 && rand_seq[i] <= 0.6)
            histo[5]++;
        else if(rand_seq[i] > 0.6 && rand_seq[i] <= 0.7)
            histo[6]++;
        else if(rand_seq[i] > 0.7 && rand_seq[i] <= 0.8)
            histo[7]++;
        else if(rand_seq[i] > 0.8 && rand_seq[i] <= 0.9)
            histo[8]++;
        else
            histo[9]++;
    }

    for(int i=0; i<10; i++){
        histo[i] = (histo[i]/size) * 100;
        printf("%0.2lf  || ",histo[i]);
    }
    printf("\n");
}

void inRange(double rand_seq[]){
    for(int i=0; i<size; i++)
        rand_seq[i] = rand_seq[i] / (double)M;
}

void init(double histo[]){
    for(int i=0; i<size; i++)
        histo[i] = 0;
}

void printSeq(double rand_seq[]){
    for(int i=0; i<size; i++)
        printf("%lf ",rand_seq[i]);
    printf("\n");
}

int main(int argc, char *argv[]){
    double rand_seq[size];
    double histo[10];
    init(histo);

    int n = atoi(argv[1]);
    switch(n){
        case 1:
            {
                Rand1(1,rand_seq);
                inRange(rand_seq);
                // printSeq(rand_seq);
                histogram(histo, rand_seq);
                break;
            }
        case 2:
            {
                Rand2(1,rand_seq);
                inRange(rand_seq);
                // printSeq(rand_seq);
                histogram(histo, rand_seq);
                // printf("%lf \n",histo2[3]);
                break;
            }
        case 3:
            {
                Rand3(1,rand_seq);
                inRange(rand_seq);
                // printSeq(rand_seq);
                histogram(histo, rand_seq);
                break;
            }
        default: break;
    }

    return 0;
}