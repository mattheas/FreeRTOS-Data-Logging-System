# FreeRTOS-Data-Logging-System

## Description
The FreeRTOS-Data-Logging-System  is a real-time data acquisition and logging system designed to collect and record data from a liquid level sensor. The system is composed of a Arduino Mega 2560 running FreeRTOS to perform data polling and transmission. The acquired data is then transmitted via a Serial connection to a PC, where it is logged to a file using a Python3 script.

## Features Explored
This project serves as an exploration and refamiliarization journey into the capabilities of FreeRTOS. By utilizing FreeRTOS, various features were investigated, including task synchronization, inter-task communication, data polling frequency, and multitasking schemes. Additionally, the project delved into the realm of serial communication between an Arduino and PC, using Python to facilitate seamless data transmission.

## Installation

It is assumed that your PC is using a Windows OS and the following are already installed:
- Python 3
- Arduino IDE
- 
To install the necessary dependencies, kindly follow these steps:

1. Install the pySerial package for Python by executing the following command in the Windows PowerShell:
python -m pip install pyserial

2. Install the FreeRTOS port for the Arduino microcontroller. Open the Arduino IDE Library Manager and install the most recent version of "FreeRTOS by Richard Barry."

## Usage

Wire the water level sensor to your Arduino Mega as seen below. The sensor should connect to the board as follows:

Sensor      Arduino
  -           GND
  +           5V (or 3.3V)
  S           A0

The Arduino microntroller should then be connected to your PC via a USB cable. Then the Arduino IDE can be used to compile and upload the data_logger.ino script to the Arduino. Once that is done ensure the Serial Monitor in the IDE is CLOSED, or else the python script will not work.

Then open Windows PowerShell and navigate to the directory containing the data_recorder.py file, and use the following command "python data_recorder.py" to start running the script. Type the number of the port that the Arduino is connected to and press enter (e.g., the Arduino IDE says my Arduino is connected to COM6 so type '6' and press Enter). Then in a few moments the PowerShell should start updating with a new value every 5 seconds (this is how often the sensor is polled), all the values seen in the terminal will also be logged to a .txt file.

  
