/* 
    Andrea Centeno
    sep-dic 2017
*/
#ifndef STATEMACHINE_CPP
#define STATEMACHINE_CPP

#include "StateMachine.h"
#include "../assets/kinematic.h"

/*
Los personajes persiguen a marlene cuando sale de la oficina.
Se detienen si estan cerca de marlene
*/
StateMachine* StudentStateMachine(	Kinematic &character,
							Kinematic &target, 
							CollisionDetector &collisionDetector,
							list<Kinematic*> &targets,
							Graph &graph ){

	Bezier *path = new Bezier(); //camino que se genera del A*
	std::list<int> *nodes = new list<int>{};

	std::map<string,Behavior*> behaviors; 
	//(character,maxAcceleration,collisionDetector,avoidDistance,lookahead) 	
	behaviors["obstacle"] = new ObstacleAvoidance(character,16,collisionDetector,3,2);
	//character,maxAcceleration
	behaviors["followPath"] =new FollowPath(character,*path,20);
	//(character,maxAngularAcceleration,maxRotation,slowRadius,targetRadius,
	//wanderOffset,wanderRadius,wanderRate,wanderOrientation,maxAcceleration)
	behaviors["wander"] = new Wander(character,8,20,5,2,0,4,2,30,10);
	//(character,targets,threshold,decayCoefficient,maxAcceleration) 
    behaviors["separation"] = new Separation(character,targets,1.5,4,16);

	//accion para disminuir el costo 
	Action *actPathWeightD = new ActPathWeight(graph,*nodes,-10);
	//accion para aumentar el costo
	Action *actPathWeightU = new ActPathWeight(graph,*nodes,10);

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
	State *stAStart = new State(aStartAct,actPathWeightU,actPathWeightD);

	// wander -> a*
	//la transicion tiene una accion que es calcular el camino
	Action *aStartEntryAct= new ActPath(graph,*path,target,character,*nodes);
	Transition iniToAStart = {stAStart, new ConIniToA(target), aStartEntryAct};
	stWander->addTransition(iniToAStart);

	//  a* -> a*
	//cuando el path es 0 (llego al final), vuelve a calcular un path
	Transition aStartToIni = {stAStart,new ConPathZero(character,*path), aStartEntryAct};
	stAStart->addTransition(aStartToIni);

	//  a* -> nothing
	Action *actNothing = new ActNothing(character);
	Action *actStopGame = new ActStopGame();
	State *stNothing = new State(actNothing,actStopGame);
	Transition aStartToNothing = {stNothing, new ConCloseTo(character,target)};
	stAStart->addTransition(aStartToNothing);

	// a* -> wander , nothing -> wander 
	// marlene entra a la coordinacion
	Transition outCoordToInCoord = {stWander, new ConOutCoord(target)};
	stAStart->addTransition( outCoordToInCoord );
	stNothing->addTransition(outCoordToInCoord);

	StateMachine *stateMachine = new StateMachine(stWander);
	stateMachine->addState(stAStart);
	stateMachine->addState(stNothing);

	return stateMachine;
}

/*
character le dice hola a target cuando esta cerca
*/
StateMachine* HelloStateMachine(Kinematic &character, list<Kinematic*> &targets ){

	/* INI STATE */
	Action *nothingAct = new ActNothing(character);
	State *stIni = new State(nothingAct);
	StateMachine *stateMachine = new StateMachine(stIni);

	Action *actText = new ActText(0,character);

	// Loop through each target
	for (list<Kinematic*>::iterator target=targets.begin(); target != targets.end(); ++target){
		/* HELLO STATE */
	    //(character,target, maxAngularAcceleration,maxRotation,slowRadius,targetRadius)
		Action *actFace = new ActBehavior(new Face(character,**target,10,30,5,2));
		State *stText = new State(actText,actFace);

		// ini -> hello
		Transition iniToHello = {stText, new ConCloseTo(character,**target)};
		stIni->addTransition(iniToHello);

		//  hello -> ini
		Transition helloToIni = {stIni,new ConFarFrom(character,**target)};
		stText->addTransition(helloToIni);

		stateMachine->addState(stText);
	}	

	return stateMachine;
}

StateMachine* FollowStateMachine(	Kinematic &character,
								Kinematic &target, 
								list<Kinematic*> &targets,
								CollisionDetector &collisionDetector ){
	
	std::map<string,Behavior*> behaviors; 
	
	//(character,maxAcceleration,collisionDetector,avoidDistance,lookahead) 	
	behaviors["obstacle"] = new ObstacleAvoidance(character,16,collisionDetector,3,2);
	//(character,maxAngularAcceleration,maxRotation,slowRadius,targetRadius,
	//wanderOffset,wanderRadius,wanderRate,wanderOrientation,maxAcceleration)
	behaviors["wander"] = new Wander(character,5,30,5,2, 0,4,2,50,8);	
	//(character,target, targetRadius,slowRadius, maxAcceleration,maxSpeed) 
	behaviors["arrive"] = new Arrive(character,target,2,3,20,6);
	//(character,targets,threshold,decayCoefficient,maxAcceleration) 
    behaviors["separation"] = new Separation(character,targets,1.5,4,16);

	//*********************** wander_s STATE ***********************
	//character,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedWander = new BlendedSteering(character,8,30,8, *new list<BehaviorAndWeight*>());
	wanderWithObs(behaviors,*blendedWander);

	Action *wanderAct = new ActBlended(blendedWander);
	State *wander_s = new State(wanderAct);

	//character sigue al target cuando esta cerca de el
	
	BlendedSteering *blendedFollowT = new BlendedSteering(character,8,30,8, *new list<BehaviorAndWeight*>());
	followTarget( behaviors, *blendedFollowT);
	Action *actFollow = new ActBlended(blendedFollowT);
	State *stFollowTarget = new State(actFollow);
	Transition wanderToFollow = {stFollowTarget, new ConCloseTo(character,target,3)};
	wander_s->addTransition(wanderToFollow);
	

	StateMachine *stateMachine = new StateMachine(wander_s);
	stateMachine->addState(stFollowTarget);

	return stateMachine;
}

#endif