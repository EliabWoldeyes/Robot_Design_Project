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

void archLeft(){
  leftWheelHalf();
  leftWheelForward();
}

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

/*	Attempt at 90 degree turn functions. Delay is
	hardcoded from observing approximately 90
	degree turn.
	
	Delay value is only valid when using USB power
	source. Battery power source spins motor too
	fast.
*/

void turnLeft90Degrees()
{
	fullStop();
	turnLeft();
	delay(700);
	fullStop();
}

void turnRight90Degrees()
{
	fullStop();
	turnLeft();
	delay(700);
	fullStop();
}

