//Author: Jonathan Chan

#include "WheelControl.h" //wheel pin constants defined here
#include "SensorControl.h" //sensor pin constants defined here
#include "DirectionControl.h"

const int echoPin = 4;
const int trigPin = 3;

boolean goLeft, goRight = false;

long duration;

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
//  pinMode(middle_sens, INPUT);
  pinMode(right_sens, INPUT);
  pinMode(right_diagonal_sens, INPUT);
  pinMode(left_diagonal_sens, INPUT);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//  myRun();

  while (getDistance() < 15) Serial.print("DETECTED\n");
}

int getDistance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  return (int) duration*0.034/2;
}


void myRun(){

//  //handle cases with no obstruction directly in front
//  if(middleHigh()){
//    
//    //move forward but keep to the left-hand wall
////    if(leftLow() && rightLow()){
//      archLeft();
////    }
//  
//    //adjust right if it gets too close to the left wall
//    if(leftLow() && rightHigh()){
//      while(rightHigh() && middleHigh() && leftLow()){
//        archRight();
//      }
//    }
//
//    /*adjust left if it gets too close to the right wall
//      (might not need this since we always want to go left)
//    */
//    else if(leftHigh() && rightLow()){
//      while(leftHigh() && middleHigh() && rightLow()){
//        archLeft();
//      }
//    }
//  }
//  
//  //handle cases were the there is an obstruction directly ahead
//  else{
//    //stop so we can determine where an open path is
//    fullStop();
//
//    if(leftLow() && rightHigh()){
//      while(middleLow()){
//        clockwiseSpin();
//      }
//      archRight();
//    }
//
//    else{
//      while(middleLow()){
//        counterClockSpin();
//      }
//      archLeft();
//    }

//    //reached a corner
//    if(leftLow() && rightHigh()) goRight = true;
//
//    //otherwise default left
//    else goLeft = true;
//    
//    //we want to back up a little to give the robot space to turn if it needs to
//    while(middleLow()) moveBackward();
//
//    if(goRight){
//      while(rightHigh() && middleHigh()){
////        clockwiseSpin();
//        turnRight();
//      }
//    }
//
//    else if(goLeft){
//      while(leftHigh() && middleHigh()){
////        counterClockSpin();
//        archLeft();
//      }
//    }
//
//    //reset turn flags
//    goRight = false;
//    goLeft = false; 
//    
//  }
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

//  while(1){
//
//    /* Don't we need to handle the case where neither left or right are low? */
//
//   // high means it does not detect the wall, so move in an arch left until it finds it
//   while(digitalRead(left_sens) == HIGH || digitalRead(middle_sens) == HIGH){
//
//     archLeft();
//     
//     // If both detect a wall, then assume it is a corner.
//     if(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == LOW){
//
//       while(digitalRead(middle_sens) == LOW){
//
//        turnRight();
//       }
//
//       // checking left hand side and ensure the head of the robot is pointing greater than parallel to the left wall
//       if(digitalRead(left_sens) == HIGH){
//
//        while(digitalRead(left_sens) == HIGH){
//
//          turnRight();
//        }
//       }
//
//
//       if(digitalRead(left_sens) == LOW){
//        while(digitalRead(left_sens) == LOW){
//          turnRight();
//        }
//       }
//       
//     }
//
//    
//     if(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == HIGH){
//
//      //detects wall on left, so turn away to setup for next archLeft
//      while(digitalRead(left_sens) == LOW){
//
//        turnRight();
//      }
//      
//     }
//
//     if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == LOW){
//
//      // for now move in a circle until it detects a wall on its left sensor. If none, feedback to the operator.
//      while(digitalRead(left_sens) == HIGH){
//
//        archRight();
//        
//      }
//     }
//    
//   }
//    
//  }
  
}

