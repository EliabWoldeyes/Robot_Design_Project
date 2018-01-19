#include "WheelControl.h" //pin constants defined here
#include "DirectionControl.h"



  boolean tmp = false;

  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Setup pins -----
  // Motors
  pinMode(right_BB, OUTPUT);
  pinMode(right_BA, OUTPUT);
  pinMode(left_AB, OUTPUT);
  pinMode(left_AA, OUTPUT);

  // Sensors
  pinMode(right_sens, INPUT);
  pinMode(left_sens, INPUT);
  
  // -----
}

void loop() {

 // put your main code here, to run repeatedly:
  if(left_sens == LOW && right_sens == LOW)
  {
    // Forward ------
    moveForward();
    // -----
  }
  // Sensors check
  else if(left_sens == HIGH || right_sens == HIGH)
  {
    // If both sensors are HIGH, both detect black.
    // Happens at "T" and "+" junctions.
    //
    while(left_sens == HIGH && right_sens == HIGH)
    {
      // do something like stop
      fullStop();
    }

    // If left sensor is HIGH, detects the black line, adjust left.
    // Turn left until input goes low.
    while(left_sens == HIGH && right_sens == LOW)
    {
      // Pivot Left
      turnLeft();
    }

    // If right sensor is HIGH, detects the black line, adjust right.
    // Turn right until input goes low.
    while(left_sens == LOW && right_sens == HIGH)
    {
      // Pivot Right
      turnRight();
    }
  }
}
