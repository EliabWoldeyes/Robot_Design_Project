//Author: Jonathan Chan

#include "WheelControl.h" //wheel pin constants defined here
#include "SensorControl.h" //sensor pin constants defined here
#include "DirectionControl.h"

const int echoPin = 4;
const int trigPin = 3;

//in cm
const int THRESHOLD_DISTANCE = 5;
const int TURN_DISTANCE = 8; //distance to clear before making a left turn so wheel doesn't get stuck on the wall
const int MAX_DISTANCE = 150;

int startDistance = 0;
int delta = 0;
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
  myRun();

//    moveForward();
//    delay(1000);
//    fullStop();
//    delay(2000);

//  while (getDistance() < THRESHOLD_DISTANCE) {Serial.print(getDistance(),DEC);Serial.print("\n");}
//  Serial.print(getDistance(),DEC);Serial.print("\n");

//if(rightDiagonalHigh() && rightHigh() && leftDiagonalHigh() && leftHigh()) {
//      startDistance = getDistance();
//      delta = min(LEFT_TURN_DISTANCE,(startDistance-THRESHOLD_DISTANCE));
//      while ((startDistance - getDistance()) < delta){
//        Serial.print((startDistance),DEC);
//        Serial.print("----");
//        Serial.print((getDistance()),DEC);
//        Serial.print("\n");
//        moveForward();
//      }
//      turnLeft();
//    }

}

int getDistance(){
  // Clears the trigPin
  delay(50);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  return ((int) duration*0.034/2 < 0) ? 0 : (int) duration*0.034/2;
}


void myRun(){

  //Normal operation with no obstruction ahead
  if (getDistance() > THRESHOLD_DISTANCE) {
    //Denis: this moveForward is for what purpose?
//    moveForward();
//    archLeft();

    if(leftLow() || leftDiagonalLow()){
      moveForward();
      delayMicroseconds(5);
      archRight();
    }

    else if((rightLow() || rightDiagonalLow())){
      moveForward();
      delayMicroseconds(5);
      archLeft();

      if(rightHigh() && rightDiagonalHigh){
        while(rightDiagonalHigh()) clockwiseSpin();
      }
    }

    else if(rightDiagonalHigh() && rightHigh() && leftDiagonalHigh() && leftHigh()) {
//      startDistance = getDistance();
//      delta = min(LEFT_TURN_DISTANCE,(startDistance-THRESHOLD_DISTANCE));
//      while ((startDistance - getDistance()) < delta){
////        Serial.print((startDistance),DEC);
////        Serial.print("----");
////        Serial.print((getDistance()),DEC);
////        Serial.print("\n");
//        moveForward();
//      }

//      while (getDistance<THRESHOLD_DISTANCE && rightDiagonalHigh() && rightHigh() && leftDiagonalHigh() && leftHigh()) {
//        moveForward();
//      }

        turnLeftWide();
    }

    else if(rightDiagonalLow() && leftDiagonalLow()){

      while(leftHigh()){
        archBackLeft();
      }
//      if(leftHigh() && rightLow()){
//        moveForward();
//        delayMicroseconds(5);
//        while(getDistance > THRESHOLD_DISTANCE){
//          counterClockSpin();
//        }
//      }
//      else{
//        moveForward();
//        delayMicroseconds(5);
//        while(getDistance > THRESHOLD_DISTANCE){
//          clockwiseSpin();
//        }
//      }
    }

    else{
      moveForward();
      delayMicroseconds(5);
      //Denis: default case, what incuded here and why archleft and turnLeft or smth?
      archLeft();
    }
  }

  //There's an obstruction ahead
  else if (getDistance() < THRESHOLD_DISTANCE) {

    if (rightDiagonalLow() && leftDiagonalLow()){
      while(leftHigh()){
        archBackLeft();
      }
    }
    else if (leftHigh()){
      moveForward();
      delayMicroseconds(5);
      while (getDistance() < THRESHOLD_DISTANCE){
        counterClockSpin();
      }
    }

    else if (rightHigh()){
      moveForward();
      delayMicroseconds(5);
      while (getDistance() < THRESHOLD_DISTANCE){
        clockwiseSpin();
      }
    }

    else if (leftLow() && leftDiagonalLow() && rightDiagonalLow() && rightHigh()){
      moveForward();
      delayMicroseconds(5);
      clockwiseSpin();
    }

    else if (leftLow() && leftDiagonalLow() && rightLow() && rightDiagonalLow()){
//      moveForward();
//      delayMicroseconds(5);
      while ( !(rightDiagonalHigh() && rightHigh())){
        moveBackward();

        if(leftLow() || leftDiagonalLow()){
          archBackRight();
        }
        else if(rightLow() || rightDiagonalLow()){
          archBackLeft();
        }
        else moveBackward();
//        clockwiseSpin();
//        if (rightDiagonalHigh()){
//          //Denis: block is for backing, but we have moveForward with delay and then moveBackward without any delay. Hmm?
//          //moveForward();
//          delayMicroseconds(5);
//          moveBackward();
//        }
      }

      while(leftLow() && leftDiagonalLow() && rightLow() && rightDiagonalLow() && getDistance() < THRESHOLD_DISTANCE+TURN_DISTANCE) clockwiseSpin();
      
    }
    
    else fullStop();
  }

}

