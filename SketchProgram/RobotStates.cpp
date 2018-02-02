#include "Arduino.h"
#include "RobotStates.h"
#include "SensorControl.h"

//Returns a state value depending on last state and current sensor data
State determineRobotState(){
  return STOP;
}

//Update the new Robot state setting:
//      previous state  -->   current state
//      current state   -->   new state
void updateRobotState(RobotState curState, State newState){
  curState.previousState = curState.currentState;
  curState.currentState = newState;
}

