#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INFINITE 2147483647

typedef struct Node{
    int vertex;
    int weigh;
    struct Node* next;
} Node;

typedef struct SPT{
    int d;
    int pi;
    bool b;
} SPT;

typedef struct Graph{
    int numVertices;
    Node** adjacent;
    SPT* SPT;
} Graph;

Node* newNode(Graph* G, int v);
Graph* newGraph(int v);
void addEdge(Graph* G, int u, int v, int w);
void RELAX(Graph* G, int u, int v, int w);
Node* min_adjacent(Graph* G, int v);
void Dijksta(Graph* G, int s);
void printGraph(Graph* G);
void printSPT(Graph* G);

int main(){
    Graph* G = newGraph(8);
    addEdge(G,0,1,5);
    addEdge(G,0,4,9);
    addEdge(G,0,7,8);

    addEdge(G,1,7,4);
    addEdge(G,1,3,15);
    addEdge(G,1,2,12);

    addEdge(G,2,3,3);
    addEdge(G,2,6,11);

    addEdge(G,3,6,9);

    addEdge(G,4,7,5);
    addEdge(G,4,5,4);
    addEdge(G,4,6,20);

    addEdge(G,5,2,1);
    addEdge(G,5,6,13);

    addEdge(G,7,5,6);
    addEdge(G,7,2,7);

    
    for(int i=0; i<8; i++) addEdge(G,i,i,0);
    printGraph(G);

    printf("\n");

    Dijksta(G,0);
    printSPT(G);

    return 0;
}

Node* newNode(Graph* G, int v){
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->vertex = v;
    temp->weigh = 0;
    temp->next = NULL;
    return temp;
}

Graph* newGraph(int v){
    Graph* temp = (Graph*) malloc(sizeof(Graph));
    temp->numVertices = v;
    temp->adjacent = (Node**) malloc(v*sizeof(Node*));
    temp->SPT = (SPT*) malloc(v*sizeof(SPT));

    for(int i=0; i<v; i++){
        temp->adjacent[i] = NULL;
        (temp->SPT+i)->d = INFINITE;
        (temp->SPT+i)->pi = 0;
        (temp->SPT+i)->b = 0;
    }
    return temp;
}

void addEdge(Graph* G, int u, int v, int w){
    Node* temp = newNode(G,v);
    temp->weigh = w;
    temp->next = G->adjacent[u];
    G->adjacent[u] = temp;
}

void RELAX(Graph* G, int u, int v, int w){
    if((G->SPT+v)->d > (G->SPT+u)->d + w){
        (G->SPT+v)->d = (G->SPT+u)->d + w;
        (G->SPT+v)->pi = u;
    }
}

Node* min_adjacent(Graph* G, int v){
    Node* temp = G->adjacent[v]->next;
    Node* temp_w = temp;
    bool b=0;
    while(temp!=NULL){
        if((G->SPT+temp->vertex)->b == 0 && (G->SPT+temp->vertex)->pi == v){
            temp_w = temp;
            b = 1;
            break;
        }
        temp = temp->next;
    }
    if(b==0) return temp;
    
    temp = temp_w;
    while(temp!=NULL){
        if(((G->SPT+temp->vertex)->d < (G->SPT+temp_w->vertex)->d) && ((G->SPT+temp->vertex)->b == 0) && (G->SPT+temp->vertex)->pi == v){
            temp_w = temp;
        }
        temp = temp->next;
    }
    return temp_w;
}

void Dijksta(Graph* G, int s){
    int counter = 1;
    (G->SPT+s)->b = 1;
    (G->SPT+s)->d = 0;
    Node* temp = G->adjacent[s]->next;
    while(temp!=NULL){
        RELAX(G,s,temp->vertex,temp->weigh);
        temp = temp->next;
    }

    while(counter < G->numVertices){
        temp = NULL;
        for(int i=0; i<G->numVertices; i++){
            if((G->SPT+i)->b==1){
                Node* min = min_adjacent(G,i);
                if(temp==NULL)  
                    temp = min;
                else if(min!=NULL && (G->SPT+temp->vertex)->d > (G->SPT+min->vertex)->d) 
                    temp = min;
            }
        }

        (G->SPT+temp->vertex)->b = 1;
        temp = G->adjacent[temp->vertex];
        Node* temp1 = temp->next;
        while(temp1!=NULL){
            if((G->SPT+temp1->vertex)->b == 0) RELAX(G,temp->vertex,temp1->vertex,temp1->weigh);
            temp1 =  temp1->next;
        }
        counter++;
    }
}

void printGraph(Graph* G){
    for(int i=0; i<G->numVertices; i++){
        printf("Vertex[%d]: ",i);
        Node* temp = G->adjacent[i];
        while(temp!=NULL){
            printf("%d|%d ",temp->vertex, temp->weigh);
            temp = temp->next;
        }
        printf("\n");
    }
}

void printSPT(Graph* G){
    for(int i=0; i<G->numVertices; i++){
        printf("Node %d has pi = %d | Distance to root = %d\n",i,(G->SPT + i)->pi,(G->SPT + i)->d);
    }
    printf("\n");
}