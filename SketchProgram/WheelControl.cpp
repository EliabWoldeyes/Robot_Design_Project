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
