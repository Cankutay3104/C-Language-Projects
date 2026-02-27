cmake_minimum_required(VERSION 3.20)
project(Assignments C)

set(CMAKE_C_STANDARD 99)

add_executable(generala GeneralaGame/Generala_Game.c)
add_executable(networkReg NetworkRegistrationProgram/NetworkRegistrationProgram.c)
add_executable(flightProgramCopy
        FlightSchedulingProgramWithDataStructures/queue.c
        FlightSchedulingProgramWithDataStructures/list.c
        FlightSchedulingProgramWithDataStructures/flight.c
        FlightSchedulingProgramWithDataStructures/flightScheduling.c)
add_executable(flightsAppCopy
        AirportDataAnalysisProgramWithDataStructures/avltree.c
        AirportDataAnalysisProgramWithDataStructures/flightsApp.c)