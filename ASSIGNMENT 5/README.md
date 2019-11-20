
###### **PROJECT 5 README**


## TEAM MEMBERS :   

1) SANKALP PUND (sapu9724@colorado.edu) 
2) SAKET PENURKAR (sape5303@colorado.edu) 

This repository contains the files as mentioned below: 

## Repo Content.:
.settings,
board,
CMSIS, CMSIS Driver,
debug, drivers,
source,
startup,
ucunit-master,
Utilities,
.cproject,
.project, PES_5813_Project_5_Final PE Debug.launch,
PES_5813_Project_5_Final.mex,
PROJECT_5_FMEA_REPORT.pdf,
Trace of UART traffic between KL25Z and the PC using LOGIC ANALYSER.pdf,
README.md

## Observations:

•	Problem 1:While using an instance of a circular buffer in other files using extern, it was throwing a hard fault error while flashing code into the board. The reason was, whenever we used extern to used circular buffer instance in another file it would create new instance and it would not get the memory access leading to hard fault. The same we tried solving by creating an instance in one header file and including header file wherever instance was required. It lead to another problem of multiple declaration which was solved by adding a linker flag which activated the header guards and error was resolved.

•	Problem 2: While adding any number to circular buffer it used to throw randomly a hard fault error stating memory cannot be accessed. While debugging it was observed that head was getting some random values which were out of memory scope. Issue was resolved by initializing head to 0.

•	Problem 3: During ECO mode using an interrupt, an ISR was continuously getting triggered and thus no data was received in interrupt to be echoed. During debugging it was observed that PC counter used to get stuck at receive interrupt flag every time. The issue was that, we did not handle clearing of receive interrupt flag (UART0->S1 & UART0_S1_RDRF_MASK). The same was resolved by receiving the data from UART in ISR itself which automatically clears the receive interrupt flag.

•	Problem 4: While using timestamp function, it would not print any timestamps on console. We assumed the problem must be with systick timer but during debugging mode it was observed that systick time was getting the required values. The issue was with the data type of variable in which we stored the current counter values. Mistakenly uint64_t was used. Since the microcontroller is 32bit it was not storing data in those variables. We replaced all such variable data types from uint64_t to uint32_t and got the timestamps on PC terminal.

•	Problem 5: While comparing the special character stored in circular buffer for generating report in application mode, it was storing the special character continuously in buffer even after making the buffer pointer free. The issue was that since heap retains the data, the compering condition used to get satisfied every time even though some different character was sent from terminal. The issue was resolved using destroy buffer function as soon as special character was received so that next time, we compare the value it does not get the previously stored value.

•	Problem 6: While writing the test cases it was throwing more than 100 errors of no declaration found. The same was resolved by taking System.c file in source folder.


## Installation/Execution Notes:

•	FRDM-KL25Z MCU: Connect FRDM-KL25Z to host machine through USB. For testing purpose,
Nex Robotics serial terminal was installed (http://www.nex-robotics.com/resources/serial-terminal-2.html). All ECO Mode, Application Mode were tested on the same at baud rate of 9600 and Test Mode was tested at baud rate of 115200.

•	Test Mode, ECO Mode, Application Mode & Interrupt mode can be selected using #define macros. For enabling any mode enter ‘1’ and disabling any mode enter ‘0’ in main.h file.

•	While transmitting and receiving the data through UART, polling mode runs by default. To run the operations in Interrupt mode use #define USE_UART_INTERRUPTS (0) in main.h file.

•	If you want to run the code in the test mode, for running the test scripts, #define TEST_MODE (1) in the main.h otherwise change it to (0)

•	If you want to enable logging, write the #define value (1) to LOG_ENABLE macro in main.h

•	For logging functionalities, please follow the respective enums in the logger.h file. For Log level setting, use the enums in Logging_level_m. For functions’ enum, use the eunum stated in the Function_Name_m.

•	For generating report in application mode, send characters one by one through serial terminal and if you want to generate the report, send special character ‘ = ‘ from serial terminal.

•	For initializing the circular buffer of given length and inserting given number of elements, use #define BUFFER_SIZE and #define NO_OF_ELEMENTS in main.h

•	For setting the baud rate for UART Initialization, use #define BAUD_RATE in main.h




