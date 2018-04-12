#include "DirectionControl.h"
#include "WheelControl.h"
#include "Arduino.h"

void moveForward()
{
 	leftWheelForward();
	rightWheelForward();
}

void moveBackward()
{
	leftWheelBackward();
	rightWheelBackward();
}

void fullStop()
{
	leftWheelStop();
	rightWheelStop();
}

//move forward hanging to the left
void archLeft(){
  leftWheelHalf();
  rightWheelForward();
}

//move backwards hanging to the left
void archBackLeft(){
  leftWheelHalfBack();
  rightWheelBackward();
}

//move forwards hanging to the right
void archRight(){
  leftWheelForward();
  rightWheelHalf();
}

//move backwards hanging to the right
void archBackRight(){
  rightWheelHalfBack();
  leftWheelBackward();
}

/*	NOTE: turnLeft() and turnRight() do not control
	stopping. If called in main loop, the robot
	will keep spinning.
*/

//turns left (pivoting on left wheel) with wide berth
void turnLeft()
{
  leftWheelStop();
  rightWheelForward();
}

void turnLeftBack()
{
  leftWheelStop();
  rightWheelBackward();
}

//turns left (pivoting on left wheel)
void turnLeftWide()
{
	leftWheelQuarter();
	rightWheelForward();
}

//turns right (pivoting on right wheel)
void turnRight()
{
	leftWheelForward();
	rightWheelStop();
}

// spinning may be more efficient than pivots. Something to experiment with.
// Clock wise spin the robot
void clockwiseSpin()
{
	leftWheelForward();
	rightWheelBackward();
}

// Counter clock wise spin the robot
void counterClockSpin()
{
	leftWheelBackward();
	rightWheelForward();
}

