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

