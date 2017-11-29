#ifndef STATEMACHINE_S_CPP
#define STATEMACHINE_S_CPP

#include "../assets/StateMachine.h"
#include "../assets/kinematic.h"

StateMachine* StudentStateMachineS(	Kinematic &character,
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
	State *wander_s = new State(wanderAct);

	/*********************** A* STATE ***********************/
	//novich,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedPath = new BlendedSteering(character,8,30,8, *new list<BehaviorAndWeight*>());
    followPathWithObstacle(behaviors, *blendedPath);

	Action *alert_Act = new ActBlended(blendedPath);
	Action *alert_EntryAct= new ActPathPos(graph,*path,alert.position,character.position);
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

	Bezier *path = new Bezier(); //camino que se genera del A*
	std::map<string,Behavior*> behaviors; 
	//(character,maxAcceleration,collisionDetector,avoidDistance,lookahead) 	
	behaviors["obstacle"] = new ObstacleAvoidance(character,16,collisionDetector,3,2);
	//character,maxAcceleration
	behaviors["followPath"] =new FollowPath(character,*path,8);
	//(character,maxAngularAcceleration,maxRotation,slowRadius,targetRadius,
	//wanderOffset,wanderRadius,wanderRate,wanderOrientation,maxAcceleration)
	behaviors["wander"] = new Wander(character,10,20,5,2,0,4,2,50,10);

	/* INI STATE */
	//character,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedWander = new BlendedSteering(character,10,30,8, *new list<BehaviorAndWeight*>());
	wanderWithObs(behaviors,*blendedWander);

	Action *wanderAct = new ActBlended(blendedWander);
	State *stWander = new State(wanderAct);

	/* A* STATE */
	//novich,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedPath = new BlendedSteering(character,10,30,8, *new list<BehaviorAndWeight*>());
    followPathWithObstacle(behaviors, *blendedPath);

	Action *aStartAct = new ActBlended(blendedPath);
	State *stAStart = new State(aStartAct);

	// wander -> a* student
	//la transicion tiene una accion que es calcular el camino
	Action *aStartEntryAct= new ActPath(graph,*path,student,character);
	Transition iniToAStart = {stAStart, new ConIniToA(target), aStartEntryAct};
	stWander->addTransition(iniToAStart);

	//  a* student -> a* student
	//cuando el path es 0 (llego al final), vuelve a calcular un path
	Transition aStartToIni = {stAStart,new ConPathZero(character,*path), aStartEntryAct};
	stAStart->addTransition(aStartToIni);

	// a* student -> a* target
	State *stAStartTarget = new State(aStartAct);
	Transition AStartToAStart = {stAStartTarget, new ConNextTo(character,student), new ActPath(graph,*path,target,character)};
	stAStart->addTransition(AStartToAStart);

	// a* student -> wander , a* target -> wander 
	// marlene entra a la coordinacion
	Transition outCoordToInCoord = {stWander, new Con_MarleneInCoord(target)};
	stAStart->addTransition( outCoordToInCoord );
	stAStartTarget->addTransition( outCoordToInCoord );

	StateMachine *stateMachine = new StateMachine(stWander);
	stateMachine->addState(stAStart);
	stateMachine->addState(stAStartTarget);

	return stateMachine;
}

#endif