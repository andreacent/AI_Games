#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "../movements/Behaviors.cpp"
#include "../assets/kinematic.h"

#include <list>
#include <functional>

class State;

class Action{
	Behavior *behavior = NULL;
};

class Transition{
public:
	State &targetState;
	Action *action;

	std::function<bool (Kinematic character,Kinematic target)> isTriggered;

	Transition(State &ts, Action *a) : targetState(ts), action(a){
		 isTriggered = [](Kinematic character,Kinematic target) { return true; };
	}
};

class State{
public:
	Action *action=NULL;
	Action *entryAction=NULL;
	Action *exitAction=NULL;
	std::list<Transition> transitions;

	State(Action *a) : action(a){}
	State(Action *a, Action *ena, Action *exa) : action(a), entryAction(ena), exitAction(exa){}

	void addTransition(Transition transition){
		transitions.push_back(transition);
	}
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
	StateMachine(std::list<State> s, State is) : states(s), initialState(is), currentState(is){}

	StateMachine(State is) : initialState(is), currentState(is){ states.push_back(is); }

	// Checks and applies transitions, returning a list of actions.
	std::list<Action*> update(){
		std::list<Action*> actions;

		// Check through each transition and store the first
		// one that triggers.
		//for(std::list<Transition> it = currentState.transitions.begin(); it != currentState.transitions.end(); ++it){ 
		for (Transition triggeredTransition : currentState.transitions){  
			if (triggeredTransition.isTriggered){
				// Add the exit action of the old state, the
				// transition action and the entry for the new state.
				actions.push_back(currentState.exitAction);
				actions.push_back(triggeredTransition.action);
				actions.push_back(triggeredTransition.targetState.entryAction);

				// Complete the transition and return the action list
				State currentState = triggeredTransition.targetState;
				return actions;
			}
		}

		actions.push_back(currentState.action);
		return actions;
	}

	void addState(State state){
		states.push_back(state);
	}
};

#endif