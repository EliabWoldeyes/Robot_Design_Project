/*	States to help Robot Robot control
*/

#ifndef ROBOT_STATES
	#define ROBOT_STATES

	//Some sample states
	enum State {
    FORWARD,
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

  State determineRobotState();

  void updateRobotState(RobotState curState, State newState);

#endif
