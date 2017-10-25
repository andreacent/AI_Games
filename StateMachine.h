class Transition{
protected:
	action;
	State targetState;

public:
	bool isTriggered(){

	}
};

class State{
protected:
	action;
	entryAction;
	exitAction;
	list<Transition> transitions;
};

class StateMachine{
protected:

	// Holds a list of states for the machine
	list<State> states;

	// Holds the initial state
	State initialState;

	// Holds the current state
	State currentState;

public:
	//maxRotation, slowRadius, targetRadius to radians
	StateMachine(list<State> s, State is) : states(s), initialState(is), currentState(is){}

	// Checks and applies transitions, returning a list of
	// actions.
	void update(){
		// Assume no transition is triggered
		Transition triggeredTransition;

		// Check through each transition and store the first
		// one that triggers.
		for (list<Transition>::iterator iter = currentState.transitions.begin(); iter != currentState.transitions.end(); ++iter){  
			if ((*iter)->isTriggered()){
				triggeredTransition = transition;
				break;
			}
		}

		// Check if we have a transition to fire
		if (triggeredTransition){
			// Find the target state
			targetState = triggeredTransition.getTargetState();

			// Add the exit action of the old state, the
			// transition action and the entry for the new state.
			actions = currentState.getExitAction();
			actions += triggeredTransition.getAction();
			actions += targetState.getEntryAction();

			// Complete the transition and return the action list
			currentState = targetState;
			return actions;
		}		
		else{ // Otherwise just return the current state’s actions
			return currentState.getAction();
		}
	}
};