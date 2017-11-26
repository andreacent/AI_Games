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
	behaviors["obstacle"] = new ObstacleAvoidance(character,16,collisionDetector,4.5,3);
	//character,maxAcceleration
	behaviors["followPath"] =new FollowPath(character,*path,10);
	//(character,maxAngularAcceleration,maxRotation,slowRadius,targetRadius,
	//wanderOffset,wanderRadius,wanderRate,wanderOrientation,maxAcceleration)
	behaviors["wander"] = new Wander(character,10,30,5,2, 0,4,2,50,8);

	/* INI STATE */
	//character,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedWander = new BlendedSteering(character,10,30,8, *new list<BehaviorAndWeight*>());
	wanderWithObs(behaviors,*blendedWander);

	Action *wanderAct = new ActBlended(blendedWander);
	State *ini = new State(wanderAct);

	/* A* STATE */
	//novich,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedPath = new BlendedSteering(character,10,30,8, *new list<BehaviorAndWeight*>());
    followPathWithObstacle(behaviors, *blendedPath);

	Action *aStartAct = new ActBlended(blendedPath);
	Action *aStartEntryAct= new ActPath(graph,*path,target,character);
	State *aStart = new State(aStartAct,aStartEntryAct);

	// ini -> a*
	Transition iniToAStart = {aStart, new ConIniToA(target)};
	ini->addTransition(iniToAStart);

	//  a* -> ini
	Transition aStartToIni = {ini,new ConAtoIni(character)};
	aStart->addTransition(aStartToIni);

	StateMachine *stateMachine = new StateMachine(ini);
	stateMachine->addState(aStart);

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