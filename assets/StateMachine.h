#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <list>

class Action{};

class Transition(){
public:
	State targetState;
	Action action;

	isTriggered();
}

class State{
public:
	Action action;
	Action entryAction;
	Action exitAction;
	std::list<Transition> transitions;
};

class StateMachine{
protected:

	// Holds a list of states for the machine
	std::list<State> states;

	// Holds the initial state
	State initialState;

	// Holds the current state
	State currentState;

public:
	//maxRotation, slowRadius, targetRadius to radians
	StateMachine(std::list<State> s, State is) : states(s), initialState(is), currentState(is){}

	// Checks and applies transitions, returning a list of actions.
	std::list<Action> update(){
		std::list<Action> actions;
		// Assume no transition is triggered
		Transition triggeredTransition;
		State targetState;

		// Check through each transition and store the first
		// one that triggers.
		for (std::list<Transition>::iterator iter = currentState.transitions.begin(); iter != currentState.transitions.end(); ++iter){  
			if ((*iter)->isTriggered()){
				triggeredTransition = (*iter);

				// Find the target state
				targetState = triggeredTransition.targetState;

				// Add the exit action of the old state, the
				// transition action and the entry for the new state.
				actions.push_back(currentState.exitAction;
				actions.push_back(triggeredTransition.action;
				actions.push_back(targetState.entryAction;

				// Complete the transition and return the action list
				currentState = targetState;
				return actions;
			}
		}

		actions.push_back(currentState.action);
		return actions;
	}
};

#endif