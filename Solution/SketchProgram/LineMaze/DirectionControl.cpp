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

//move forward while hanging left
void archLeft(){
  leftWheelHalf();
  leftWheelForward();
}

//move forward while hanging right
void archRight(){
  leftWheelForward();
  rightWheelHalf();
}

/*	NOTE: turnLeft() and turnRight() do not control
	stopping. If called in main loop, the robot
	will keep spinning.
*/

//turns left (pivoting on left wheel)
void turnLeft()
{
	leftWheelStop();
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

