

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 30

struct Registration{
    int id;
    char name[STR_LEN];
    char surname[STR_LEN];
    char status[STR_LEN];
    int year;
    char deviceMACAddress[STR_LEN];
};

typedef struct Registration Register;

Register *load_registrationData(char *fileName, int *recordSize);
void display_registrationData(Register *registrationData, int recordSize);
Register *add_registration(Register *registrationData, int *recordSize);
void sort(Register *registrationData, int recordSize);
void statistics(Register *registrationData, int recordSize);
void menu(void);

#define MAX_LENGTH 100

int main(int argc, char *argv[]){

    char file_name[MAX_LENGTH];

    FILE *file = NULL;

    // checking to see whether there is a file or not
    if (argc < 2) {
        printf("You must provide a file name as a command-line argument.\n");
        printf("Example: %s RegistrationData.txt\n", argv[0]);
        return 1;
    }

    printf(">%s %s\n", argv[0], argv[1]);

    //  Assigned the first argument after the program's name to my file_name
    strcpy(file_name, argv[1]);

    int correct_file = 1;

    //  Loop for finding the correct file
    while(correct_file){
        if(strcmp(file_name, "RegistrationData.txt") != 0){
            printf("This file does not exist. Please enter again: ");
            fgets(file_name, MAX_LENGTH, stdin);
            file_name[strcspn(file_name, "\n")] = '\0';
        }
        else{
            //  Opening the file
            file = fopen(file_name, "r");
            if(file == NULL){
                printf("Opening file process failed.\n");
                exit(1);
            }

            correct_file = 0; // Exit the loop
            printf("The registration records file (%s) has been successfully loaded!\n", file_name);
            fclose(file);
        }
    }

    int recordSize;

    Register *registrationData = load_registrationData(file_name, &recordSize);
    printf("The following have been loaded:\n");

    display_registrationData(registrationData, recordSize);

    int option = 5;
    int controller = 0; // to control the loop
    while(!controller){

        menu();
        printf("Enter your choice:");
        scanf("%d", &option);
        getchar(); // getting rid of newline character

        if(option == 1){
            registrationData = add_registration(registrationData, &recordSize);
        }
        else if(option == 2){
            sort(registrationData, recordSize);
        }
        else if(option == 3){
            statistics(registrationData, recordSize);
        }
        else if(option == 4){
            printf("Bye\n");
            controller = 1;
        }
        else{
            printf("Wrong input!\n");
        }
    }

    free(registrationData);

    return 0;
}

// -------------------------------------------------------------------------------

Register *load_registrationData(char *file_name, int *recordSize){

    FILE *infile = fopen(file_name, "r");
    if(infile == NULL){
        printf("File cannot be opened.\n");
        *recordSize = 0;
        exit(1);
    }

    char line[100];
    int line_count = 0;
    int total_count = 5;

    Register *registrationData = (Register *)malloc(sizeof(Register) * total_count);
    if(registrationData == NULL){
        printf("Memory allocation failed.\n");
        *recordSize = 0;
        fclose(infile);
        exit(1);
    }

    //  To skip the first line of information which contains headers
    fgets(line, sizeof(line), infile);

    //  exit the loop when fgets hit '\0'
    while(fgets(line, sizeof(line), infile) != NULL){

        //  extending the coverage if it is needed
        if(line_count == total_count){
            total_count += 5;
            registrationData = (Register *)realloc(registrationData, sizeof(Register) * total_count);
            if(registrationData == NULL){
                printf("Memory reallocation failed.\n");
                free(registrationData);
                *recordSize = 0;
                fclose(infile);
                exit(1);
            }
        }

        char *token;
        //  splitting the information to share it between the variables
        token = strtok(line, " ");
        registrationData[line_count].id = atoi(token); // atoi has been introduced in class to convert a string into an integer

        token = strtok(NULL, " ");
        strcpy(registrationData[line_count].name, token);

        token = strtok(NULL, " ");
        strcpy(registrationData[line_count].surname, token);

        token = strtok(NULL, " ");
        strcpy(registrationData[line_count].status, token);

        token = strtok(NULL, " ");
        registrationData[line_count].year = atoi(token);

        token = strtok(NULL, "\n");
        strcpy(registrationData[line_count].deviceMACAddress, token);

        line_count++;
    }

    fclose(infile);

    *recordSize = line_count;

    return registrationData;
}

// -------------------------------------------------------------------------------

