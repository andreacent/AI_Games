#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "../movements/Behaviors.cpp"
#include "../movements/BlendedSteering.cpp"
#include "../graph/graph.cpp"
#include "../assets/text.cpp"

#include <GL/freeglut.h>
#include <list>
#include <functional>
#include <iostream>

GLfloat oldTimeSinceStart = 0.0;
GLfloat deltaTime = 0.0;

class State;

/********************** ACTION **********************/
class Action{
	public:
		virtual void execute() = 0;
};

class ActBehavior: public Action{
public:
	Behavior *behavior = NULL;

	ActBehavior(){}
	ActBehavior(Behavior *b) : Action(), behavior(b) {}

	void execute(){
		behavior->update(maxSpeed, deltaTime);
	}
};

class ActBlended: public Action{
public:
	BlendedSteering *blended = NULL;

	ActBlended(){}
	ActBlended(BlendedSteering *b) : Action(), blended(b) {}

	void execute(){ blended->update(maxSpeed, deltaTime); }
};

class ActPath: public Action{
public:
	Graph &graph;
	Bezier &path;
	Kinematic &target;
	Kinematic &character;

	ActPath(Graph &g,Bezier &p,Kinematic &t,Kinematic &c) 
		: Action(), graph(g), path(p), target(t), character(c) {}

	void execute(){
        path = {pathfindAStar(graph, character.position, target.position)};
	}
};

class ActText: public Action{
public:
	int typeText = 0;
	Kinematic &character;

	ActText(int n, Kinematic &c) : Action(), typeText(n), character(c) {}

	void execute(){ 
		glm::vec3 newPos = {character.position.x-1.2,0.0,character.position.z+2.4};
		drawText(typeText,newPos); 
	}
};

class ActNothing: public Action{
public:
	Kinematic &character;

	ActNothing(Kinematic &c) : Action(), character(c) {}

	void execute(){ 
		character.velocity = {0.0,0.0,0.0}; 
		character.orientation =0.0;
	}
};


class ActPathPos: public Action{
public:
	Graph &graph;
	Bezier &path;
	vec3 &positionT;
	vec3 &positionC;

	ActPathPos(Graph &g,Bezier &p,vec3 &t,vec3 &c) 
		: Action(), graph(g), path(p), positionT(t), positionC(c) {}

	void execute(){
        path = {pathfindAStar(graph, positionC, positionT)};
	}
};

/********************** CONDITION **********************/
class Condition{
public:
	virtual bool test() = 0;
};

class ConIniToA: public Condition{
	Kinematic &target;
public:
	ConIniToA(Kinematic &t) : Condition(), target(t){}

	bool test(){
		if( target.position.z < 8 && target.position.x < 13) return false;
		return true;
	}
};

class ConAtoIni: public Condition{
	Kinematic &character;
	Bezier &path;
public:
	ConAtoIni(Kinematic &t, Bezier &p) : Condition(), character(t), path(p){}
	
	bool test(){
		if( path.size < 1 ) return true; 
		return false;
	}
};

class ConNextTo: public Condition{
	Kinematic &character;
	Kinematic &target;
public:
	ConNextTo(Kinematic &t,Kinematic &c) : Condition(), character(c), target(t){}
	
	bool test(){
		if( glm::distance(character.position,target.position) <= 2 ) return true; 
		return false;
	}
};

class ConFarFrom: public Condition{
	Kinematic &character;
	Kinematic &target;
public:
	ConFarFrom(Kinematic &t,Kinematic &c) : Condition(), character(c), target(t){}
	
	bool test(){
		if( glm::distance(character.position,target.position) > 2 ) return true; 
		return false;
	}
};

/********************** CONDITION SM_1 **********************/

/********************** Marlene out of Coord **********************/
	class Con_MarleneOutCoord: public Condition{
		Kinematic &target;
	public:
		Con_MarleneOutCoord(Kinematic &t) : Condition(), target(t){}

		bool test(){
			if( target.position.z >= 7 || target.position.x >= 13){
			 	return false;
			 }
			return true;
		}
	};

/********************** Marlene in Coord **********************/
	class Con_MarleneInCoord: public Condition{
		Kinematic &target;
	public:
		Con_MarleneInCoord(Kinematic &t) : Condition(), target(t){}

		bool test(){
			if( target.position.z < 7 && target.position.x < 13){
			 	return true;
			 }
			return false;
		}
	};

/********************** Marlene out of Coord **********************/
	class Con_XinY: public Condition{
		vec3 &zone;
		Kinematic &target;
		float perimeter;
	public:
		Con_XinY(vec3 &z,Kinematic &t,float p) : Condition(), zone(z), target(t), perimeter(p){}

		bool test(){
			bool ZinPerimeter = target.position.z < zone.z+perimeter && target.position.z >= zone.z-perimeter;
			bool XinPerimeter = target.position.x < zone.x+perimeter && target.position.x >= zone.x-perimeter;
			if( ZinPerimeter && XinPerimeter){
			 	return true;
			 }
			//cout << ZinPerimeter << ',' << XinPerimeter << endl;
			return false;
		}
	};

/********************** Character Stop **********************/
	class Con_Stop: public Condition{
		Kinematic &character;
	public:
		Con_Stop(Kinematic &c) : Condition(),character(c){}

		bool test(){
			if( glm::length(character.velocity) == 0.0){
			 	return true;
			 }
			//cout << ZinPerimeter << ',' << XinPerimeter << endl;
			return false;
		}
};

/********************** TRANSITION **********************/
class Transition{
public:
	State *targetState;
	Action *action;
	Condition *condition;

	Transition(State *ts, Condition *c, Action *a=NULL) : targetState(ts), action(a), condition(c) {}

	bool isTriggered(){ return condition->test(); }
};

/********************** STATE **********************/
class State{
public:
	Action *action;
	Action *entryAction;
	Action *exitAction;
	std::list<Transition> transitions;

	State(Action *a, Action *ena=NULL, Action *exa=NULL) : action(a), entryAction(ena), exitAction(exa){}

	void addTransition(Transition transition){ transitions.push_back(transition); }
};

/********************** STATE MACHINE **********************/
class StateMachine{
protected:
	// Holds a list of states for the machine
	std::list<State*> states;

	// Holds the initial state
	State *initialState;

	// Holds the current state
	State *currentState;

public:
	StateMachine(std::list<State*> s, State *is) : states(s), initialState(is), currentState(is){}

	StateMachine(State *is) : initialState(is), currentState(is){ states.push_back(is); }

	// Checks and applies transitions, returning a list of actions.
	std::list<Action*> update(){
		std::list<Action*> actions;

		// Check through each transition and store the first
		// one that triggers. 
		for (Transition triggeredTransition : currentState->transitions){  
			if (triggeredTransition.isTriggered()){
				// Add the exit action of the old state, the
				// transition action and the entry for the new state.
				if(currentState->exitAction) actions.push_back(currentState->exitAction);
				if(triggeredTransition.action) actions.push_back(triggeredTransition.action);
				if(triggeredTransition.targetState->entryAction) actions.push_back(triggeredTransition.targetState->entryAction);

				// Complete the transition and return the action list
				currentState = triggeredTransition.targetState;
				return actions;
			}
		}

		actions.push_back(currentState->action);
		return actions;
	}

	void addState(State* state){ states.push_back(state); }

	void check(){
		std::list<Action*> actions = update();
		for (list<Action*>::iterator it=actions.begin(); it != actions.end(); ++it) (*it)->execute();
	}
};

#endif