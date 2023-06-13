#include <Arduino_FreeRTOS.h>

#define sensorPowerPin 52
#define sensorOutputPin A0

void TaskReadSensorData( void *pvParameters );
void TaskTransmitSensorData( void *pvParameters );


void setup() 
{ 
  pinMode(sensorOutputPin, INPUT);
  pinMode(sensorPowerPin, OUTPUT);

  digitalWrite(sensorPowerPin, HIGH);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Create two tasks
  xTaskCreate(    TaskReadSensorData                /* The function that implements the task. */
                  , "ReadSensorData"                /* Text name for the task, provided to assist debugging only. */
                  , configMINIMAL_STACK_SIZE        /* The stack allocated to the task. */
                  , NULL                            /* The task parameter is not used, so set to NULL. */
                  , 2                               /* The priority at which the task is created */
                  , NULL );                         /* Used to pass out the created task's handle. It is not used so set to NULL */
  
  xTaskCreate(    TaskTransmitSensorData                /* The function that implements the task. */
                  , "TransmitSensorData"                /* Text name for the task, provided to assist debugging only. */
                  , configMINIMAL_STACK_SIZE        /* The stack allocated to the task. */
                  , NULL                            /* The task parameter is not used, so set to NULL. */
                  , 1                               /* The priority at which the task is created */
                  , NULL );                         /* Used to pass out the created task's handle. It is not used so set to NULL */
  
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

  for(;;)
  {
    int sensorValue = analogRead(sensorOutputPin);
    Serial.println(sensorValue);
    vTaskDelay(1);

  }

}
 

void TaskTransmitSensorData(void *pvParameters) // This is a task.
{
  (void) pvParameters;

  for(;;){
    Serial.println("Transmit sensor data task");
    vTaskDelay(1);

  }

}

