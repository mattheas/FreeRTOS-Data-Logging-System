# Python code transmits a byte to Arduino /Microcontroller
import serial


def main():
    # Constants
    SENSOR_DATA_FILE = "SensorData.txt"

    while True:
        try:
            COM_number = int(input("Enter your COM port number (positive integer): "))
            if COM_number > 0:
                break  # Exit the loop if a positive integer is provided
            else:
                print("Invalid input. Please enter a positive integer")
        except ValueError:
            print("Invalid input. Please enter a positive integer")
    
    # open port 
    SerialObj = serial.Serial('COM' + str(COM_number)) # COMxx  format on Windows
                                      # ttyUSBx format on Linux

    SerialObj.baudrate = 9600  # set Baud rate to 9600
    SerialObj.bytesize = 8     # Number of data bits = 8
    SerialObj.parity  ='N'     # No parity bit 
        
    while True:    
        # retrieve data from Serial port
        ReceivedString = SerialObj.readline().decode('utf-8').rstrip()

        # print data to terminal
        print(ReceivedString)

        # Open file and write data to it 
        sensorDataFile = open(SENSOR_DATA_FILE, "a") 
        sensorDataFile.write(ReceivedString)
        sensorDataFile.write("\n")
        sensorDataFile.close()

    SerialObj.close()      # Close the port
 

if __name__ == '__main__':
    main()
