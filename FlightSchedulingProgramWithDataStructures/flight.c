
#include "flight.h"
#include <string.h>


//This function will create a dynamically allocated flight with random values and return its address.
Flight * createRandomFlight(int maxReadyTime, int maxServiceTime){

    const char *airlines[] = {
            "AQ", "DM", "BJ", "RL", "GB", "ZA", "VX", "JP", "ML", "VF", "DW", "SU", "SM",
            "KJ", "YE", "VJ", "QH", "HD", "UJ", "EI", "EG", "RV", "ZI", "KI", "QB", "LD",
            "UX", "NX", "HM", "CY", "AA", "AZ", "EK", "ED", "ZW", "YI", "GN", "ZB"};

    const char *destinations[] = {
            "JYH", "DWI", "ABJ", "ABG", "ABX", "CYD", "AES", "ADR", "AEK", "TKJ", "UCR", "AFL",
            "AAW", "AAZ", "ACQ", "AFF", "FLA", "ADO", "LMU", "EIN", "EUK", "ROU", "AAF", "AAG", "AAJ", "AHK",
            "AEA", "AMU", "SEY", "LCA", "MAP", "CAI", "MCM", "AXE", "AWI", "RSI", "AGN", "ABN"
    };

    Flight *flight = malloc(sizeof(Flight));
    if(flight == NULL){
     printf("Memory allocation failed.\n");
     exit(1);
    }

    int r = rand() % 3;
    switch (r) {
     case 0:
         flight->flightType = 'E';
         break;
     case 1:
         flight->flightType = 'I';
         break;
     case 2:
         flight->flightType = 'D';
         break;
    }

    flight->readyTime = rand() % (maxReadyTime + 1);
    flight->serviceTime = rand() % maxServiceTime + 1;
    flight->serviceStartTime = 0;
    flight->runwayNumber = 0;

    int i = rand() % (sizeof(airlines)/sizeof(airlines[0]));
    strcpy(flight->airline, airlines[i]);

    int j = rand() % (sizeof(destinations)/sizeof(destinations[0]));
    strcpy(flight->destination, destinations[j]);

    return flight;
}

//This function gets a flights address and prints its values.
void printFlightInformation(Flight* flight){
    if(flight != NULL){
        printf("%c %2d %2d %2d %2d %3s %4s\n", flight->flightType, flight->readyTime, flight->serviceTime, flight->serviceStartTime, flight->runwayNumber, flight->airline, flight->destination);
    }
}
