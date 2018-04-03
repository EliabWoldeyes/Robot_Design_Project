//Author: Jonathan Chan

#include "WheelControl.h" //wheel pin constants defined here
#include "SensorControl.h" //sensor pin constants defined here
#include "DirectionControl.h"
#include "RobotStates.h"

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
  pinMode(left_sens, INPUT);
  pinMode(middle_sens, INPUT);
  pinMode(right_sens, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  run();
}

/*
 * 
 */

// Assuming sensor configuration is:
// Left and right are over the wheels
// Head is at the front of the robot
void run(){

// LOW means wall
// HIGH means no wall

// middle sensor distance adjusted to be about half of left sensor
// may just ignore right sensor.

  while(1){

    /* Don't we need to handle the case where neither left or right are low? */

   // high means it does not detect the wall, so move in an arch left until it finds it
   while(digitalRead(left_sens) == HIGH || digitalRead(middle_sens) == HIGH){

     archLeft();
     
     // If both detect a wall, then assume it is a corner.
     if(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == LOW){

       while(digitalRead(middle_sens) == LOW){

        turnRight();
       }

       // checking left hand side and ensure the head of the robot is pointing greater than parallel to the left wall
       if(digitalRead(left_sens) == HIGH){

        while(digitalRead(left_sens) == HIGH){

          turnRight();
        }
       }


       if(digitalRead(left_sens) == LOW){
        while(digitalRead(left_sens) == LOW){
          turnRight();
        }
       }
       
     }

    
     if(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == HIGH){

      //detects wall on left, so turn away to setup for next archLeft
      while(digitalRead(left_sens) == LOW){

        turnRight();
      }
      
     }

     if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == LOW){

      // for now move in a circle until it detects a wall on its left sensor. If none, feedback to the operator.
      while(digitalRead(left_sens) == HIGH){

        archRight();
        
      }
     }
    
   }
    
  }
  
}

