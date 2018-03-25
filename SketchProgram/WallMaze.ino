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
<<<<<<< HEAD
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

=======
 * 000 forward
 * 101 forward
 * 
 * adjusting needed, i think
 * 
 * could do 90 degree turns if accurate, otherwise micro adjust turns on sensor conditions
 * 
 * 010 front blocked, always pick left
 * 
 * 
 * 011 left open
 * 110 right open
 * 
 * Two openings
 * 001
 * 100
 * 
 * 111 all blocked, 180, unless this indicates end
 */

void run(){
  while(1){
    if((digitalRead(left_sens) == WALL && digitalRead(middle_sens) == NOWALL && digitalRead(right_sens) == WALL) || (digitalRead(left_sens) == NOWALL && digitalRead(middle_sens) == NOWALL && digitalRead(right_sens) == NOWALL)){
      moveForward();
    }
    else if(digitalRead(left_sens) == NOWALL && digitalRead(middle_sens) == WALL && digitalRead(right_sens) == NOWALL){
      while(digitalRead(middle_sens) == WALL){
        counterClockSpin();
      }
    }
    // left opening
    else if(digitalRead(left_sens) == NOWALL && digitalRead(middle_sens) == WALL && digitalRead(right_sens) == WALL){
      while(digitalRead(middle_sens) == WALL){
        counterClockSpin();
      }
    }
    // right opening
    else if(digitalRead(left_sens) == WALL && digitalRead(middle_sens) == WALL && digitalRead(right_sens) == NOWALL){
      while(digitalRead(middle_sens) == WALL){
        clockwiseSpin();
      }
    }
    // left and middle open
    else if(digitalRead(left_sens) == NOWALL && digitalRead(middle_sens) == NOWALL && digitalRead(right_sens) == WALL){
      while(){
        
      }
    }
    // right and middle open
    else if(digitalRead(left_sens) == NOWALL && digitalRead(middle_sens) == NOWALL && digitalRead(right_sens) == WALL){
      while(){
           
      }
    }
    // all blocked,180 and go back, unless this indicates end. Only if partial turn, it will enter another state and continue the turn
    else if(digitalRead(left_sens) == WALL && digitalRead(middle_sens) == WALL && digitalRead(right_sens) == WALL){
      while(digitalRead(middle_sens) == WALL){
        counterClockSpin();
      }
    }
    
  }
}

>>>>>>> d31e76945fa48105dcd70b20c4405086937a1487
