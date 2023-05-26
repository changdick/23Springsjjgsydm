//
// Created by 83923 on 2023/4/15.
//

#ifndef TREE1_QUEUE_H
#define TREE1_QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include "binarytreea.h"


typedef Binarytree* queueDataType;
typedef struct node {
    queueDataType data;
    struct node* next;
}queuenode;
typedef struct queue{
    queuenode * front;
    queuenode * rear;
}Queue;
Queue* createnewqueue(){
    Queue * newqueue = (Queue*)malloc(sizeof (Queue));
    newqueue->front = (queuenode*) malloc((sizeof (queuenode)));
    newqueue->rear = newqueue->front;
    return newqueue;
}
queuenode * createnode(){
    queuenode * newnode = (queuenode*) malloc((sizeof (queuenode)));
    return newnode;
}
void enqueue(Queue* cqueue, queueDataType dataval){
    queuenode* newnode = createnode();
    newnode->data = dataval;
    newnode->next = NULL;
    cqueue->rear->next = newnode;
    cqueue->rear = newnode;
}
queueDataType dequeue(Queue * cqueue){
    cqueue->front = cqueue->front->next;
    return cqueue->front->data;
}
int queueempty(Queue* cqueue){
    return cqueue->front == cqueue->rear;
}
void printqueue(Queue * cqueue){
    queuenode * index = cqueue->front;
    while(index->next){
        index = index->next;
        printf(" %d",index->data->data);   //queue是针对二叉树结点设计的，用其他地方得改
    }
}


#endif //TREE1_QUEUE_H
