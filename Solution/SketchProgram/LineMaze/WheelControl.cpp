#include "Arduino.h"
#include "WheelControl.h"

//----------------------LEFT WHEEL FUNCTIONS----------------

void leftWheelForward()
{
  digitalWrite(left_AB, HIGH);
  digitalWrite(left_AA, LOW);   // Opposite of L911OS chart
}

void leftWheelBackward()
{
  digitalWrite(left_AB, LOW);
  digitalWrite(left_AA, HIGH);   // Opposite of L911OS chart
}

void leftWheelStop()
{
  digitalWrite(left_AB, LOW);
  digitalWrite(left_AA, LOW);

}

//PWM output to the left wheel to run it at half speed
void leftWheelHalf(){
  analogWrite(left_AB, 127);
  analogWrite(left_AA, 0);   
}


//----------------------RIGHT WHEEL FUNCTIONS----------------

void rightWheelForward()
{
  digitalWrite(right_BB, LOW);
  digitalWrite(right_BA, HIGH); // Same as L911OS chart

}

void rightWheelBackward()
{
  digitalWrite(right_BB, HIGH);
  digitalWrite(right_BA, LOW); // Same as L911OS chart
}

void rightWheelStop()
{
  digitalWrite(right_BB, LOW);
  digitalWrite(right_BA, LOW);

}

//PWM output to the right wheel to run it at half speed
void rightWheelHalf(){
  analogWrite(right_BA, 127);
  analogWrite(right_BB, 0);   
}
