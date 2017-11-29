#ifndef STATEMACHINE_CPP
#define STATEMACHINE_CPP

#include "../assets/StateMachine.h"
#include "../assets/kinematic.h"

StateMachine* StudentStateMachine(	Kinematic &character,
							Kinematic &target, 
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
	behaviors["wander"] = new Wander(character,8,20,5,2,0,4,2,30,10);

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

	// wander -> a*
	//la transicion tiene una accion que es calcular el camino
	Action *aStartEntryAct= new ActPath(graph,*path,target,character);
	Transition iniToAStart = {stAStart, new ConIniToA(target), aStartEntryAct};
	stWander->addTransition(iniToAStart);

	//  a* -> a*
	//cuando el path es 0 (llego al final), vuelve a calcular un path
	Transition aStartToIni = {stAStart,new ConPathZero(character,*path), aStartEntryAct};
	stAStart->addTransition(aStartToIni);

	//  a* -> nothing
	Action *actNothing = new ActNothing(character);
	State *stNothing = new State(actNothing);
	Transition aStartToNothing = {stNothing, new ConNextTo(character,target)};
	stAStart->addTransition(aStartToNothing);

	// a* -> wander , nothing -> wander 
	// marlene entra a la coordinacion
	Transition outCoordToInCoord = {stWander, new Con_MarleneInCoord(target)};
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
		Transition iniToHello = {stText, new ConNextTo(character,**target)};
		stIni->addTransition(iniToHello);

		//  hello -> ini
		Transition helloToIni = {stIni,new ConFarFrom(character,**target)};
		stText->addTransition(helloToIni);

		stateMachine->addState(stText);
	}	

	return stateMachine;
}
#endif