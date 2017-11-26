#ifndef STATEMACHINE_CPP
#define STATEMACHINE_CPP

#include "../assets/StateMachine.h"
#include "../assets/kinematic.h"

StateMachine* StudentStateMachine(	Kinematic &character,
							Kinematic &target, 
							CollisionDetector &collisionDetector,
							Graph &graph ){

	Bezier *path = new Bezier();
	std::map<string,Behavior*> behaviors; 
	
	//(character,maxAcceleration,collisionDetector,avoidDistance,lookahead) 	
	behaviors["obstacle"] = new ObstacleAvoidance(character,16,collisionDetector,4.5,3);
	
	//character,maxAcceleration
	behaviors["followPath"] =new FollowPath(character,*path,10);
	
	//(character,maxAngularAcceleration,maxRotation,slowRadius,targetRadius,
	//wanderOffset,wanderRadius,wanderRate,wanderOrientation,maxAcceleration)
	behaviors["wander"] = new Wander(character,10,30,5,2, 0,4,2,50,8);

	/*********************** INI STATE ***********************/
	//character,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedWander = new BlendedSteering(character,10,30,8, *new list<BehaviorAndWeight*>());
	wanderWithObs(behaviors,*blendedWander);

	Action *wanderAct = new ActBlended(blendedWander);
	State *ini = new State(wanderAct);

	/*********************** A* STATE ***********************/
	//novich,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedPath = new BlendedSteering(character,10,30,8, *new list<BehaviorAndWeight*>());
    followPathWithObstacle(behaviors, *blendedPath);

	Action *aStartAct = new ActBlended(blendedPath);
	Action *aStartEntryAct= new ActPath(graph,*path,target,character);
	State *aStart = new State(aStartAct,aStartEntryAct);

	/********************** ini -> A* **********************/
	Transition in_To_AStart = {aStart, new ConIniToA(target)};
	ini->addTransition(in_To_AStart);

	/**********************  A* -> ini **********************/
	Transition aStart_To_Ini = {ini,new ConAtoIni(character)};
	aStart->addTransition(aStart_To_Ini);

	StateMachine *stateMachine = new StateMachine(ini);
	stateMachine->addState(aStart);

	return stateMachine;
}

#endif