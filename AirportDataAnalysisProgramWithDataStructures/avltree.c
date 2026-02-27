#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"


struct AVLNode* CreateTree(void){
    return NULL;
}

struct AVLNode* MakeEmptyTree(struct AVLNode* t)
{
    if (t == NULL)
        return NULL;

    t->left = MakeEmptyTree(t->left);
    t->right = MakeEmptyTree(t->right);

//    freeing the flights
    struct Flight *f = t->data;
    while (f != NULL){
        struct Flight *temp = f;
        f = f->next;
        free(temp);
    }

    free(t);
    return NULL;
}

struct AVLNode* InsertFlight(struct AVLNode* t, struct Flight* flight){
    if (t == NULL){
        t = malloc(sizeof(struct AVLNode));
        if (t == NULL){
            printf("Memory allocation failed.\n");
            exit(1);
        }

        t->data = flight;
        flight->next = NULL;
        t->left = t->right = NULL;
        t->height = 0;

        return t;
    }

    int result = strcmp(flight->destination, t->data->destination);
    int balance;
    if (result < 0){
        t->left = InsertFlight(t->left, flight);

        balance = AVLTreeHeight(t->left) - AVLTreeHeight(t->right);
//        To see whether left side is heavy or not
        if (balance == 2){
            if (strcmp(flight->destination, t->left->data->destination) < 0)
                t = SingleRotateWithRight(t);   // LL heavy
            else
                t = DoubleRotateWithLeft(t);    // LR heavy
        }
    }
    else if (result > 0){
        t->right = InsertFlight(t->right, flight);

        balance = AVLTreeHeight(t->left) - AVLTreeHeight(t->right);
//        To see whether right side is heavy or not
        if (balance == -2){
            if (strcmp(flight->destination, t->right->data->destination) > 0)
                t = SingleRotateWithLeft(t); // RR heavy
            else
                t = DoubleRotateWithRight(t); // RL heavy
        }
    }
    else{
//        Destinations are the same, therefore they should be in the same node
        flight->next = t->data;
        t->data = flight;
        return t;   // Since no rotation is needed simply return
    }

    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) +1;

    return t;
}

//right rotation
struct AVLNode*  SingleRotateWithRight(struct AVLNode*  k2)
{
    struct AVLNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = Max(AVLTreeHeight( k2->left), AVLTreeHeight(k2->right)) +1;
    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) +1;

    return k1;
}

//left rotation
struct AVLNode*  SingleRotateWithLeft(struct AVLNode*  k1)
{
    struct AVLNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) +1;
    k2->height = Max(AVLTreeHeight( k2->left), AVLTreeHeight(k2->right)) +1;

    return k2;
}

//left and right rotation
struct AVLNode*  DoubleRotateWithLeft(struct AVLNode*  k3)
{
    k3->left = SingleRotateWithLeft(k3->left);
    return SingleRotateWithRight(k3);

//    Clearer manual pointer version is below, since this version is longer
//    I wrote it just to demonstrate and see it clearly.
/*
    struct AVLNode* k2 = k3->left;
    struct AVLNode* k1 = k2->right;

    k2->right = k1->left;
    k1->left = k2;

    k3->left = k1->right;
    k1->right = k3;

    k2->height = Max(AVLTreeHeight( k2->left), AVLTreeHeight(k2->right)) +1;
    k3->height = Max(AVLTreeHeight(k3->left), AVLTreeHeight(k3->right)) +1;
    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) +1;

    return k1;
*/
}

// right and left rotation
struct AVLNode*  DoubleRotateWithRight(struct AVLNode* k3)
{
    k3->right = SingleRotateWithRight(k3->right);
    return SingleRotateWithLeft(k3);

//    Clearer manual pointer version is below, since this version is longer
//    I wrote it just to demonstrate and see it clearly.
/*
    struct AVLNode* k2 = k3->right;
    struct AVLNode* k1 = k2->left;

    k2->left = k1->right;
    k1->right = k2;

    k3->right = k1->left;
    k1->left = k3;

    k3->height = Max(AVLTreeHeight(k3->left), AVLTreeHeight(k3->right)) +1;
    k2->height = Max(AVLTreeHeight( k2->left), AVLTreeHeight(k2->right)) +1;
    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) +1;

    return k1;
*/
}

int Max(int x, int y)
{
    if (x >= y)
        return x;
    else
        return y;
}

int AVLTreeHeight(struct AVLNode* t)
{
    if (t == NULL)
        return -1;

    return t->height;
}

void DisplayTree(struct AVLNode* t)
{
    if (t == NULL)
        return;

    DisplayTree(t->left);
    struct Flight *f = t->data;
    while (f != NULL){
        PrintFlightDetails(f);
        f = f->next;
    }
    DisplayTree(t->right);
}

void PrintFlightDetails(struct Flight* flight){
    printf("%s %s %c %s %d\n", flight->destination, flight->airline, flight->type, flight->date, flight->miles);
}

struct Flight* FindDestination(struct AVLNode *t, char *destination){
    if (t == NULL)
        return NULL;

    int result = strcmp(destination, t->data->destination);
    if (result < 0)
        return FindDestination(t->left, destination);
    else if (result > 0)
        return FindDestination(t->right, destination);
    else
        return t->data;
}



