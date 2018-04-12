#include "Arduino.h"
#include "SensorControl.h"


// Black is low from sensor, but digitalRead as high
// White is high from sensor, but digitalRead as low

//left sensor reading LOW
boolean leftLow(){
	return digitalRead(left_sens) == LOW;
}

boolean leftDiagonalLow(){
  return digitalRead(left_diagonal_sens) == LOW;
}

//left sensor reading HIGH
boolean leftHigh(){
	return digitalRead(left_sens) == HIGH;
}

boolean leftDiagonalHigh(){
  return digitalRead(left_diagonal_sens) == HIGH;
}

//right sensor reading LOW
boolean rightLow(){
	return digitalRead(right_sens) == LOW;
}

boolean rightDiagonalLow(){
  return digitalRead(right_diagonal_sens) == LOW;
}

//right sensor reading HIGH
boolean rightHigh(){
	return digitalRead(right_sens) == HIGH;
}

boolean rightDiagonalHigh(){
  return digitalRead(right_diagonal_sens) == HIGH;
}
