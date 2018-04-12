#include "Arduino.h"
#include "SensorControl.h"


// Black is low from sensor, but digitalRead as high
// White is high from sensor, but digitalRead as low

boolean leftLow(){
	return digitalRead(left_sens) == LOW;
}

boolean leftHigh(){
	return digitalRead(left_sens) == HIGH;
}

boolean middleLow(){
	return digitalRead(middle_sens) == LOW;
}

boolean middleHigh(){
	return digitalRead(middle_sens) == HIGH;
}

boolean rightLow(){
	return digitalRead(right_sens) == LOW;
}

boolean rightHigh(){
	return digitalRead(right_sens) == HIGH;
}
