#include "WheelControl.h" //pin constants defined here
#include "DirectionControl.h"

// Black is low rom sensor, but digitalRead as high
// White is high from sensor, but digitalRead as low

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
  if(digitalRead(left_sens) == LOW && digitalRead(right_sens) == LOW)
  {
    // Forward ------
    moveForward();
    delayMicroseconds(1200);
    fullStop();
    delayMicroseconds(2041 - 1200);
    // -----
  }
  // Sensors check
  else if(digitalRead(left_sens) == HIGH || digitalRead(right_sens) == HIGH)
  {
    // If both sensors are HIGH, both detect black.
    // Happens at "T" and "+" junctions.
    //
    while(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == HIGH)
    {
      // do something like stop
      fullStop();
    }
    // If left sensor is HIGH, detects the black line, adjust left.
    // Turn left until input goes low.
    while(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == LOW)
    {
      // Pivot Left
      turnLeft();
    }

    // If right sensor is HIGH, detects the black line, adjust right.
    // Turn right until input goes low.
      
    while(digitalRead(left_sens) == LOW && digitalRead(right_sens) == HIGH)
    {
      // Pivot Right
      turnRight();
    }
    
  }
}
