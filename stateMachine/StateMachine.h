/* 
    Andrea Centeno
    sep-dic 2017
*/
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

bool stopGame = false;
bool win = false;

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
	std::list<int> &nodes;

	ActPath(Graph &g,Bezier &p,Kinematic &t,Kinematic &c,std::list<int> &n) 
		: Action(), graph(g), path(p), target(t), character(c), nodes(n) {}

	void execute(){
		nodes.clear();
		path.points.clear();

		std::list<glm::vec3> pathAux1;
		std::list<glm::vec3> pathAux2;

		std::list<int> nodesAux;

		pathAux1 = pathfindAStar(graph, character.position, target.position,nodes);

		if( pathAux1.size() > 10 ){
		    pathAux2.splice( pathAux2.begin(), 
		                 pathAux1, 
		                 pathAux1.begin(), 
		                 std::next( pathAux1.begin(), 10 ) );
		    /*
		    nodes.splice( nodes.begin(), 
		                 nodesAux, 
		                 nodesAux.begin(), 
		                 std::next( nodesAux.begin(), 10 ) );
			*/
	        path = {pathAux2};
		}
		else{
			path = {pathAux1};
		}
        
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

class ActPathWeight: public Action{
public:
	Graph &graph;
	std::list<int> &nodes;
	int cost = 1;

	ActPathWeight(Graph &g,std::list<int> &p, float c) 
		: Action(), graph(g), nodes(p), cost(c) {}

	void execute(){
		graph.changeWeight(nodes, cost);
	}
};

/*
detiene el juego
stopGame y win son variables globales
*/
class ActStopGame: public Action{
public:
	ActStopGame() : Action() {}

	void execute(){ 
		stopGame = true;
		win = false;
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

class ConPathZero: public Condition{
	Kinematic &character;
	Bezier &path;
public:
	ConPathZero(Kinematic &t, Bezier &p) : Condition(), character(t), path(p){}
	
	bool test(){
		if( path.size < 1 ) return true; 
		return false;
	}
};

class ConCloseTo: public Condition{
	Kinematic &character;
	Kinematic &target;
	float dist;
public:
	ConCloseTo(Kinematic &t,Kinematic &c, float d = 1.5) 
		: Condition(), character(c), target(t), dist(d){}
	
	bool test(){
		if( glm::distance(character.position,target.position) <= dist ) return true; 
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

class ConOutCoord: public Condition{
	Kinematic &target;
public:
	ConOutCoord(Kinematic &t) : Condition(), target(t){}

	bool test(){
		if( target.position.z >= 8 || target.position.x >= 13) return false;
		return true;
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