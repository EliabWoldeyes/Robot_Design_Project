#include "Arduino.h"
#include "RobotStates.h"
#include "SensorControl.h"

//Returns a state value depending on current sensor data
State determineRobotState(){

  if(leftHigh() && rightLow()){
    return LEFT;
  }

  else if(leftLow() && rightHigh()){
    return RIGHT;
  }

  else{
    return FORWARD;
  }
}

//Update the new Robot state setting:
//      previous state  -->   current state
//      current state   -->   new state
void updateRobotState(RobotState curState, State newState){
  curState.previousState = curState.currentState;
  curState.currentState = newState;
}

