#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "list.h"
#include "queue.h"

// To parse input from program arguments
void parseInput(char **, int *, int *, int *, int *);

// To initialise, create and populate the flight list with random flight data
List createFlightList(int, int, int);

//To initialise queue of the arrived flights and runway availability data
int* initialiseSimulator(Queue*, int);

//Adds the arrived flight into the priority queue
void newFlight(Flight*, Queue);

//Randomly assign an available runway to the flight
void serveFlight(Flight*, int*, int);

//Print the statistical data of the simulation run
void reportStatistics(List, int, int, int);

//Clear dynamically allocated memories
void exitFromTheSimulation(List, Queue, int *);

int main(int argc, char *argv[])
{
//    Seeding rand()
    srand(time(NULL));

    int noOfFlights, noOfRunways, maxReadyTime, maxServiceTime;

//    Command line argument validation
    if(argc != 5){
        printf("Argument count doesn't match!!\n");
        return 1;
    }

//    Getting the input
    parseInput(argv, &noOfFlights, &noOfRunways, &maxReadyTime, &maxServiceTime);

//    Creating sorted list
    List flight_list = createFlightList(noOfFlights, maxReadyTime, maxServiceTime);

//    Starting simulator
    Queue flight_queue;
    int *runways = initialiseSimulator(&flight_queue, noOfRunways);

//    Helper array to track when the runways are freed and available again
    int *runwayFreedTime = malloc(sizeof(int) * noOfRunways);
    if(runwayFreedTime == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

//    New list to store completed flights for "Report" part
    List completedList = CreateList();

    int clock_time = 0;
    int servedFlights = 0;

    while(servedFlights < noOfFlights){

//        Checking whether there is a flight that is ready
        while(!IsEmptyList(flight_list)){
            Flight *next_flight = HeadOfList(flight_list);

            if (next_flight->readyTime <= clock_time){
                Flight* arrivingFlight = DeleteFirstNode(flight_list);

                newFlight(arrivingFlight, flight_queue);
            }
            else{
//                If the flight at the head of the list is not ready then,
//                no subsequent flight can be ready since the list is sorted.
                break;
            }
        }

//        Freeing runways
        for (int i = 0; i < noOfRunways; ++i) {
//            If runway is busy and its freed time has passed
            if(runways[i] == 0 && runwayFreedTime[i] <= clock_time){
                runways[i] = 1;
                servedFlights++; // a flight is done
            }
        }

        int continuing = 1;
        while(continuing){
//            If no flights waiting
            if(IsEmptyQueue(flight_queue))
                continuing = 0;

//            If there are flights in the queue
            else{
                int available_found = 0;
                for (int i = 0; i < noOfRunways; ++i) {
                    if(runways[i] == 1)
                        available_found = 1;
                }

                if(available_found){
//                    Getting the flight with the highest priority
                    Flight *flightToDepart = Dequeue(flight_queue);

//                    Assigning the flight to a random runway that is available
                    serveFlight(flightToDepart, runways, noOfRunways);

//                    Updating the start time of the flight
                    flightToDepart->serviceStartTime = clock_time;

//                    Calculating when will the runway be freed
                    int runway_index = flightToDepart->runwayNumber - 1;
                    runwayFreedTime[runway_index] = clock_time + flightToDepart->serviceTime;

//                    Inserting to the completed list for reports
                    InsertToListEnd(completedList, flightToDepart);
                }
                else{
                    continuing = 0;
                }
            }
        }

//        Advancing the clock
        int nextEventTime = -1;

//        Checking new arrivals
        if (!IsEmptyList(flight_list))
//            Advancing clock if there is another event
            nextEventTime = HeadOfList(flight_list)->readyTime;

        for (int i = 0; i < noOfRunways; ++i) {
            if(runways[i] == 0){
                if(nextEventTime == -1 || runwayFreedTime[i] < nextEventTime)
//                    Advancing the clock to when the runway is freed and is available again
                    nextEventTime = runwayFreedTime[i];
            }
        }

//        Updating main clock
        if(nextEventTime != -1 && nextEventTime > clock_time)
            clock_time = nextEventTime;
        else
            if(servedFlights < noOfFlights)
                clock_time++;
    }

    reportStatistics(completedList, noOfRunways, noOfFlights, clock_time);

//    Freeing the memory spaces
    exitFromTheSimulation(completedList, flight_queue, runways);
    free(runwayFreedTime);
    deleteList(flight_list); // flight_list was empty but not freed in the program

    return 0;
}

void parseInput(char *programArguments[], int *noOfFlights, int *noOfRunways, int *maxReadyTime, int *maxServiceTime){
//    Converting the string inputs to integers
    *noOfFlights = atoi(programArguments[1]);
    *noOfRunways = atoi(programArguments[2]);
    *maxReadyTime = atoi(programArguments[3]);
    *maxServiceTime = atoi(programArguments[4]);
}

List createFlightList(int numberOfFlights, int maxReadyTime, int maxServiceTime){
    List flight_list = CreateList();

    for (int i = 0; i < numberOfFlights; ++i) {
//        Creating the flights and inserting them to the list
        Flight *newFlight = createRandomFlight(maxReadyTime, maxServiceTime);

        InsertListOrderedByReadyTime(flight_list, newFlight);
    }

    return flight_list;
}

int* initialiseSimulator(Queue* flightQueue, int noOfRunways){
    *flightQueue = CreateQueue();

    int *runways = malloc(sizeof(int) * noOfRunways);
    if(runways == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

//    Initializing the runways as available
    for (int i = 0; i < noOfRunways; ++i) {
        runways[i] = 1;
    }

    return runways;
}

void newFlight(Flight* flightData, Queue flightQueue){
    Enqueue(flightData, flightQueue);
}

// int *runways is the runway array
void serveFlight(Flight* flightData, int* runways, int runwayNumber){
    int availableRunways[runwayNumber];
    int count = 0;

//    Finding all available runways
    for (int i = 0; i < runwayNumber; ++i) {
        if(runways[i] == 1){
            availableRunways[count++] = i;
        }
    }

//    Picking a random runway
    int random = rand() % count;
    int selectedRunway = availableRunways[random];

//    Updating runway as busy
    runways[selectedRunway] = 0;

//    Updating flight data
    flightData->runwayNumber = selectedRunway + 1;
}

void reportStatistics(List flightsDataList, int noOfRunways, int numberOfFlights, int clockTime){

//    Counters for flight types
    int countE = 0, countI = 0, countD = 0;

//    Counters for runways
    int *runwayCounts = malloc(sizeof(int) * noOfRunways);
    if(runwayCounts == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < noOfRunways; ++i) {
        runwayCounts[i] = 0;
    }

    double total_wait = 0.0;
    int max_wait = 0;

//    Helper struct to count airline-destination frequencies,
//    created inside the function since it will only be used here.
    typedef struct{
        char place[5];
        int count;
    }FrequencyRecord;

//    Allocating memory for the airline-destination statistics,
//    also tracking each different occurrence.
    FrequencyRecord *airlineProperties = malloc(sizeof(FrequencyRecord) * numberOfFlights);
    int uniqueAirlineCount = 0;

    FrequencyRecord *destinationProperties = malloc(sizeof(FrequencyRecord) * numberOfFlights);
    int uniqueDestinationCount = 0;

    if(airlineProperties == NULL || destinationProperties == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

//    Going through the list
    struct ListNode *current = flightsDataList->head->next;
    while(current != NULL) {
        Flight *flight = current->flightInformation;

//        Counting types
        switch(flight->flightType){
            case 'E':
                countE++;
                break;
            case 'I':
                countI++;
                break;
            case 'D':
                countD++;
                break;
            default:
                return;
        }

//        flight->runwayNumber is 1-based, array is 0-based
        if(flight->runwayNumber > 0){
            runwayCounts[flight->runwayNumber -1]++;
        }

//        Calculating waiting time
        int waiting_time = flight->serviceStartTime - flight->readyTime;
        total_wait += waiting_time;
        if(waiting_time > max_wait)
            max_wait = waiting_time;

//        Counting airline and destination frequencies
        int foundAirline = 0;
        for (int i = 0; i < uniqueAirlineCount; ++i) {
            if(strcmp(airlineProperties[i].place, flight->airline) == 0){
                airlineProperties[i].count++;
                foundAirline = 1;
                break;
            }
        }
        if(!foundAirline){
            strcpy(airlineProperties[uniqueAirlineCount].place, flight->airline);
            airlineProperties[uniqueAirlineCount].count = 1;
            uniqueAirlineCount++;
        }


        int foundDestination = 0;
        for (int j = 0; j < uniqueDestinationCount; ++j) {
            if(strcmp(destinationProperties[j].place, flight->destination) == 0){
                destinationProperties[j].count++;
                foundDestination = 1;
                break;
            }
        }
        if(!foundDestination){
            strcpy(destinationProperties[uniqueDestinationCount].place, flight->destination);
            destinationProperties[uniqueDestinationCount].count = 1;
            uniqueDestinationCount++;
        }

//        Moving to next node in the list
        current = current->next;
    }

//    Calculating average waiting time
    double average_wait = 0.0;
    if(numberOfFlights > 0)
        average_wait = total_wait / numberOfFlights;

//    Finding the most popular airline and destination
    int popularAirlineIndex = 0;
    for (int i = 1; i < uniqueAirlineCount; ++i) {
        if(airlineProperties[i].count > airlineProperties[popularAirlineIndex].count)
            popularAirlineIndex = i;
    }

    int popularDestinationIndex = 0;
    for (int i = 1; i < uniqueDestinationCount; ++i) {
        if(destinationProperties[i].count > destinationProperties[popularDestinationIndex].count)
            popularDestinationIndex = i;
    }


    printf("****************** REPORT ******************\n");
    printf("The number of runways: %d\n", noOfRunways);
    printf("The number of flights: %d\n", numberOfFlights);
    printf("Number of flights for each flight type:\n");
    printf("\t\tEmergency: %d\n", countE);
    printf("\t\tInternational: %d\n", countI);
    printf("\t\tDomestic: %d\n", countD);
    printf("Number of flights for each runway:\n");

    for (int j = 0; j < noOfRunways; ++j) {
        printf("\t\tRunway %d: %d\n", j+1, runwayCounts[j]);
    }

    printf("Completion time: %d\n", clockTime);
    printf("Average time spent in the queue: %.1lf\n", average_wait);
    printf("Maximum waiting time: %d\n", max_wait);

    if(uniqueAirlineCount > 0)
        printf("Popular airline: %s\n", airlineProperties[popularAirlineIndex].place);

    if(uniqueDestinationCount > 0)
        printf("Popular destination: %s\n", destinationProperties[popularDestinationIndex].place);

//    Freeing memory
    free(runwayCounts);
    free(airlineProperties);
    free(destinationProperties);
}

void exitFromTheSimulation(List flightList, Queue flightQueue, int *flightData){
    deleteQueue(flightQueue);
    deleteList(flightList);
    if(flightData != NULL){
        free(flightData);
    }
}