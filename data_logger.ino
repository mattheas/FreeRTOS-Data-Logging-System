#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define sensorPowerPin 52
#define sensorOutputPin A0

void TaskReadSensorData( void *pvParameters );
void TaskTransmitSensorData( void *pvParameters );

QueueHandle_t xQueue_FIFO = NULL;	//queue between two tasks 

void setup() 
{ 
  pinMode(sensorOutputPin, INPUT);
  pinMode(sensorPowerPin, OUTPUT);

  digitalWrite(sensorPowerPin, HIGH);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Create two tasks, one for reading sensor data, and one for transmitting it back to PC
  BaseType_t Task1 = xTaskCreate(    TaskReadSensorData                 /* The function that implements the task. */
                                      , "ReadSensorData"                /* Text name for the task, provided to assist debugging only. */
                                      , configMINIMAL_STACK_SIZE        /* The stack allocated to the task. */
                                      , NULL                            /* The task parameter is not used, so set to NULL. */
                                      , 2                               /* The priority at which the task is created */
                                      , NULL );                         /* Used to pass out the created task's handle. It is not used so set to NULL */
  
  BaseType_t Task2 = xTaskCreate(    TaskTransmitSensorData            /* The function that implements the task. */
                                      , "TransmitSensorData"            /* Text name for the task, provided to assist debugging only. */
                                      , configMINIMAL_STACK_SIZE        /* The stack allocated to the task. */
                                      , NULL                            /* The task parameter is not used, so set to NULL. */
                                      , 1                               /* The priority at which the task is created */
                                      , NULL );                         /* Used to pass out the created task's handle. It is not used so set to NULL */
  
  // Create Queue for inter-process communication
  xQueue_FIFO = xQueueCreate( 10, sizeof( int ) ); //connects task1 -> task2

  // Check that Tasks and Queue were initialized properly
  if (xQueue_FIFO == NULL) { Serial.println("QUEUE WAS NOT INITIALIZED"); }
  if (Task1 != pdPASS || Task2 != pdPASS) { Serial.println("TASK(S) WERE NOT INITIALIZED"); }


  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.

  Serial.println("Setup() complete");

}


void loop() 
{
  // Idle Task

}


/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskReadSensorData(void *pvParameters) // This is a task.
{
  (void) pvParameters;

  for (;;)
  {
    int sensorValue = analogRead(sensorOutputPin);
    //Serial.println(sensorValue);
    xQueueSendToBack(xQueue_FIFO, &sensorValue, 0UL);
    vTaskDelay(1);

  }

}
 

void TaskTransmitSensorData(void *pvParameters) // This is a task.
{
  (void) pvParameters;

  int recievedData;

  for (;;)
  {
    xQueueReceive(xQueue_FIFO, &recievedData, portMAX_DELAY); // Waits indefinetely for the queue to have data
    Serial.println(recievedData);
    vTaskDelay(1);

  }

}