void display_registrationData(Register *registrationData, int recordSize){

    printf("%-10s %-12s %-15s %-15s %-10s %-20s\n","REGID", "NAME", "SURNAME", "STATUS", "YEAR", "DEVICEMACADDRESS");
    for (int i = 0; i < recordSize; i++) {
        printf("%-10d %-12s %-15s %-15s %-10d %-20s\n",registrationData[i].id,registrationData[i].name,registrationData[i].surname,registrationData[i].status,registrationData[i].year,registrationData[i].deviceMACAddress);
    }
}

// -------------------------------------------------------------------------------

Register *add_registration(Register *registrationData, int *recordSize){

    // adding one more record
    registrationData = realloc(registrationData, (*recordSize + 1) * sizeof(Register));
    if (registrationData == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    registrationData[*recordSize].id = registrationData[*recordSize - 1].id + 1;

    printf("Please enter the name: ");
    fgets(registrationData[*recordSize].name, STR_LEN, stdin);
    registrationData[*recordSize].name[strcspn(registrationData[*recordSize].name, "\n")] = '\0';

    printf("Please enter the surname: ");
    fgets(registrationData[*recordSize].surname, STR_LEN, stdin);
    registrationData[*recordSize].surname[strcspn(registrationData[*recordSize].surname, "\n")] = '\0';

    // these variables are needed for the error check
    int valid = 0;
    char temp[STR_LEN];
    while(!valid){
        printf("Please enter the status: ");
        fgets(temp, STR_LEN, stdin);
        temp[strcspn(temp, "\n")] = '\0';

        //  Status validation check as asked
        if (strcmp(temp, "Approved") == 0 || strcmp(temp, "Blocked") == 0 || strcmp(temp, "Declined") == 0) {
            strcpy(registrationData[*recordSize].status, temp);
            valid = 1;
        }
        else {
            printf("This is not valid!\n");
        }
    }

    printf("Please enter the year: ");
    fgets(temp, STR_LEN, stdin);
    registrationData[*recordSize].year = atoi(temp);

    // again for the error check
    valid = 0;
    while(!valid){
        printf("Please enter the mac address: ");
        fgets(temp, STR_LEN, stdin);
        temp[strcspn(temp, "\n")] = '\0';

        //  for the format check about ":"
        if(strlen(temp) == 17 && temp[2] == ':' && temp[5] == ':' && temp[8] == ':' && temp[11] == ':' && temp[14] == ':'){
            strcpy(registrationData[*recordSize].deviceMACAddress, temp);
            valid = 1;
        }
        else
            printf("This is not valid.\n");
    }

    // incrementing record size for the newly added record
    (*recordSize)++;

    printf("It is recorded successfully!\n");

    return registrationData;

}

// -------------------------------------------------------------------------------

void sort(Register *registrationData, int recordSize){
    int choice;
    printf("Which column (1: year, 2: surname)?: ");
    scanf("%d", &choice);
    getchar(); //   erasing the newline character after scanf

    while(choice != 1 && choice != 2){
        printf("Invalid choice!\n");
        printf("Which column (1: year, 2: surname)?: ");
        scanf("%d", &choice);
        getchar();
    }

    //  now the bubble sort as required
    for (int i = 0; i < recordSize - 1; i++) {
        for (int j = 0; j < recordSize - i - 1; j++) {
            if (choice == 1) {  // sorting by year
                if (registrationData[j].year > registrationData[j + 1].year) {
                    Register temp = registrationData[j];
                    registrationData[j] = registrationData[j + 1];
                    registrationData[j + 1] = temp;
                }
            }
            else if (choice == 2) {  // sorting by surname
                if (strcmp(registrationData[j].surname, registrationData[j + 1].surname) > 0) {
                    Register temp = registrationData[j];
                    registrationData[j] = registrationData[j + 1];
                    registrationData[j + 1] = temp;
                }
            }
        }
    }

    display_registrationData(registrationData, recordSize);
}

// -------------------------------------------------------------------------------

void statistics(Register *registrationData, int recordSize){
    int blocked = 0, approved = 0, declined = 0;

    for (int i = 0; i < recordSize; ++i) {
        if(strcmp(registrationData[i].status, "Blocked") == 0)
            blocked++;
        else if(strcmp(registrationData[i].status, "Approved") == 0)
            approved++;
        else if(strcmp(registrationData[i].status, "Declined") == 0)
            declined++;
    }

    printf("Summary:\n");
    printf("%d Blocked\n", blocked);
    printf("%d Approved\n", approved);
    printf("%d Declined\n", declined);
}

// -------------------------------------------------------------------------------

void menu(void){
    printf("\nWhat would you like to do?\n");
    printf("1 - add\n");
    printf("2 - sort\n");
    printf("3 - statistics\n");
    printf("4 - exit\n");
}