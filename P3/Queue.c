#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 100
typedef struct Queue{
    int queue[SIZE];
    int left;
    int right;
} Queue;

void enqueue(Queue* q, int n);
int dequeue(Queue* q);
void printQueue(Queue* q);
bool isEmpty(Queue* q);
bool isFull(Queue* q);

int main(){
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->left = q->right = 0;
    for(int i=1; i<=3; i++){
        enqueue(q,i);
    }

    printQueue(q);
    dequeue(q);
    printQueue(q);
    enqueue(q,4);
    printQueue(q);
    dequeue(q); dequeue(q); dequeue(q);
    printQueue(q);
    dequeue(q);
    printQueue(q);
    return 0;
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