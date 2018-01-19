/*	All function prototypes defined
	in WheelControl.cpp
*/

#ifndef WHEEL_CONTROL_FUNC
	#define WHEEL_CONTROL_FUNC

	// Pins for Motor B
	const int right_BB = 5;
	const int right_BA = 6;

	// Pins for Motor A
	const int left_AB = 9;
	const int left_AA = 10;

	// Pins for sensor inputs
	const int right_sens = 7;
	const int left_sens = 8;

	void leftWheelForward();

	void leftWheelBackward();

	void leftWheelStop();

	void rightWheelForward();

	void rightWheelBackward();

	void rightWheelStop();

#endif