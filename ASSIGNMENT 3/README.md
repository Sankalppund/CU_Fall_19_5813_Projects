# PES_PROJECT_3_FINAL

#TEAM MEMBERS : 1) SANKALP PUND (sapu9724@colorado.edu) 2) SAKET PENURKAR (sape5303@colorado.edu)

#This repository contains the files as mentioned below: 

#1) PES_5318_Project_3 o Project Settings o Build Targets o Binaries o Includes o CMSIS o Board o Drivers o Source o Startup o Utilities o   Debug o Doc o ucunit-master & PES_5318_Project_3 PE Debug.launch o PES_5318_Project_3.mex

#2) Problem: 1. While implementing fb version code on linux it was showing error that uint32_t data type could not be resolved. Same was addressed using “stdint.h” header file in linux version program.

#3) Problem:2. While implementing KL25Z version code on linux, the conditional functions such as write_pattern, invert_block were not working since we had used initial address pointer and last address for bound checking in KL25Z version which is 32bit system whereas same thing did not work on host machine since it is a 64 bit machine. Problem resolved using both initial pointer and last pointer for bound checking instead of just address. Conditional error got resolved.


#4) Installation/execution notes: A) FRDM-KL25Z MCU: Connect FRDM-KL25Z to host machine through USB. Go to Windows tab and select show view and then Others and select terminal. Now choose terminal as serial terminal, serial port, baud rate 115200, data size 8, parity none, stop bit 1 and encoding default which will set the terminal for output through UART. Select the project and build in debug mode. Flash the code into the target KL25Z and check the terminal to see the status outputs.


#5) Memory test suit’s function’s arguments, seed value , running unit test case can be changed through main.h file through #define functionality.

#6) Installation/execution notes: A) LINUX: open terminal in folder containing the source files. Write command “cd/folder_name” where folder name is of source folder having .c & .o files. Now use “$ gcc main.c ss_memory_suit.c SS_PatternGeneration.c logger.c -o output”. output named object file will be generated in source folder. Now use command “./output” to get the result on terminal.

#7) Log_enable() is already called in main.c file by default which enables logging on terminal. To disable the functionality, kindly comment the Log_enable() function. After this logging output will not be printed on terminal.

#8) For running unit test case define ENABLE_TESTING to 1 in main.h file & for running Memory suit test mode define MEMORY_SUITE_MODE to 1 in main.h

