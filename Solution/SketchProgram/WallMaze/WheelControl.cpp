#include "Arduino.h"
#include "WheelControl.h"

//----------------------LEFT WHEEL FUNCTIONS----------------

//turn the left wheel forward
void leftWheelForward()
{
  digitalWrite(left_AB, HIGH);
  digitalWrite(left_AA, LOW);   // Opposite of L911OS chart
}

//turn the left wheel backward
void leftWheelBackward()
{
  digitalWrite(left_AB, LOW);
  digitalWrite(left_AA, HIGH);   // Opposite of L911OS chart
}

//stop the left wheel
void leftWheelStop()
{
  digitalWrite(left_AB, LOW);
  digitalWrite(left_AA, LOW);
}

//turn the left wheel backwards at approximately half speed (tested value)
void leftWheelHalfBack()
{
  analogWrite(left_AB, 0);
  analogWrite(left_AA, 180);   // Opposite of L911OS chart
}

//turn the left wheel forwards at approximately half speed (tested value)
void leftWheelHalf(){
  analogWrite(left_AB, 180);
  analogWrite(left_AA, 0);   
}

//turn the left wheel forward at approximately a quarter full speed (tested value)
void leftWheelQuarter(){
  analogWrite(left_AB, 100);
  analogWrite(left_AA, 0);   
}


//----------------------RIGHT WHEEL FUNCTIONS----------------

//turn the right wheel forward
void rightWheelForward()
{
  digitalWrite(right_BB, LOW);
  digitalWrite(right_BA, HIGH); // Same as L911OS chart
}

//turn the right wheel backward
void rightWheelBackward()
{
  digitalWrite(right_BB, HIGH);
  digitalWrite(right_BA, LOW); // Same as L911OS chart
}

//stop the right wheel
void rightWheelStop()
{
  digitalWrite(right_BB, LOW);
  digitalWrite(right_BA, LOW);
}

//turn the right wheel backwards at approximately half speed (tested value)
void rightWheelHalfBack()
{
  analogWrite(right_BB, 180);
  analogWrite(right_BA, 0); // Same as L911OS chart
}

//turn the right wheel forwards at approximately half speed (tested value)
void rightWheelHalf(){
  analogWrite(right_BA, 180);
  analogWrite(right_BB, 0);   
}
