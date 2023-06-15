# Python code transmits a byte to Arduino /Microcontroller
import serial


def main():
    SENSOR_DATA_FILE = "SensorData.txt"
    #get input from user about what port the arduino is connected, make sure that the you ensure the input from the user is an +ive int
    # code HERE
    
    # open port 
    SerialObj = serial.Serial('COM6') # COMxx  format on Windows
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
