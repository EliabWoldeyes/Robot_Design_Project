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

void run(){

// LOW means wall
// HIGH means no wall

// middle sensor distance adjusted to be about half of left sensor
// may just ignore right sensor.

  while(1){

   // high means it does not detect the wall, so move in an arch left until it finds it
   while(digitalRead(left_sens) == HIGH || digitalRead(middle_sens) == HIGH){

     archLeft();
     
     // If both detect a wall, then assume it is a corner.
     if(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == LOW){

       while(digitalRead(middle_sens) == LOW){

        turnRight();
       }
     }

     if(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == HIGH){

      //detects wall on left, so spin away to setup for next archLeft
      while(digitalRead(left_sens) == LOW){

        clockwiseSpin();
      }
      
     }

     if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == LOW){

      // for now spin in place to put the wall on the left
      while(digitalRead(left_sens) == HIGH){

        archRight();
        
      }
     }
    
   }
    
  }
  
}

