//Author: Jonathan Chan

#include "WheelControl.h" //wheel pin constants defined here
#include "SensorControl.h" //sensor pin constants defined here
#include "DirectionControl.h"

const int echoPin = 4;
const int trigPin = 3;

//in cm
const int THRESHOLD_DISTANCE = 8;
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
//  myRun();

//  while (getDistance() < THRESHOLD_DISTANCE) {Serial.print(getDistance(),DEC);Serial.print("\n");}
  Serial.print(getDistance(),DEC);Serial.print("\n");

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
//    archLeft();
    moveForward();

    if((leftLow() && rightHigh()) || leftDiagonalLow()){
      archRight();
//      turnRight();
    }

    else if((leftHigh() && rightLow()) || rightDiagonalLow()){
      archLeft();
//      turnLeft();
    }
  }

  //There's an obstruction ahead
  else if ((getDistance() < THRESHOLD_DISTANCE) && (rightDiagonalLow() || leftDiagonalLow())) {

    //specific case for if reached a left-hand corner
    if(leftLow() && rightHigh()){
      fullStop();
    }

    //any other case we want to turn left
    else {
//      while (rightDiagonalLow() || getDistance() < THRESHOLD_DISTANCE) counterClockSpin();
    }
  }

  else if (getDistance() < THRESHOLD_DISTANCE && rightDiagonalHigh() && leftDiagonalHigh()) {
    fullStop();
  }

}

