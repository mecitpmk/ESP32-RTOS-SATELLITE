#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

#include "MAVLINKPROTOCOL.h"

// define two tasks for Blink & AnalogRead
void TaskCommunucation( void *pvParameters );
void TaskSensors( void *pvParameters );
void TaskDescentControl( void *pvParameters );

Communucation cProtocol ;

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  cProtocol.stringCopies();  
  // Now set up two tasks to run independently.
  xTaskCreatePinnedToCore(
    TaskCommunucation
    ,  "TaskComm"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  0);

  xTaskCreatePinnedToCore(
    TaskSensors
    ,  "TaskSensor"
    ,  1024  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL 
    ,  1);

   xTaskCreatePinnedToCore(
    TaskDescentControl
    ,  "TaskDescent"
    ,  1024  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL 
    ,  1);

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskDescentControl(void *pvParameters)  // This is a task.
{
  (void) pvParameters;


//   pinMode(LED_BUILTIN, OUTPUT); // To Remember We can Adjust PinModes.


    // INIT BMP IN HERE.
  for (;;) // A Task shall never return or exit.
  {
    cProtocol.readBMP(); // Get Altitude Temp, Pressure
    cProtocol.setNewStatus(); //To get status and Velocity.
    if (cProtocol.controlVar.FLAGS.seperatedBefore) // if Motor Activated
    {
        if (cProtocol.controlVar.FLAGS.fixAltitude)
        {
            // if Altitude fixed in (200m)
            return;
        }
        else // if seperated but altitude is not = 200m.
        {
            // if normally falling with Activated Motor Speed (8-10 m/s)
            
            return;
        }
    }
    else
    {
      // Nothing to do.(MOTOR DOESNT HAVE TO RUN.)
    }
  }
}


void TaskSensors(void *pvParameters)  // This is a task.
{
  (void) pvParameters;


  // Init Sensors in here.

  for (;;) // A Task shall never return or exit.
  {
     cProtocol.readIMU();
     cProtocol.readGPS();

  }
}

void TaskCommunucation(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  
  for (;;) // A Task shall never return or exit.
  {
    cProtocol.readSerialDatas(); // Reads serial data all the time.
  }
}