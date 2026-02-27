# Network Registration System

## Description
A management utility designed for IT officers to process university network device registrations. 
The system handles student data, device MAC addresses, and registration statuses using file-based persistence.

## Features
* **Data Structure**: Utilizes a custom `Registration` struct to manage IDs, names, statuses, and Mac addresses.
* **File I/O**: Loads and saves data to `RegistrationData.txt`.
* **Sorting Engine**: Implements the Bubble Sort algorithm to organize records by year or student surname.
* **Validation**: Enforces strict formatting for MAC addresses (XX:XX:XX:XX:XX:XX) and registration statuses.
* **Statistics**: Generates real-time reports on the number of Approved, Blocked, and Declined devices.

## Programming Requirements
* **Dynamic Allocation**: Dynamically populates data arrays without assuming a fixed record size.
* **Modular Interface**: Controlled via a centralized menu system.
* **Command Line Support**: Accepts filename arguments directly from the terminal.

## How to Run
```bash
gcc main.c -o NetworkRegistration
./NetworkRegistration RegistrationData.txt
```