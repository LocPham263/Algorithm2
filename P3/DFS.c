#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int f_time, d_time;
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph{
    int numVertices;
    int* visited;
    Node** adjlist;
} Graph;

Node* newNode(int v);
Graph* newGraph(int v);
void addEdge(Graph* G, int src, int dst);
void DFS(Graph* G, int v);
void printGraph(Graph* G);
static int time = 0;

int main(){
    // Build the graph
    Graph* G = newGraph(6);
    addEdge(G,0,1);
    addEdge(G,0,3);
    addEdge(G,1,4);
    addEdge(G,3,1);
    addEdge(G,4,3);
    addEdge(G,2,4);
    addEdge(G,2,5);
    for(int i=0; i<6; i++) addEdge(G,i,i);
    printGraph(G);

    // Visit each node
    for(int i=0; i<6; i++){
        if(G->visited[i]==0) DFS(G,i);
    }

    // Print the result
    for(int i=0; i<6; i++){
        printf("Node %d: d_time = %d   f_time = %d \n",i+1, G->adjlist[i]->d_time, G->adjlist[i]->f_time);
    }
    printf("\n");
    return 0;
}

Node* newNode(int v){
    Node* temp = (Node*) malloc(sizeof(Node));
    temp -> d_time = 0;
    temp -> f_time = 0;
    temp -> vertex = v;
    temp -> next = NULL;
    return temp;
}

Graph* newGraph(int v){
    Graph* temp = (Graph*) malloc(sizeof(Graph));
    temp -> numVertices = v;
    temp -> visited = (int*) malloc(v*sizeof(int));
    temp -> adjlist = (Node**) malloc(v*sizeof(Node*));
    
    for(int i=0; i<v; i++){
        temp->visited[i] = 0;
        temp->adjlist[i] = NULL;
    }
    return temp;
}

void addEdge(Graph* G, int src, int dst){
    Node* temp = newNode(dst);
    temp->next = G->adjlist[src];
    G->adjlist[src] = temp;
}

void DFS(Graph* G, int v){
    Node* temp = G->adjlist[v];
    // printf("%d ",v+1); Traversal order
    G->visited[v] = 1;

    // Calculate discovery time
    time++;
    G->adjlist[v] -> d_time = time;

    while(temp!=NULL){
        if(G->visited[temp->vertex]==0){   
            DFS(G,temp->vertex);
        }
        temp = temp->next;
    }

    // Calculate finish time
    time++;
    G->adjlist[v] -> f_time = time;
}

void printGraph(Graph* G){
    for(int i=0; i<G->numVertices; i++){
        printf("Vertex[%d] ",i+1);
        Node* temp = G->adjlist[i];
        while(temp!=NULL){
            printf("%d ",temp->vertex+1);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("\n");
}