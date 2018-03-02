#include "WheelControl.h" //wheel pin constants defined here
#include "SensorControl.h" //sensor pin constants defined here
#include "DirectionControl.h"
#include "RobotStates.h"

#define STATES 4

int End_OR_turnleft();

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
  
  
  // -----
}

void loop() {

//  if(leftLow() && rightLow()){
//    moveForward();
//  }
//
//  else if(leftHigh() && rightLow()) {
//    
////    updateRobotState(robotState,RIGHT);
//
//    while(leftHigh() && rightLow()){
//      counterClockSpin();
//    }
////    moveForward();
//  }
//
//  else if(leftLow() && rightHigh()) {
//    
//    while(leftLow() && rightHigh()) {
//      clockwiseSpin();
//    }
//    
//  }
//
//  else if(leftHigh() && rightHigh()) {
//    //move foward a little bit and stop
//    moveForward();
//    delay(50);
//    fullStop();
//
//    //reached the end so stop
//    if(leftHigh() && rightHigh()){
//      while(leftHigh() && rightHigh()){
//        fullStop();
//      }
//    }
//
//    else{
//      while(!leftHigh() && !rightHigh()){
//        moveBackward();
//      }
//
//      updateRobotState(robotState,determineRobotState());
//
//      if(robotState.currentState == LEFT) {
//        while(leftHigh()){
//          counterClockSpin(); 
//        }
//      }
//      else if(robotState.currentState == RIGHT) {
//        while(rightHigh()){
//          clockwiseSpin();
//        }
//      }
//      
//    }
////    checkEnd();
//  }

initialCode();

}















//--------------------------------------------------------INITIAL CODE----------------------------------------------------------

/* FSM
 * #1: 010 - Forward
 * #2: 000 - Dead end and correction.
 * #3: 111 110 011 - Junction and Correction.
 *      110 111 - Junction
 *      100 101 - Left
 *      001 011 - Right
 * #
 */

//if(junctionDecision() == 1) for states
//if(End_OR_turnleft() == 1) for always pick left.
void initialCode(){

  
   // put your main code here, to run repeatedly:
  
  // #1 If left and right sensors see white and middle sensors detects the black line.

  if(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == LOW)
  {
    // Forward ------
    moveForward();
    
    // Manual PWM to adjust speed
    //delayMicroseconds(1200);
    //fullStop();
    //delayMicroseconds(2041 - 1200);
    // -----
  }

  // Since middle sensor added, this could be the normal line following if middle goes LOW before a side sensor goes HIGH too often.
  // #2 if middle sensor does not detect the black line then check if still inbetween with a pivot in one direction.
  // solves dead end.

  else if (digitalRead(left_sens) == LOW && digitalRead(middle_sens) == LOW && digitalRead(right_sens) == LOW)
  {
    // if no detection.
    while(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == LOW && digitalRead(right_sens) == LOW){
       clockwiseSpin();
    }
    fullStop();
    // check which sensor hits the black line first.

    // situation is the line is still in the middle so adjust it so the middle sensor is back on it.
    if (digitalRead(left_sens) == HIGH){
      // spin counterclock until middle hits black
      while(digitalRead(middle_sens) == LOW)
      {
        counterClockSpin();
      }
      fullStop();
    }
    // Situation - tape still in middle
    else if(digitalRead(middle_sens) == HIGH)
    {
      fullStop();
      // normal operation, let it loop back to #1
    }
    // situation - spinning clockwise and right sensor hitting first likely means it is a little bit over a deadend.
    // Align middle sensor
    else if(digitalRead(right_sens) == HIGH)
    {
      while(digitalRead(middle_sens) == LOW)
      {
        clockwiseSpin();
      }
      fullStop();
    }
  }
  // --- ---

  // #3
  // middle sensor still black and one of the side sensors is on black.
  // OR middle is white but one of the sides is on black.
  else if((((digitalRead(left_sens) == HIGH || digitalRead(right_sens) == HIGH) && digitalRead(middle_sens) == HIGH) ||
            digitalRead(left_sens) == HIGH || digitalRead(right_sens) == HIGH) && digitalRead(middle_sens) == LOW)
  {
    // If both sensors are HIGH, both detect black.
    // Happens at END block, "T", and "+" junctions.
    //
    while(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == HIGH)
    {
      // ---------------- Behaviour for left ------------------------
      // check of end of maze or junction, could be a T or +.
      //if(junctionDecision() == 1) 
      if(End_OR_turnleft() == 1)
      {
        // Assume finished maze
        while(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == HIGH)
        {
          fullStop();   // loops until reset
        }
      }else {

        break;
      }
    }
    
    // If left sensor is HIGH, detects the black line, adjust left.
    // case where middle is not one black
    // Turn left until middle re-aligns
    if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == LOW && digitalRead(right_sens) == LOW)
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
    // case where middle already on black. state  
    else if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == LOW){

      while(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == LOW)
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

    
    // If right sensor is HIGH, detects the black line, adjust right.
    // case where middle is not one black
    // Turn right until input goes low.
    if(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == LOW && digitalRead(right_sens) == HIGH){
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
    // 
    else if(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == HIGH)
    {
      while(digitalRead(left_sens) == LOW && digitalRead(middle_sens) == HIGH && digitalRead(right_sens) == HIGH )
      {
        if(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == HIGH){
          fullStop();
          break;  // evaluate if end in first check for both sensors black, just break
        }
        // Pivot Right
        clockwiseSpin();
      }
      fullStop();
    }
    

    // need to check if aligned
    if(digitalRead(middle_sens) == LOW){
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
      
    }
    
  }
  
}
/*
int junctionDecision()
{

  // stack pointer, need reset if fresh start.
  if(!intialized){
    intialized = 1;
    
    //int *pStack;              // pointer to the state
    //int* stateBuffer[MAX];     // 4 bytes for the 4 directions, chars

    junction_info* info;
    count = 0;
    
    //pStack = malloc(4 * sizeof(int));

    // 10 pointers to pointers for states
    // int **arrayPointer[MAX];

    /*
     * for (int i = 0; i < MAX; i ++){
     * 
     *  pStack = malloc(4 * sizeof(int)); 
     *  pStack[0] = 2;
     *  pStack[1] = 2;
     *  pStack[2] = 2;
     *  pStack[3] = 2;
     *  
     *  *arrayPointer[i] = &pStack;
     * }
     * count = 5;
     * for (int x = 0; x < count; x ++){
     *  printf("Values are: %d", *(arrayPointer + x));
     * }
     * 
     *  states for directions
     *  0: dead end
        1: Chosen before
        2: Not explored

     */
  
  /* 
  }
  else{
    /*
    moveForward();
    delay(200);
    fullStop();
    delay(50);
    */
