/*	States to help Robot Robot control
*/

#ifndef ROBOT_STATES
	#define ROBOT_STATES

	//Some sample states
	enum State {
		STOP,
		LEFT,
		RIGHT,
		T_JUNCTION,
		CROSS_JUNCTION
	};

 struct RobotState {
  enum State previousState;
  enum State currentState;
 };

#endif
