# FreeRTOS-Data-Logging-System

## Description
The FreeRTOS-Data-Logging-System  is a real-time data acquisition and logging system designed to collect and record data from a liquid level sensor. The system is composed of a Arduino Mega 2560 running FreeRTOS to perform data polling and transmission. The acquired data is then transmitted via a Serial connection to a PC, where it is logged to a file using a Python3 script.

## Features Explored
This project serves as an exploration and refamiliarization journey into the capabilities of FreeRTOS. By utilizing FreeRTOS, various features were investigated, including inter-task communication, data polling frequency, and multitasking schemes. Additionally, the project delved into the realm of serial communication between an Arduino and PC, using Python to facilitate seamless data transmission. Details below:

### 1) inter-task communication
- There are various ways to communicate between tasks. I chose to use two methods, that is a Queue (FIFO) and Stack (LIFO). The Queue implementation uses the built in Queue type in its default configuration (i.e., xQueueSendToBack() and xQueueReceive()), the implementation can be seen in the "data_logger_Queue_Implementation.ino" file. The Stack however is not a built in type so it requires using the same Queue type in a different manner, that is posting to the front (w/ xQueueSendToFront()) and also receiving data from the front (w/ xQueueReceive()). In this project it is logical to use a Queue as it keeps the data in the correct order, however exploring alternative communication methods was an objective of this project so therefore I also chose to implement a Stack.

### 2) Data Polling Frequency
- The way I achieved data polling of the liquid level sensor at specific frequencies was straightforward. I had TaskReadSensorData Task block itself using the vTaskDelay() function for period of time that I wanted between sensor reads (i.e., 5 seconds), once that time had elapsed the Task would return to the Ready state where it would be executed shortly after, this process would repeat indefinitely.

### 3) Multitasking Schemes
- I explored a few multitasking schemes. The first being round robin time slicing, to implement this I simply made both tasks have the same priority level of 2, the FreeRTOS scheduler should therefore give each task equal CPU time. Round robin time slicing is a simple and fair way of splitting CPU time among tasks, the drawback of this approach is that it does not predictable response times and is therefore not suitable for hard real time software tasks.
- The next approach I employed was pre-emptive multitasking. I did this by creating the TaskReadSensorData with a priority that was one higher than the TaskTransmitSensorData. This means that whenever the TaskReadSensorData entered the Ready state, the scheduler would immediately perform a context switch to that task as it had the highest priority. This architecutre is more suitable to hard real time software tasks, a drawback of this architecture is possible priority inversion, where a higher priority task is waiting for a lower priority task to release a resource so it can execute.

## Installation

It is assumed that your PC is using a Windows OS and the following are already installed:
- Python 3
- Arduino IDE

To install the necessary dependencies, kindly follow these steps:

1. Install the pySerial package for Python by executing the following command in the Windows PowerShell:

python -m pip install pyserial

2. Install the FreeRTOS port for the Arduino microcontroller. Open the Arduino IDE Library Manager and install the most recent version of "FreeRTOS by Richard Barry."

## Usage

Wire the water level sensor to your Arduino Mega as seen below. The sensor should connect to the board as follows:

Sensor       Arduino
 (-)    <->    GND
 (+)    <->     5V (or 3.3V)
 (S)    <->     A0

The Arduino microntroller should then be connected to your PC via a USB cable. Then the Arduino IDE can be used to compile and upload the data_logger.ino script to the Arduino. Once that is done ensure the Serial Monitor in the IDE is CLOSED, or else the python script will not work.

Then open Windows PowerShell and navigate to the directory containing the data_recorder.py file, and use the following command "python data_recorder.py" to start running the script. Type the number of the port that the Arduino is connected to and press enter (e.g., the Arduino IDE says my Arduino is connected to COM6 so type '6' and press Enter). Then in a few moments the PowerShell should start updating with a new value every 5 seconds (this is how often the sensor is polled), all the values seen in the terminal will also be logged to a .txt file.

  
