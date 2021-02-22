#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int vertex;
    int weigh;
    struct Node* next;
} Node;

typedef struct Graph{
    int numVertices;
    int* visited;
    Node** adjacent;
    Node** MST;
} Graph;

Node* newNode(Graph* G, int v);
Graph* newGraph(int v);
void addEdge(Graph* G, int u, int v, int w);
void addEdge_MST(Graph* G, int u, int v, int w);
void MST_PRIM(Graph* G, int r);
Node* min_adjacent(Graph* G, int v);
void printGraph(Graph* G);
void printMST(Graph* G);

int main(){
    Graph* G = newGraph(7);
    addEdge(G,0,1,20);
    addEdge(G,0,5,23);
    addEdge(G,0,6,1);
    addEdge(G,1,6,4);
    addEdge(G,1,2,15);
    addEdge(G,2,6,9);
    addEdge(G,2,3,3);
    addEdge(G,3,6,16);
    addEdge(G,3,4,17);
    addEdge(G,4,6,25);
    addEdge(G,4,5,28);
    addEdge(G,5,6,36);
    
    for(int i=0; i<7; i++) addEdge(G,i,i,0);
    printGraph(G);

    printf("\n\n");

    MST_PRIM(G,0);
    for(int i=0; i<7; i++) addEdge_MST(G,i,i,0);
    printMST(G);

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
    temp->visited = (int*) malloc(v*sizeof(int));
    temp->adjacent = (Node**) malloc(v*sizeof(Node*));
    temp->MST = (Node**) malloc(v*sizeof(Node*));

    for(int i=0; i<v; i++){
        temp->visited[i] = 0;
        temp->adjacent[i] = NULL;
        temp->MST[i] = NULL;
    }
    return temp;
}

void addEdge(Graph* G, int u, int v, int w){
    if(u!=v){
        Node* temp = newNode(G,v);
        temp->weigh = w;
        temp->next = G->adjacent[u];
        G->adjacent[u] = temp;

        temp = newNode(G,u);
        temp->weigh = w;
        temp->next = G->adjacent[v];
        G->adjacent[v] = temp; 
    }
    else{
        Node* temp = newNode(G,v);
        temp->next = G->adjacent[u];
        G->adjacent[u] = temp;
    }
}

void addEdge_MST(Graph* G, int u, int v, int w){
    if(u!=v){
        Node* temp = newNode(G,v);
        temp->weigh = w;
        temp->next = G->MST[u];
        G->MST[u] = temp;

        temp = newNode(G,u);
        temp->weigh = w;
        temp->next = G->MST[v];
        G->MST[v] = temp; 
    }
    else{
        Node* temp = newNode(G,v);
        temp->next = G->MST[u];
        G->MST[u] = temp;
    }
}

Node* min_adjacent(Graph* G, int v){
    Node* temp = G->adjacent[v]->next;
    Node* temp_w = temp;
    bool b=0;
    while(temp!=NULL){
        if(G->visited[temp->vertex]==0){
            temp_w = temp;
            b = 1;
            break;
        }
        temp = temp->next;
    }
    if(b==0) return temp;
    
    temp = temp_w;
    while(temp!=NULL){
        if((temp->weigh < temp_w->weigh) && (G->visited[temp->vertex]==0)){
            temp_w = temp;
        }
        temp = temp->next;
    }
    return temp_w;
}

void MST_PRIM(Graph* G, int r){
    int counter = 1;
    G->visited[r] = 1;

    while(counter < G->numVertices){
        int j=0;
        Node* temp = NULL;
        for(int i=0; i<G->numVertices; i++){
            if(G->visited[i]==1){
                Node* min = min_adjacent(G,i);
                if(temp==NULL){
                    temp = min;
                    j = i;
                }
                else if(min!=NULL && temp->weigh>min->weigh){
                    temp = min;
                    j = i;
                } 
            }
        }
        addEdge_MST(G,j,temp->vertex,temp->weigh);
        counter++;
        G->visited[temp->vertex] = 1;
    }
}

void printGraph(Graph* G){
    for(int i=0; i<G->numVertices; i++){
        printf("Vertex[%d]: ",i+1);
        Node* temp = G->adjacent[i];
        while(temp!=NULL){
            printf("%d|%d ",temp->vertex+1, temp->weigh);
            temp = temp->next;
        }
        printf("\n");
    }
}

void printMST(Graph* G){
    for(int i=0; i<G->numVertices; i++){
        printf("Vertex[%d]: ",i+1);
        Node* temp = G->MST[i];
        while(temp!=NULL){
            printf("%d|%d ",temp->vertex+1, temp->weigh);
            temp = temp->next;
        }
        printf("\n");
    }
}