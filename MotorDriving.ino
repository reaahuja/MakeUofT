/***********************************************************************************************
** Description: Project uses ultrasonic sensors to check whether there is a wall in front, and
**              if so, the robot will rotate until it no longer sees a wall anymore. The robot
**              will continue to drive forward.
**
** Author: Tyler Yan
** Date: February 19, 2023
***********************************************************************************************/

#include <NewPing.h>

// Defining where each component is connected
#define TRIG_IN A1
#define TRIG_OUT 3
#define ECHO_IN A2
#define ECHO_OUT 4

//Motor A
const int motorPin1 = 5;  // Pin 14 of L293
const int motorPin2 = 6;  // Pin 10 of L293
//Motor B
const int motorPin3 = 10; // Pin  7 of L293
const int motorPin4 = 9;  // Pin  2 of L293

// Defining constants used in code
#define DISTANCE 50 // Distance from wall

float entryDistance; // Float records distance that Ultrasonic sensors read at entry point
bool wall = false; // Boolean records whether there's a wall

NewPing sonar[1] = {NewPing(TRIG_IN, ECHO_IN, DISTANCE)};

void setup() 
{
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  
  // Set all components up
  pinMode(A0, OUTPUT); 
  pinMode(A5, OUTPUT);
  pinMode(A3, OUTPUT); 
  //Set pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  // Activate all components
  digitalWrite(A0, HIGH); 
  digitalWrite(A3, LOW); 
  digitalWrite(motorPin4, LOW);
  
  // Print out distance that sensors are tracking at and amount of people at start
  Serial.print("Wall distance is: ");
  Serial.println(DISTANCE);
  
  delay(1000);
}

void loop() 
{ 
  // Records the distance at the entry point
  entryDistance = sonar[0].ping_cm();
  
  // Checks if the distance is less than the wall and is greater than zero at entry point
  if (entryDistance < DISTANCE && entryDistance > 0) 
  { 
    // If at a wall
    Serial.println("Wall");
    
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin1, HIGH);
  } 
  else 
  {
    // If not at a wall
    Serial.println("No wall");
    
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
  }
}
