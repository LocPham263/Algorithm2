#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    char name;
    int freq;
    struct Node* next;
} Node;

typedef struct Heap{
    int size;
    Node** heap;
} Heap;

int main(){
    int i;
	Heap* H = (Heap*) malloc(sizeof(Heap));
    H->size = 6;
    H->heap = (Node**) malloc(H->size*sizeof(Node*));
	H->heap[1] = NULL;

    /*
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->next = H->heap[1];
    H->heap[1] = tmp;
    */
   
    H->heap[1]->name = 'A';
    H->heap[1]->freq = 1;
    printf("%c %d\n", H->heap[1]->name, H->heap[1]->freq);
    printf("\n");
    return 0;
}