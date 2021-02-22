#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 100

typedef struct Queue{
    int queue[SIZE];
    int left;
    int right;
} Queue;

typedef struct Node{
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph{
    int nunmVertices;
    int* visited;
    Node** adjlist;
    Queue* Queue;
} Graph;

Node* newNode(int v);
Graph* newGraph(int v);
void addEdge(Graph* G, int src, int dst);
void BFS(Graph* G, int v);
void printGraph(Graph* G);

void enqueue(Queue* q, int n);
int dequeue(Queue* q);
void printQueue(Queue* q);
bool isEmpty(Queue* q);
bool isFull(Queue* q);

int main(){
    Graph* G = newGraph(10);
    addEdge(G,1,2);
    addEdge(G,1,3);
    addEdge(G,1,7);
    addEdge(G,1,9);
    addEdge(G,2,4);
    addEdge(G,2,8);
    addEdge(G,3,4);
    addEdge(G,3,5);
    addEdge(G,7,6);
    addEdge(G,9,8);
    addEdge(G,5,6);
    addEdge(G,8,0);
    for(int i=0; i<10; i++){
        Node* temp = newNode(i);
        temp->next = G->adjlist[i];
        G->adjlist[i] = temp;
    }
    printGraph(G);
    
    for(int i=0; i<10; i++){
        if(G->visited[i]==0) BFS(G,i);
    }
    printf("\n");
    return 0;
}

Node* newNode(int v){
    Node* temp = (Node*) malloc(sizeof(Node));
    temp -> vertex = v;
    temp -> next = NULL;
    return temp;
}

Graph* newGraph(int v){
    Graph* temp = (Graph*) malloc(sizeof(Graph));
    temp -> nunmVertices = v;
    temp -> visited = (int*) malloc(v*sizeof(int));
    temp -> adjlist = (Node**) malloc(v*sizeof(Node*));
    temp -> Queue   = (Queue*) malloc(sizeof(Queue));

    for(int i=0; i<v; i++){
        temp -> visited[i] = 0;
        temp -> adjlist[i] = NULL; 
    }

    return temp;
}

void addEdge(Graph* G, int src, int dst){
    Node* temp = newNode(dst);
    temp->next = G->adjlist[src];
    G->adjlist[src] = temp;

    temp = newNode(src);
    temp->next = G->adjlist[dst];
    G->adjlist[dst] = temp; 
}

void BFS(Graph* G, int v){
    Node* temp = G->adjlist[v];
    enqueue(G->Queue,v);
    G->visited[v] = 1;

    while(!isEmpty(G->Queue)){
        temp = G->adjlist[dequeue(G->Queue)];
        printf("%d ",temp->vertex);
        // Enqueue all adjacent nodes 
        while(temp!=NULL){
            if(G->visited[temp->vertex]==0){
                enqueue(G->Queue,temp->vertex);
                G->visited[temp->vertex] = 1;
            }
            temp = temp->next;
        }
    }
}

void printGraph(Graph* G){
    for(int i=0; i<G->nunmVertices; i++){
        printf("Vertex[%d] ",i);
        Node* temp = G->adjlist[i];
        while(temp!=NULL){
            printf("%d ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

bool isEmpty(Queue* q){
    return q->left == q->right;
}

bool isFull(Queue* q){
    return q->right == SIZE;
}

void enqueue(Queue* q, int n){
    if(!isFull(q)){
        q->queue[q->right] = n;
        q->right++;
    }
}

int dequeue(Queue* q){
    if(!isEmpty(q)){
        int temp = q->queue[q->left];
        q->left++;
        return temp;
    }else{printf("Queue is full");}
}

void printQueue(Queue* q){
    int temp = q->left;
    while(temp!=q->right){
        printf("%d ",q->queue[temp]); 
        temp++;
    }
    printf("\n");
}
