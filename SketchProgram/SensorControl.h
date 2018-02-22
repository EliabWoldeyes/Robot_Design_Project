/*	All function prototypes
	defined in SensorControl.cpp
*/

#ifndef	SENSOR_CONTROL_FUNC
	#define SENSOR_CONTROL_FUNC

  // Black is low from sensor, but digitalRead as high
  // White is high from sensor, but digitalRead as low

	// Pins for sensor inputs
  const int left_sens = 8;
  const int middle_sens = 12;
	const int right_sens = 7;

	boolean leftLow();
	boolean leftHigh();

  boolean middleLow();
  boolean middleHigh();

	boolean rightLow();
	boolean rightHigh();

#endif