/*
    // middle sensor ahead of the sides.
    
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
        
      }// State for the "+" Junction after re-aligning --------------
      // back at previous junction so decrement the direction came from to 0, since only returning to previous junction if the recent junction was exhausted.
      if(currState < count){
        // ---
        info->backState = 0;
        count = currState;
      } else{ // new junction
        info = (junction_info*)malloc(sizeof(junction_info));
  
        info->leftState = 2;
        info->forState = 2;
        info->rightState = 2;
        info->backState = 1;

        currState = currState + 1;
        count = count + 1;
        info = info + 1;
      }
      
    // T junction
    } else if(digitalRead(left_sens) == HIGH && digitalRead(middle_sens) == LOW && digitalRead(right_sens) == HIGH){
      // State for the Junction ------------

      // back at previous junction so decrement the direction came from to 0, since only returning to previous junction if the recent junction was exhausted.
      if(currState < count){
        info->backState = 0;
        count = currState;
      } else { // new junction
        info = (junction_info*)malloc(sizeof(junction_info));
    
        info->leftState = 2;
        info->forState = 0;
        info->rightState = 2;
        info->backState = 1;

        currState = currState + 1;
        count = count + 1;
        info = info + 1;
      }
      
    }

    // make the decision and alter the current states for the junction info
    // sequence is to check Left, forward, right, then back.

     unsigned char temp;
    
    // usually there is a junction that has a direction state = 2, unexplored. Unless revisited junction that has been explored.
    //while(!decisionMade){
      if(info->leftState == 2 || info->forState == 2 || info->rightState == 2 || info->backState == 2){
        if(info->leftState == 2){
          info->leftState == 1;
  
          // make turn ---

          // counter clock spin middle sensor off black if "+" junction.
          while(digitalRead(middle_sens) == HIGH){
            counterClockSpin();
          }
          fullStop();

          // counter clock spin middle to the left black line of the "+" junction
          while(digitalRead(middle_sens) == LOW){
            counterClockSpin();
          }
          fullStop();
          
          // may need more to get it on the line

          //

          // shift states to the left
          temp = info->leftState;
          info->leftState = info->forState;  
          info->forState = info->rightState;
          info->rightState = info->backState;
          info->backState = temp;
          
          //decisionMade = 1;
          
        } else if(info->forState == 2){
          info->forState == 1;
  
          // 
          // go forward
          while(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == HIGH){
            moveForward();
          }
          fullStop();

          // align on the forward line
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

          // left and right flip
          temp = info->leftState;
          info->leftState = info->rightState;
          info->rightState = temp;
          
          //decisionMade = 1;
          
        } else if(info->rightState == 2){
          info->rightState == 1;
  
          // make turn
          
          // clock spin middle sensor off front black if "+" junction.
          while(digitalRead(middle_sens) == HIGH){
            clockwiseSpin();
          }
          fullStop();

          // clock spin middle to the right black line of the "+" junction
          while(digitalRead(middle_sens) == LOW){
            clockwiseSpin();
          }
          fullStop();
          // may need more to get it on the line

          //

          // right shift
          temp = info->backState;
          info->backState = rightState;
          info->rightState = info->forState;
          info->forState = info-leftState;
          info->leftstate = temp;
          
          
          //decisionMade = 1;
          
        } else if(info->backState == 2){ // never, usually 1.
          info->backState == 1;
  
          // 180 back ---
          // off front line
          while(digitalRead(middle_sens) == HIGH){
            counterClockSpin();
          }
          fullStop();

          // to left line
          while(digitalRead(middle_sens) == LOW){
            counterClockSpin();
          }
          fullStop();

          // off left line
          while(digitalRead(middle_sens) == HIGH){
            counterClockSpin();
          }
          fullStop();

          // to 180 line
          while(digitalRead(middle_sens) == LOW){
            counterClockSpin();
          }
          fullStop();

          //decisionMade = 1;
          
        }
      } else if(info->leftState == 1 || info->forState == 1 || info->rightState == 1 || info->backState == 1){
        if(info->leftState == 1){
          info->leftState == 0;
  
          // make turn
          
          // counter clock spin middle sensor off black if "+" junction.
          while(digitalRead(middle_sens) == HIGH){
            counterClockSpin();
          }
          fullStop();

          // counter clock spin middle to the left black line of the "+" junction
          while(digitalRead(middle_sens) == LOW){
            counterClockSpin();
          }
          fullStop();
          
          // may need more to get it on the line

          //

          // shift states to the left
          temp = info->leftState;
          info->leftState = info->forState;  
          info->forState = info->rightState;
          info->rightState = info->backState;
          info->backState = temp;
          
          //decisionMade = 1;

          // pointer to previous junction
          currState = currState - 1;
          info = info - 1;          
          
        } else if(info->forState == 1){
          info->forState == 0;
  
          // make turn
          // go forward
          while(digitalRead(left_sens) == HIGH && digitalRead(right_sens) == HIGH){
            moveForward();
          }
          fullStop();

          // align on the forward line
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

          // left and right flip
          temp = info->leftState;
          info->leftState = info->rightState;
          info->rightState = temp;
          
          //decisionMade = 1;

          // pointer to previous state
          currState = currState - 1;
          info = info - 1;
          
        } else if(info->rightState == 1){
          info->rightState == 0;
  
          // make turn
          // clock spin middle sensor off front black if "+" junction.
          while(digitalRead(middle_sens) == HIGH){
            clockwiseSpin();
          }
          fullStop();

          // clock spin middle to the right black line of the "+" junction
          while(digitalRead(middle_sens) == LOW){
            clockwiseSpin();
          }
          fullStop();
          // may need more to get it on the line

          //

          // right shift
          temp = info->backState;
          info->backState = rightState;
          info->rightState = info->forState;
          info->forState = info-leftState;
          info->leftstate = temp;
          
          
          //decisionMade = 1;

          // pointer to previous state
          info = info - 1;
          
        } else if(info->backState == 1){ // never, usually 1.
          info->backState == 0;
  
          // make turn
          // 180 back ---
          // off front line
          while(digitalRead(middle_sens) == HIGH){
            counterClockSpin();
          }
          fullStop();

          // to left line
          while(digitalRead(middle_sens) == LOW){
            counterClockSpin();
          }
          fullStop();

          // off left line
          while(digitalRead(middle_sens) == HIGH){
            counterClockSpin();
          }
          fullStop();

          // to 180 line
          while(digitalRead(middle_sens) == LOW){
            counterClockSpin();
          }
          fullStop();

          //decisionMade = 1;

          // pointer to previous junction
          currState = currState - 1;
          info = info - 1;
          
        }
        // no more options, so counterClockSpin for operator feedback
      } else if(info->leftState == 0 && info->forState == 0 && info->rightState == 0 && info->backState == 0){
        while(1){
          counterClockSpin();
        }
      }
    //}
*/
    

    //decisionMade = 0;
    /*
    // check if sides white and if middle still black. Not the end so need to back track.
    else if((digitalRead(left_sens) == LOW || digitalRead(right_sens) == LOW) && digitalRead(middle_sens) == HIGH)
    {
      // Reverse until at least one sensor detects black
      while(digitalRead(left_sens) == LOW && digitalRead(right_sens) == LOW)
      {
        moveBackward();
      }
      
      fullStop();
      updateRobotState(robotState,determineRobotState());
      
      // if back to both black
      if(digitalRead(left_sens) == HIGH || digitalRead(right_sens) == HIGH)
      {
        // must pick a direction, chance of running off the course due to dead ends.
        // At T junction pivot. This logically doesn't work at "+" junction
        // example pivot left
        if(robotState.currentState == LEFT) {
          while(leftHigh() || rightLow()){
            counterClockSpin(); 
          }
        }
        else if(robotState.currentState == RIGHT) {
          while(rightHigh() || leftLow()){
            clockwiseSpin();
          }
        }
  
        
        // Then return 0 and continue normal operation
        return 0;
      }
      else // only one black so can continue normal operation
      {
        // Then return 0, not end
        return 0; 
      }
    }
    else
    {
      return 0;
    }
  }
}*/

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

