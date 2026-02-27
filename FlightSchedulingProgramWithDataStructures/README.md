# Flight Departure Simulator

## Description
A discrete-event simulation of an international airport's departure scheduling system.
It manages multiple runways and prioritizes flights using a combination of Linked Lists and Priority Queues.

## Features
* **Priority-Based Scheduling**: Flights are queued based on urgency: Emergency (Priority 3), International (Priority 2), and Domestic (Priority 1).
* **Multi-Server Simulation**: Handles $N$ runways (servers) simultaneously, tracking availability and "Busy" states.
* **Simulated Clock**: Tracks events across three stages: Flight Ready, Start Service, and Complete Service.
* **Statistical Insights**: Reports on average queue wait times, runway utilization, and the most popular airlines.

## Simulation Parameters
The program is initialized via command line with four variables:
1. `noofFlights`
2. `noOfRunways`
3. `maxReadyTime`
4. `maxServiceTime`

## Technical Constraints
* **Template Based**: Strictly follows the List and Queue ADT templates provided by METU NCC.
* **No Global Variables**: All simulation states are managed locally within the coordination logic.