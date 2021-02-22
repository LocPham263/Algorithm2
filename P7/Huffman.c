#include <stdio.h>
#include <stdlib.h>
#define SIZE 31
#define heap_SIZE 6
char s[SIZE] = "ABBCACCEACBCCFABCDAFEABFFADBBC ";
typedef struct Node{
    char name;
    int freq;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Heap{
    int size;
    int capacity;
    Node** heap;
} Heap;

Node* newNode(char name, int freq);
Heap* newHeap(int size);
int Freq(char c);
void MinHeapify(Heap* H, int i);
void HeapBottomUp(Heap* H);
Node* Huffman(Heap* H);
void Encode(Node* root, int code[], int index);
Node* Extract_Min(Heap* H);
void Insert(Heap* H, Node* z);
void swapNode(Node* A, Node* B);
void printHeap(Heap* H);

int main(){
    Heap* H = newHeap(heap_SIZE);
    HeapBottomUp(H);
   
    Node* tmp = Huffman(H);
    H->size = heap_SIZE*2-1;
    
    int code[heap_SIZE];
    Encode(tmp,code,0);
    
    return 0;
}

Node* newNode(char name, int freq){
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->name = name;
    tmp->freq = freq;
    tmp->left = tmp->right = NULL;

    return tmp;
}

Heap* newHeap(int size){
    // Heap allocation
    Heap* H = (Heap*) malloc(sizeof(Heap));
    H->size = size;
    H->capacity = 2*H->size-1;
    H->heap = (Node**) malloc(H->capacity*sizeof(Node*));
    // Heap initialization
    for(int i=0; i<H->size; i++)    
        H->heap[i] = newNode(65+i,Freq(65+i));
    
    return H;
}

int Freq(char c){
    int count = 0;
    for(int i=0; s[i]!=' '; i++){
        if(s[i] == c) count++;
    }
    return count;
}

void MinHeapify(Heap* H, int i){
    int left = 2*i+1;
    int right = 2*i+2;
    int min = i;
    if(left < H->size && H->heap[min]->freq > H->heap[left]->freq) 
        min = left;
    if(right < H->size && H->heap[min]->freq > H->heap[right]->freq) 
        min = right;
    if(min != i){
        swapNode(H->heap[min],H->heap[i]);
        MinHeapify(H,min);
    }
}

void HeapBottomUp(Heap* H){
    for(int i=(H->size-1)/2; i>=0; i--)
        MinHeapify(H,i);
}

Node* Huffman(Heap* H){
    while(H->size!=1){
        Node* z = newNode('z',0);
        z->left = Extract_Min(H);
        z->right = Extract_Min(H);
        z->freq = z->left->freq + z->right->freq;
        Insert(H,z);
    }
    return H->heap[0];
}

void Encode(Node* root, int code[], int index){
    if(root->left != NULL){
        code[index] = 0;
        Encode(root->left, code, index + 1);
    }
    if(root->right != NULL){
        code[index] = 1; 
        Encode(root->right, code, index + 1);
    }
    if(root->left == NULL && root->right == NULL){
        printf("%c ",root->name);
        for(int i=0; i<index; i++) 
            printf("%d",code[i]);
        printf("\n");
    }
}

Node* Extract_Min(Heap* H){
    swapNode(H->heap[0], H->heap[H->size-1]);
    H->heap[H->capacity-1] = newNode('x',H->capacity);
    swapNode(H->heap[H->size-1],H->heap[H->capacity-1]);

    Node* min = H->heap[H->capacity-1];
    H->size--;
    H->capacity--;

    MinHeapify(H,0);
    return min;
}

void Insert(Heap* H, Node* z){
    H->size++;
    H->heap[H->size-1] = z;

    int count = H->size-1;
    while(count > 0 && H->heap[(H->size-1)/2] > H->heap[count]){
        swapNode(H->heap[(H->size-1)/2], H->heap[count]);
        count = (count-1)/2;
    }
}

void swapNode(Node* A, Node* B){
    Node tmp = *A;
    *A = *B;
    *B = tmp;
}

void printHeap(Heap* H){
    for(int i=0; i<H->size; i++){
        printf("%c %d || ", H->heap[i]->name, H->heap[i]->freq);
    }
    printf("\n");
}