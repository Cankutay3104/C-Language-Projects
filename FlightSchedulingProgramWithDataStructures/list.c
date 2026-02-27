
#include "list.h"

//-----------------------------------------------------------------------
// I wanted to complete every single function including the ones
// that I will not use in this program, since I consider it practice
//-----------------------------------------------------------------------

List CreateList()
{
    List l = malloc(sizeof(struct ListRecord));
    if(l == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    l->head = NULL;
    l->tail = NULL;
    l->length = 0;

    MakeEmptyList(l);

    return l;
}

void MakeEmptyList(List l)
{
    if(!IsEmptyList(l)){
        struct ListNode *ptr = l->head;
        while(ptr != NULL){
            struct ListNode *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }

    struct ListNode *dummy = malloc(sizeof(struct ListNode));
    if(dummy == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    dummy->flightInformation = NULL;
    dummy->next = NULL;

    l->head = dummy;
    l->tail = dummy;
    l->length = 0;
}

void InsertList(List l, int pos, Flight* data)
{
    if(pos < 0 || pos > l->length){
        printf("Invalid position.\n");
        return;
    }

    struct ListNode* current = l->head;
    for (int i = 0; i < pos; ++i) {
        current = current->next;
    }

    struct ListNode* newNode = malloc(sizeof(struct ListNode));
    if(newNode == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->flightInformation = data;
    newNode->next = current->next;
    current->next = newNode;

    if(l->tail == current){
        l->tail = newNode;
    }

    l->length++;
}

void InsertToListEnd(List l, Flight* flight){
    struct ListNode* newNode = malloc(sizeof(struct ListNode));
    if(newNode == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->flightInformation = flight;
    newNode->next = NULL;
    l->tail->next = newNode;
    l->tail = newNode;
    l->length++;
}

void InsertToListHead(List l, Flight* flight){
    struct ListNode* newNode = malloc(sizeof(struct ListNode));
    if(newNode == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->flightInformation = flight;
    newNode->next = l->head->next;
    l->head->next = newNode;

    if(l->tail == l->head){
        l->tail = newNode;
    }

    l->length++;
}

void InsertListOrderedByReadyTime(List l, Flight* newFlight){
    struct ListNode *newNode = malloc(sizeof(struct ListNode));
    if(newNode == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->flightInformation = newFlight;

    struct ListNode *previous = l->head;
    struct ListNode *current = l->head->next;
    while(current != NULL && current->flightInformation->readyTime < newNode->flightInformation->readyTime){
        previous = current;
        current = current->next;
    }

    if(current == NULL){
        previous->next = newNode;
        newNode->next = NULL;
        l->tail = newNode;
    }
    else{
        previous->next = newNode;
        newNode->next = current;
    }

    l->length++;
}

Flight* DeleteFirstNode(List l){
    if(IsEmptyList(l)){
        printf("List is empty.\n");
        return NULL;
    }

    struct ListNode *temp = l->head->next;
    Flight* data = temp->flightInformation;

    l->head->next = l->head->next->next;

    if(temp == l->tail){
        l->tail = l->head;
    }

    free(temp);
    l->length--;

    return data;
}

void DeleteFromList(List l, Flight* v)
{
    if(IsEmptyList(l))
        printf("List is empty.\n");
    else{
        struct ListNode *previous = l->head;
        struct ListNode *current = l->head->next;

        while(current != NULL && current->flightInformation != v){
            previous = current;
            current = current->next;
        }

        if(current == NULL){
            printf("There is no such element in the list.\n");
            return;
        }

        previous->next = current->next;
        if(current == l->tail)
            l->tail = previous;

        free(current);
        l->length--;
    }
}

int IsEmptyList(List l)
{
    return l->length == 0;
}

int ListSize(List l)
{
    return l->length;
}

Flight* HeadOfList(List l)
{
    if(!IsEmptyList(l))
        return l->head->next->flightInformation;
    else{
        printf("List is empty.\n");
        return NULL;
    }
}

Flight* TailOfList(List l)
{
    if(!IsEmptyList(l))
        return l->tail->flightInformation;
    else{
        printf("List is empty.\n");
        return NULL;
    }
}

void DisplayList(List l)
{
    struct ListNode *ptr = l->head->next;
    while(ptr != NULL){
        printFlightInformation(ptr->flightInformation);
        ptr = ptr->next;
    }
}

void deleteList(List toDeleteList)
{
    if(toDeleteList == NULL)
        return;

    struct ListNode *ptr = toDeleteList->head;
    while(ptr != NULL){
        struct ListNode *temp = ptr;
        ptr = ptr->next;

        if(temp->flightInformation != NULL){
            free(temp->flightInformation);
        }
        free(temp);
    }

    free(toDeleteList);
}
