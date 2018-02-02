#include "WheelControl.h" //wheel pin constants defined here
#include "SensorControl.h" //sensor pin constants defined here
#include "DirectionControl.h"
#include "RobotStates.h"

// Black is low from sensor, but digitalRead as high
// White is high from sensor, but digitalRead as low

RobotState robotState = {
  BEGIN,   //previous state
  BEGIN    //current state
};

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

  if(leftLow() && rightLow()){
    moveForward();
  }

  else if(leftHigh() && rightLow()) {
    
    updateRobotState(robotState,RIGHT);
    
    while(leftHigh() && rightLow()){
      turnLeft();
    }
//    moveForward();
  }

  else if(leftLow() && rightHigh()) {
    while(leftLow() && rightHigh()) {
      turnRight();
    }
  }

  else {
    fullStop();
  }

}















//--------------------------------------------------------INITIAL CODE----------------------------------------------------------
void initialCode(){

   // put your main code here, to run repeatedly:
  
  // If both sensors see white, this assumes black line is between the two sensors
  if(digitalRead(left_sens) == LOW && digitalRead(right_sens) == LOW)
  {
    // Forward ------
    moveForward();
    
    // Manual PWM to adjust speed
    //delayMicroseconds(1200);
    //fullStop();
    //delayMicroseconds(2041 - 1200);
    // -----
  }
  // Sensors check, if either sensor detects the black line
  else if(digitalRead(left_sens) == HIGH || digitalRead(right_sens) == HIGH)
  {
    // If both sensors are HIGH, both detect black.
    // Happens at "T" and "+" junctions.
    //
    while(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == HIGH)
    {
      // check of end of maze or junction, could be a T or +
      if(checkEnd() == 1)
      {
        // Assume finished maze
        while(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == HIGH)
        {
          fullStop();   // loops until reset 
        }
      }
    }
    
    // If left sensor is HIGH, detects the black line, adjust left.
    // Turn left until input goes low.
    while(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == LOW)
    {
      if(digitalRead(right_sens) == HIGH && digitalRead(left_sens) == HIGH){
        fullStop();
        break;  // evaluate if end in first check for both sensors black, just break
      }
      // Pivot Left
      turnLeft();
    }

    // If right sensor is HIGH, detects the black line, adjust right.
    // Turn right until input goes low.    
    while(digitalRead(left_sens) == LOW && digitalRead(right_sens) == HIGH)
    {
      if(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == HIGH){
        fullStop();
        break;  // evaluate if end in first check for both sensors black, just break
      }
      // Pivot Right
      turnRight();
    }
    
  }
}
  
int checkEnd()
{
  moveForward();
  delayMicroseconds(50);
  
  // Check if both sensors still detect black. If true, assume at end of the maze since it is a solid black square
  if(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == HIGH)
  {
    fullStop();
    return 1;
  }
  // check if both white. Not the end so need to back track.
  else if(digitalRead(left_sens) == LOW && digitalRead(right_sens) == LOW)
  {
    // Reverse until at least one sensor detects black
    while(digitalRead(left_sens) == LOW && digitalRead(right_sens) == LOW)
    {
      //reverse 
    }
    // if back to both black
    if(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == HIGH)
    {
      // must pick a direction, chance of running off the course due to dead ends.
      // At T junction pivot. This logically doesn't work at "+" junction
      // example pivot left
      while(digitalRead(left_sens) == HIGH)
      {
        turnLeft();
      }
      // Then return 0 and continue normal operation
      return 0;
    }
    else // only one black so can continue normal operation
    {
      // Then return 0, not end
      return 0; 
    }
  }
  else
  {
    return 0;
  }
}

