#include "WheelControl.h" //wheel pin constants defined here
#include "SensorControl.h" //sensor pin constants defined here
#include "DirectionControl.h"
#include "RobotStates.h"

#define STATES 4

// Black is low from sensor, but digitalRead as high
// White is high from sensor, but digitalRead as low

RobotState robotState = {
  FORWARD,   //previous state
  FORWARD    //current state
};

int intialized = 0;
int currState = 0;  // current junction
int count = 0;      // populated junctions' info

//int decisionMade = 0; // direction executed.
#define MAX = 10;

typedef struct {
  unsigned char leftState;
  unsigned char forState;
  unsigned char rightState;
  unsigned char backState;
} junction_info;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Setup pins -----
  // Motors
  pinMode(right_BB, OUTPUT);
  pinMode(right_BA, OUTPUT);
  pinMode(left_AB, OUTPUT);
  pinMode(left_AA, OUTPUT);

  // Sensors
  pinMode(left_sens, INPUT);
  pinMode(middle_sens, INPUT);
  pinMode(right_sens, INPUT);
  
  
}

 
void loop() {


}

/* FSM
 * #1: 010 - Forward
 * #2: 000 - Dead end and correction.
 * #3: 100 001  - Corrections.
 * #4: 110 011  - Hard turns.
 * #5: 101      - T junction.    
 * #6: 111      - END    
 * "+" junction ingored, if needed the code is ready to differentiate * END and +
 */


void run(){

  // #1 If left and right sensors see white and middle sensors detects the black line.
  if(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == LOW)
  {
    while(digitalRead(left_sens) == LOW && digitalRead(right_sens) == LOW){
      // Forward
      moveForward();
    }
  }

  // Since middle sensor added, this could be the normal line following if middle goes LOW before a side sensor goes HIGH too often.
  // #2 if middle sensor does not detect the black line then check if still inbetween with a pivot in one direction.
  // solves dead end.
  else if (digitalRead(left_sens) == LOW && digitalRead(middle_sens) == LOW && digitalRead(right_sens) == LOW)
  {
    // if no detection.
    while(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == LOW && digitalRead(right_sens) == LOW){
       //clockwiseSpin();
       turnRight();
    }
    fullStop();
    
    // check which sensor hits the black line first.
    // situation is the line is still in the middle so adjust it so the middle sensor is back on it.
    if (digitalRead(left_sens) == HIGH){
      // spin counterclock until middle hits black
      while(digitalRead(middle_sens) == LOW)
      {
        //counterClockSpin();
        turnLeft();
      }
      fullStop();
    }
    
    // Situation - tape still in middle
    else if(digitalRead(middle_sens) == HIGH)
    {
      fullStop();
      // normal operation, let it loop back to #1
    }
    
    // situation - spinning clockwise and right sensor hitting first likely means 180 past the deadend.
    // Align middle sensor
    else if(digitalRead(right_sens) == HIGH)
    {
      while(digitalRead(middle_sens) == LOW)
      {
        //clockwiseSpin();
        turnRight();
      }
      fullStop();
    }
  }
  
  // # 3 RE-ALIGN
  else if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == LOW && digitalRead(right_sens) == LOW){
    // If left sensor is HIGH, detects the black line, adjust left.
    // case where middle is not one black
    // Turn left until middle re-aligns
    
    {
      while(digitalRead(middle_sens) == LOW)
      {
        if(digitalRead(right_sens) == HIGH && digitalRead(left_sens) == HIGH){
          fullStop();
          break;  // evaluate if end in first check for both sensors black, just break
        }
        // Pivot Left
        counterClockSpin();
      }
      fullStop();
    }
  }
  else if(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == LOW && digitalRead(right_sens) == HIGH){
    // If right sensor is HIGH, detects the black line, adjust right.
    // case where middle is not one black
    // Turn right until input goes low.

      while(digitalRead(middle_sens) == LOW){
        if(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == HIGH){
          fullStop();
          break;  // evaluate if end in first check for both sensors black, just break
        }
        // Pivot Right
        clockwiseSpin();        
      }
      fullStop();
  }
  
  // # 4 Hard turns
  // Left turn
  else if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == LOW){

    moveForward();
    delay(50);
    fullStop();
    
    // counter clock spin middle sensor off black if "+" junction if "+"
    while(digitalRead(middle_sens) == HIGH){
      //counterClockSpin();
      turnLeft();
    }
    fullStop();

    // counter clock spin middle to the left black line of the junction.
    while(digitalRead(middle_sens) == LOW){
      //counterClockSpin();
      turnLeft();
    }
    fullStop();
  }

  // right turn
  else if(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == HIGH)
    {
    moveForward();
    delay(50);
    fullStop();

    // counter clock spin middle sensor off black if "+" junction if "+"
    while(digitalRead(middle_sens) == HIGH){
      //clockwiseSpin();
      turnRight();
    }
    fullStop();

    // counter clock spin middle to the left black line of the junction.
    while(digitalRead(middle_sens) == LOW){
      //clockwiseSpin();
      turnRight();
    }
    
    fullStop();   
  }
  
  // #5 T junction. always turn left.
  else if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == LOW && digitalRead(right_sens) == HIGH)
  {

    moveForward();
    delay(50);
    fullStop();
    
    // counter clock spin middle to the left black line of the junction.
    while(digitalRead(middle_sens) == LOW){
      //counterClockSpin();
      turnLeft();
    }
    fullStop();
    
    
  // #6 Assume all black is END. "+" junction ignored, but code ready to deal with one if neccessary.
  } else if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == HIGH){
    while(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == HIGH){
      fullStop();
    }
  }
  
}

