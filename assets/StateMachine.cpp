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

	/*********************** wander_s STATE ***********************/
	//character,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedWander = new BlendedSteering(character,10,30,8, *new list<BehaviorAndWeight*>());
	wanderWithObs(behaviors,*blendedWander);

	Action *wanderAct = new ActBlended(blendedWander);
	Action *wanderActEntry = new ActBlended(blendedWander);
	State *wander_s = new State(wanderAct,wanderActEntry);

	/*********************** A* STATE ***********************/
	//novich,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedPath = new BlendedSteering(character,10,30,8, *new list<BehaviorAndWeight*>());
    followPathWithObstacle(behaviors, *blendedPath);

	Action *alert_Act = new ActBlended(blendedPath);
	Action *alert_EntryAct= new ActPath(graph,*path,target,character);
	State *alert_s = new State(alert_Act,alert_EntryAct);

	/********************** wander_s -> A* **********************/
	Transition w_To_a = {alert_s, new ConIniToA(target)};
	wander_s->addTransition(w_To_a);

	/**********************  A* -> wander_s **********************/
	Transition alert_s_To_wander_s = {wander_s,new ConAtoIni(target)};
	alert_s->addTransition(alert_s_To_wander_s);

	StateMachine *stateMachine = new StateMachine(wander_s);
	stateMachine->addState(alert_s);

	return stateMachine;
}

#endif