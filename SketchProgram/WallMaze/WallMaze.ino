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
  pinMode(right_sens, INPUT);
  pinMode(right_diagonal_sens, INPUT);
  pinMode(left_diagonal_sens, INPUT);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  myRun();
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

  if (getDistance() > THRESHOLD_DISTANCE){

    if (leftLow() && leftDiagonalLow()){
      if (rightDiagonalLow()) {
        if(rightHigh()){
          while (leftDiagonalLow()) {
            clockwiseSpin();
          }
        }
        archBackLeft();
      }
      else {
        turnRight(); 
      }
    }
    else if (leftLow() && leftDiagonalHigh()){
      moveForward();
    }
    else if (leftHigh() && leftDiagonalLow()){
      if(rightDiagonalLow()){
        if(rightHigh()){
          while (leftDiagonalLow()) {
            clockwiseSpin();
          }
        }
        archBackLeft();
      }
      else {
        turnRight();
      }
    }
    else if (leftHigh() && leftDiagonalHigh()){
      if (rightDiagonalHigh()){
        turnLeft();
      }
      else{
        turnLeftWide();
      }
    }
    else if (rightLow() || rightDiagonalLow()){
      turnLeft();
    }
  }

  else if (getDistance() <= THRESHOLD_DISTANCE){
    
    if (leftDiagonalLow() && rightDiagonalLow()){
      
      if (leftHigh() && rightHigh()){
        archBackLeft();
      }
      else if (leftLow() && rightHigh()){
        clockwiseSpin();
      }
      else if (leftHigh() && rightLow()){
        clockwiseSpin();
      }
      
      //DEAD END SITUATION
      else if (leftLow() && rightLow()){
        while (rightDiagonalLow()){
          archBackLeft();
        }
        clockwiseSpin();
        delay(500);
      }
    }
  }
}