// 3 sensor always choose left turn at junctions
int End_OR_turnleft(){
  // Check if all sensors detect black. Could be END block or "+" junction
    if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == HIGH)
    {
      moveForward();
      delay(200);
      fullStop();
      delay(50);
      fullStop();

      // move forward, and if all still black then assume it is the END
      if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == HIGH){
        return 1;
      }
      // if not END, reverse back to junction.
      else{
        while(digitalRead(left_sens) == LOW && digitalRead(right_sens) == LOW){
          moveBackward();
        }
        fullStop();
      }
      // "+" junction
      // If not back on the junction, need to re-align sensors.
      if(digitalRead(left_sens) == LOW || digitalRead(middle_sens) == LOW || digitalRead(right_sens) == LOW){
        
        while(digitalRead(left_sens) == LOW || digitalRead(middle_sens) == LOW || digitalRead(right_sens) == LOW){

          unsigned char align = 0b000;
          if(digitalRead(left_sens) == HIGH){
            align = align | (1 << 2);
          }
          if(digitalRead(middle_sens) == HIGH){
            align = align | (1 << 1);
          }
          if(digitalRead(right_sens) == HIGH){
            align = align | 1;
          }
          
          switch(align){

            case(0b001):
              while(digitalRead(left_sens) == LOW)
              {
                counterClockSpin();
              }
              fullStop();
              break;

            case(0b010):
              while(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == LOW){
                clockwiseSpin();
              }
              fullStop();

              if(digitalRead(left_sens) == HIGH){
                while(digitalRead(middle_sens) == LOW){
                  counterClockSpin();
                }
                fullStop();
              }
              break;

            case(0b011):
              while(digitalRead(left_sens) == LOW){
                counterClockSpin();
              }
              fullStop();
              break;

            case(0b100):
              while(digitalRead(right_sens) == LOW){
                clockwiseSpin();
              }
              fullStop();
              break;
              
            case(0b101): // odd ball
              //while(digitalRead(middle_sens) == LOW){
                
              //}
              fullStop();
              break;
              
            case(0b110):
              while(digitalRead(right_sens) == LOW){
                clockwiseSpin();
              }
              fullStop();
              break;
              
            case(0b111):
              break;
            default:
              break;
           }
          
         }
       }
    } // "T" junction
    else if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == LOW && digitalRead(right_sens) == HIGH){
      // dont need to do anything, since it didn't advance and always pick left
    }
    

    // After re-lign, always go left at the junction
    
    // counter clock spin middle sensor off black if "+" junction if "+"
    while(digitalRead(middle_sens) == HIGH){
      counterClockSpin();
    }
    fullStop();

    // counter clock spin middle to the left black line of the junction.
    while(digitalRead(middle_sens) == LOW){
      counterClockSpin();
    }
    fullStop();
    
    return 0;

}


