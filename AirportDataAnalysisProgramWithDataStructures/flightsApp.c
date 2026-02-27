#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

struct AVLNode* loadFlights(char *fileName);
struct AVLNode* insertFlight(struct AVLNode* t, char *destination, char *airline, char type, char *date, int miles);
void infoFlights(struct AVLNode* t, char *destination);
void displayFlights(struct AVLNode* t);
struct Flight* findFurthestDestination(struct AVLNode* t);
void FurthestDestinations(struct AVLNode* t, struct Flight* highestMilesFlight);

int main (int argc, char **argv){

    struct AVLNode* myTree = NULL;
    int menuOption, flag = 1;

    if(argc == 1){
        printf("Please provide a file name: ");
        return 0;
    }

    myTree = loadFlights(argv[1]);

    printf("Welcome to data analysis @ Istanbul Airport\n");

    while (flag){
        printf("\n-------Menu-------\n"
               "(1)Insert flight\n"
               "(2)Display the full index of flights\n"
               "(3)Display the details of the flight\n"
               "(4)Display the furthest destination\n"
               "(5)Exit\n"
               "Enter your option:");
        scanf("%d", &menuOption);

        switch (menuOption) {

            case 1:{
                char destination[50], airline[50], type, date[11];
                int miles;

                printf("Please enter flight details:\n");
                printf("Destination: ");
                scanf(" %s", destination);
                printf("Airline: ");
                scanf(" %s", airline);
                printf("Type: ");
                scanf(" %c", &type);
                printf("Date: ");
                scanf(" %s", date);
                printf("Miles: ");
                scanf("%d", &miles);

                myTree = insertFlight(myTree, destination, airline, type, date, miles);
                printf("%s %s has been added successfully.\n", airline, destination);
                break;
            }
            case 2:{
                displayFlights(myTree);
                break;
            }
            case 3:{
                char destination[50];
                printf("Destination: ");
                scanf(" %s", destination);
                infoFlights(myTree,destination);
                break;
            }
            case 4:{
                printf("Detailed information of the furthest destination:\n");
                FurthestDestinations(myTree, findFurthestDestination(myTree));
                break;
            }
            case 5: {
                flag = 0;
                break;
            }
            default:{
                printf("Option %d can't be recognized.\n", menuOption);
            }
        }
    }

    myTree = MakeEmptyTree(myTree);
    return 0;
}

struct AVLNode* insertFlight(struct AVLNode* t, char *destination, char *airline, char type, char *date, int miles) {
//    allocating memory for flight
    struct Flight *f = malloc(sizeof(struct Flight));
    if (f == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

//    creating a flight
    strcpy(f->destination, destination);
    strcpy(f->airline, airline);
    f->type = type;
    strcpy(f->date, date);
    f->miles = miles;
    f->next = NULL;

    t = InsertFlight(t, f);

    return t;
}

struct AVLNode* loadFlights(char *fileName){

//    reaching to the file
    FILE *file;
    file = fopen(fileName, "r");
    if (file == NULL){
        printf("File cannot be opened.\n");
        exit(1);
    }

//    reading from the file
    struct AVLNode *t = NULL;
    char line[120];
    while(fgets(line, sizeof(line), file) != NULL){

//        creating the flight structure
        struct Flight *f = malloc(sizeof(struct Flight));
        if (f == NULL){
            printf("Memory allocation failed.\n");
            exit(1);
        }

        f->next = NULL;

//        string parsing
        char *token;
        token = strtok(line, ";");
        strcpy(f->destination, token);

        token = strtok(NULL, ";");
        strcpy(f->airline, token);

        token = strtok(NULL, ";");
        f->type = token[0];

        token = strtok(NULL, ";");
        strcpy(f->date, token);

        token = strtok(NULL, "\n");
        f->miles = atoi(token);

        t = InsertFlight(t, f);
    }

    fclose(file);
    return t;
}

void displayFlights(struct AVLNode* t){
    if (t == NULL)
        return;

    DisplayTree(t);
}

void infoFlights(struct AVLNode* t, char *destination){
    if (t == NULL)
        return;

    struct Flight* f = FindDestination(t, destination);
    if (f == NULL)
        printf("There is no available flight whose name is %s.\n", destination);
    else
        while (f != NULL){ // printing the flights with the correct name
            PrintFlightDetails(f);
            f = f->next;
        }

//        Regarding the COMPLEXITY of this function:

//    Finding the destinations take O(logN) and N is the number of AVL nodes.
//    Printing the flights take O(N) and this N is the number of linked list nodes.
//    If we name first N as N1 and second N as N2, the complexity of function becomes O(logN1 + N2).
}

struct Flight* findFurthestDestination(struct AVLNode* t){
    if (t == NULL)
        return NULL;

//    looking at left subtree
    struct Flight* max;
    max = findFurthestDestination(t->left);
//    if there are no left child max can be NULL therefore condition
//    of the below if statement should cover it as well

//    looking at current node
    struct Flight* current = t->data;
    while (current != NULL){
        if (max == NULL || max->miles < current->miles)
            max = current;
        current = current->next;
    }

//    looking at right subtree
//    created rightMax not to overwrite max
    struct Flight* rightMax;
    rightMax = findFurthestDestination(t->right);

//    finding the furthest
    if (rightMax != NULL && (max == NULL || rightMax->miles > max->miles))
        max = rightMax;

    return max;
}

void FurthestDestinations(struct AVLNode* t, struct Flight* highestMilesFlight){
    if (t == NULL || highestMilesFlight == NULL)
//        condition is set like this to prevent crashing when function
//        is called when there are no flights
        return;

//    looking at left subtree
    FurthestDestinations(t->left, highestMilesFlight);

//    printing results
    struct Flight* current = t->data;
    while (current != NULL){
        if (current->miles == highestMilesFlight->miles)
            PrintFlightDetails(current);
        current = current->next;
    }

//    looking at right subtree
    FurthestDestinations(t->right, highestMilesFlight);

//          Regarding the COMPLEXITY of this function:
//    We traverse the entire AVL tree no matter what, therefore;
//    complexity is O(N) if number of nodes is N.
}
