#ifndef STATEMACHINE_CPP
#define STATEMACHINE_CPP

#include "../assets/StateMachine.h"
#include "../assets/kinematic.h"

StateMachine* StudentStateMachine(	Kinematic &character,
								Kinematic &target, Kinematic &alert,
								CollisionDetector &collisionDetector,
								Graph &graph ){

	Bezier *path = new Bezier();
	std::map<string,Behavior*> behaviors; 
	
	//(character,maxAcceleration,collisionDetector,avoidDistance,lookahead) 	
	behaviors["obstacle"] = new ObstacleAvoidance(character,10,collisionDetector,4.5,3);
	
	//character,maxAcceleration
	behaviors["followPath"] =new FollowPath(character,*path,10);
	
	//(character,maxAngularAcceleration,maxRotation,slowRadius,targetRadius,
	//wanderOffset,wanderRadius,wanderRate,wanderOrientation,maxAcceleration)
	behaviors["wander"] = new Wander(character,5,30,5,2, 0,4,2,50,8);

	/*********************** wander_s STATE ***********************/
	//character,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedWander = new BlendedSteering(character,8,30,8, *new list<BehaviorAndWeight*>());
	wanderWithObs(behaviors,*blendedWander);

	Action *wanderAct = new ActBlended(blendedWander);
	Action *wanderActEntry = new ActBlended(blendedWander);
	State *wander_s = new State(wanderAct,wanderActEntry);

	/*********************** A* STATE ***********************/
	//novich,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedPath = new BlendedSteering(character,8,30,8, *new list<BehaviorAndWeight*>());
    followPathWithObstacle(behaviors, *blendedPath);

	Action *alert_Act = new ActBlended(blendedPath);
	Action *alert_EntryAct= new ActPath(graph,*path,alert.position,character.position);
	State *alert_s = new State(alert_Act,alert_EntryAct);

	/********************** wander_s -> A* **********************/
	Transition w_To_a = {alert_s, new Con_XinY(character.position,alert,5.0)};
	wander_s->addTransition(w_To_a);

	/**********************  A* -> wander_s **********************/
	Transition alert_s_To_wander_s = {wander_s,new Con_XinY(character.position,alert,10.0)};
	alert_s->addTransition(alert_s_To_wander_s);

	StateMachine *stateMachine = new StateMachine(wander_s);
	stateMachine->addState(alert_s);

	return stateMachine;
}

StateMachine* AlertStateMachine(Kinematic &character,
								Kinematic &target,Kinematic &student, 
								CollisionDetector &collisionDetector,
								Graph &graph ){

	Bezier *path = new Bezier();
	std::map<string,Behavior*> behaviors; 
	
	//(character,maxAcceleration,collisionDetector,avoidDistance,lookahead) 	
	behaviors["obstacle"] = new ObstacleAvoidance(character,10,collisionDetector,4.5,3);
	//character,maxAcceleration
	behaviors["followPath"] =new FollowPath(character,*path,10);
	//(character,maxAngularAcceleration,maxRotation,slowRadius,targetRadius,
	//wanderOffset,wanderRadius,wanderRate,wanderOrientation,maxAcceleration)
	behaviors["wander"] = new Wander(character,10,30,5,2, 0,4,2,50,8);

	/*********************** wander_s STATE ***********************/
	//character,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedWander = new BlendedSteering(character,8,30,8, *new list<BehaviorAndWeight*>());
	wanderWithObs(behaviors,*blendedWander);

	Action *wanderAct = new ActBlended(blendedWander);
	Action *wanderActEntry = new ActBlended(blendedWander);
	State *wander_s = new State(wanderAct,wanderActEntry);

	/*********************** alerts_s STATE ***********************/
	//novich,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedPath = new BlendedSteering(character,8,30,8, *new list<BehaviorAndWeight*>());
    followPathWithObstacle(behaviors, *blendedPath);

	Action *alert_Act = new ActBlended(blendedPath);
	Action *alert_EntryAct= new ActPath(graph,*path,student.position,character.position);
	State *alert_s = new State(alert_Act,alert_EntryAct);

	/*********************** pursue_s STATE ***********************/
	Action *pursue_Act = new ActBlended(blendedPath);
	//Action *pursue_Act= new ActPath(graph,*path,target.position,character.position);
	Action *pursue_EntryAct= new ActPath(graph,*path,target.position,character.position);
	State *pursue_s = new State(pursue_Act,pursue_EntryAct);

	/*********************** back_s STATE ***********************/
	//Action *back_Act = new ActBlended(blendedPath);
	vec3 origin = {10,0,8};
	Action *back_Act= new ActPath(graph,*path,origin,character.position);
	Action *back_EntryAct= new ActPath(graph,*path,origin,character.position);
	State *back_s = new State(back_Act,back_EntryAct);


	/********************** wander_s -> alert_s **********************/
	Transition w_To_a = {alert_s, new Con_MarleneOutCoord(target)};
	wander_s->addTransition(w_To_a);

	/********************** alert_s -> pursue_s **********************/
	Transition a_To_p = {pursue_s, new Con_XinY(character.position,student,5.0)};
	alert_s->addTransition(a_To_p);

	/********************** pursue_s-> back_s **********************/
	Transition p_To_b = {back_s, new Con_XinY(target.position,student,1.0)};
	pursue_s->addTransition(p_To_b);

	/********************** alert_s-> back_s **********************/
	//Transition a_To_b = {back_s, new Con_MarleneInCoord(target)};
	//alert_s->addTransition(a_To_b);

	/**********************  alert_s -> wander_s **********************/
	Transition a_To_w = {wander_s,new Con_MarleneInCoord(target)};
	alert_s->addTransition(a_To_w);

	StateMachine *stateMachine = new StateMachine(wander_s);
	stateMachine->addState(alert_s);
	stateMachine->addState(pursue_s);
	stateMachine->addState(back_s);

	return stateMachine;
}

#endif