//Author: Jonathan Chan

#include "WheelControl.h" //wheel pin constants defined here
#include "SensorControl.h" //sensor pin constants defined here
#include "DirectionControl.h"

const int echoPin = 4;
const int trigPin = 3;

//in cm
const int THRESHOLD_DISTANCE = 5;
const int MAX_DISTANCE = 150;

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

//  while (getDistance() < THRESHOLD_DISTANCE) {Serial.print(getDistance(),DEC);Serial.print("\n");}
//  Serial.print(getDistance(),DEC);Serial.print("\n");

}

int getDistance(){
  // Clears the trigPin
  delay(5);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH,600000);
  
  // Calculating the distance
  return (int) duration*0.034/2;
}


void myRun(){

  //Normal operation with no obstruction ahead
  if (getDistance() > THRESHOLD_DISTANCE) {
    moveForward();
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
    }

    else if(rightDiagonalHigh() && rightHigh() && leftDiagonalHigh() && leftHigh()) {
      turnLeft();
    }

    else if(rightDiagonalLow() && leftDiagonalLow()){
      if(leftHigh() && rightLow()){
        moveForward();
        delayMicroseconds(5);
        while(getDistance > THRESHOLD_DISTANCE){
          counterClockSpin();
        }
      }
      else{
        moveForward();
        delayMicroseconds(5);
        while(getDistance > THRESHOLD_DISTANCE){
          clockwiseSpin();
        }
      }
    }

    else{
      moveForward();
      delayMicroseconds(5);
      archLeft();
    }
  }

  //There's an obstruction ahead
  else if (getDistance() < THRESHOLD_DISTANCE) {

    if (leftHigh()){
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
      moveForward();
      delayMicroseconds(5);
      while (getDistance() < THRESHOLD_DISTANCE && rightDiagonalLow() && rightLow()){
        clockwiseSpin();
        if (rightDiagonalHigh()){
          moveForward();
          delayMicroseconds(5);
          moveBackward();
        }
      }
    }
    
    else fullStop();
  }

}

