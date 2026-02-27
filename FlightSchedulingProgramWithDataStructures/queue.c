
#include "queue.h"


//-----------------------------------------------------------------------
// I wanted to complete every single function including the ones
// that I will not use in this program, since I consider it practice
//-----------------------------------------------------------------------

Queue CreateQueue()
{
    Queue q = malloc(sizeof(struct QueueRecord));
    if(q == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    q->front = NULL;
    q->rear = NULL;
    q->size = 0;

    MakeEmptyQueue(q);

    return q;
}

void MakeEmptyQueue(Queue q)
{
    if(!IsEmptyQueue(q)){
        struct QueueNode *ptr = q->front;
        while(ptr != NULL){
            struct QueueNode *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }

    struct QueueNode *dummy = malloc(sizeof(struct QueueNode));
    if(dummy == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    dummy->next = NULL;
    dummy->flightInfo = NULL;
    dummy->priority = 4;

    q->front = dummy;
    q->rear = dummy;
    q->size = 0;

}

void Enqueue(Flight* newFlight, Queue q)
{
    struct QueueNode *newNode = malloc(sizeof(struct QueueNode));
    if(newNode == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->flightInfo = newFlight;
    char type = newFlight->flightType;
    switch (type) {
        case 'E': newNode->priority = 3; break;
        case 'I': newNode->priority = 2; break;
        case 'D': newNode->priority = 1; break;
        default: return;
    }

    struct QueueNode *previous = q->front;
    struct QueueNode *current = q->front->next;
    while(current != NULL && current->priority >= newNode->priority){
        previous = current;
        current = current->next;
    }

    if(current == NULL){
        previous->next = newNode;
        newNode->next = NULL;
        q->rear = newNode;
    }
    else{
        previous->next = newNode;
        newNode->next = current;
    }

    q->size++;
}

Flight* Dequeue(Queue q)
{
    if(IsEmptyQueue(q)){
        printf("Queue is empty.\n");
        return NULL;
    }

    struct QueueNode *temp = q->front->next;
    Flight* info = temp->flightInfo;
    q->front->next = temp->next;

    if(temp == q->rear)
        q->rear = q->front;

    free(temp);
    q->size--;
    return info;
}

int IsEmptyQueue(Queue q)
{
    return q->size == 0;
}

int QueueSize(Queue q)
{
    return q->size;
}

Flight* FrontOfQueue(Queue q)
{
    if(IsEmptyQueue(q)){
        printf("Queue is empty.\n");
        return NULL;
    }

    return q->front->next->flightInfo;
}

Flight* RearOfQueue(Queue q)
{
    if(IsEmptyQueue(q)){
        printf("Queue is empty.\n");
        return NULL;
    }

    return q->rear->flightInfo;
}

void DisplayQueue(Queue q)
{
    if(IsEmptyQueue(q)){
        printf("Queue is empty.\n");
        return;
    }

    struct QueueNode *ptr = q->front->next;
    while(ptr != NULL){
        printFlightInformation(ptr->flightInfo);
        ptr = ptr->next;
    }
}

void deleteQueue(Queue toDeleteList)
{
    if(toDeleteList == NULL)
        return;

    struct QueueNode *ptr = toDeleteList->front;
    while(ptr != NULL){
        struct QueueNode *temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
    free(toDeleteList);
}
