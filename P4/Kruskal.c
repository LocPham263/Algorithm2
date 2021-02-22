#include <stdio.h>
#include <stdlib.h>
#define INFINITY 2147483647
#define SIZE 7
int parent[SIZE];
int MST[SIZE][SIZE];

void MST_init(int G[][SIZE]){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(G[i][j]==INFINITY) MST[i][j] = INFINITY;
            else MST[i][j] = 0;
        }
    }
}

void makeSet(int u){
    parent[u] = u;
}

int findSet(int u){
    while(parent[u]!=u) u = parent[u];
    return u;
}

void Union(int u, int v){
    int setA = findSet(u);
    int setB = findSet(v);
    parent[setA] = setB;
}

void MST_KRUSKAL(int G[][SIZE]){
    // Initialise MST and sets
    for(int i=0; i<SIZE; i++) makeSet(i);
    MST_init(G);

    // Kruskal algorithm
    int counter=0;
    while(counter < SIZE-1){
        int min_w = INFINITY;
        int src, dst;
        for(int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE; j++){
                if(findSet(i)!=findSet(j) && G[i][j]<min_w){
                    min_w = G[i][j];
                    src = i;
                    dst = j;
                }
            }
        }

        MST[src][dst] = MST[dst][src] = min_w; 
        Union(src,dst);
        counter++;
    }
}

void printGraph(int G[][SIZE]){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(G[i][j] == INFINITY || G[i][j] == 0) printf("X ");
            else printf("%d ",G[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int main(){
    int G[SIZE][SIZE] = {
                            {0, 20, INFINITY, INFINITY, INFINITY, 23, 1},
                            {20, 0, 15, INFINITY, INFINITY, INFINITY, 4},
                            {INFINITY, 15, 0, 3, INFINITY, INFINITY, 9},
                            {INFINITY, INFINITY, 3, 0, 17, INFINITY, 16},
                            {INFINITY, INFINITY, INFINITY, 17, 0, 28, 25},
                            {23, INFINITY, INFINITY, INFINITY, 28, 0, 36},
                            {1, 4, 9, 16, 25, 36, 0},      
                        };
    printf("\n***Note: Distance = 0 or infinity will be represented as X \n\n");
    printf("Input Graph: \n");
    printGraph(G);    

    MST_KRUSKAL(G);
    printf("Output MST: \n");
    printGraph(MST);

    return 0;
}