/* 
    Sergio Teran
*/
#ifndef STATEMACHINE_S_CPP
#define STATEMACHINE_S_CPP

#include "../assets/StateMachine.h"
#include "../assets/kinematic.h"

class ActPathPos: public Action{
public:
	Graph &graph;
	Bezier &path;
	vec3 &positionT;
	vec3 &positionC;

	ActPathPos(Graph &g,Bezier &p,vec3 &t,vec3 &c) 
		: Action(), graph(g), path(p), positionT(t), positionC(c) {}

	void execute(){
        path = {pathfindAStar(graph, positionC, positionT,nodesId)};
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

	//*********************** wander_s STATE ***********************
	//character,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedWander = new BlendedSteering(character,8,30,8, *new list<BehaviorAndWeight*>());
	wanderWithObs(behaviors,*blendedWander);

	Action *wanderAct = new ActBlended(blendedWander);
	State *wander_s = new State(wanderAct);

	//*********************** A* STATE ***********************
	//novich,maxAcceleration,maxRotation,maxSpeed, list<BehaviorAndWeight*>
	BlendedSteering *blendedPath = new BlendedSteering(character,8,30,8, *new list<BehaviorAndWeight*>());
    followPathWithObstacle(behaviors, *blendedPath);

	Action *alert_Act = new ActBlended(blendedPath);
	Action *alert_EntryAct= new ActPathPos(graph,*path,alert.position,character.position);
	State *alert_s = new State(alert_Act,alert_EntryAct);

	//********************** wander_s -> A* **********************
	Transition w_To_a = {alert_s, new Con_XinY(character.position,alert,5.0)};
	wander_s->addTransition(w_To_a);

	//**********************  A* -> wander_s **********************
	Transition alert_s_To_wander_s = {wander_s,new Con_XinY(character.position,alert,10.0)};
	alert_s->addTransition(alert_s_To_wander_s);

	StateMachine *stateMachine = new StateMachine(wander_s);
	stateMachine->addState(alert_s);

	return stateMachine;
}
/*
StateMachine* StudentStateMachineS(	Kinematic &character,
								Kinematic &target, 
								list<Kinematic*> &targets,
								CollisionDetector &collisionDetector,
								Graph &graph ){

	Bezier *path = new Bezier();
	std::map<string,Behavior*> behaviors; 
	
	//(character,maxAcceleration,collisionDetector,avoidDistance,lookahead) 	
	behaviors["obstacle"] = new ObstacleAvoidance(character,10,collisionDetector,4.5,3);	
	//(character,maxAngularAcceleration,maxRotation,slowRadius,targetRadius,
	//wanderOffset,wanderRadius,wanderRate,wanderOrientation,maxAcceleration)
	behaviors["wander"] = new Wander(character,5,30,5,2, 0,4,2,50,8);	
	//(character,target, targetRadius,slowRadius, maxAcceleration,maxSpeed) 
	behaviors["arrive"] = new Arrive(character,target,2,4,maxAcceleration,maxSpeed);
	//(character,targets,threshold,decayCoefficient,maxAcceleration) 
    behaviors["separation"] = new Separation(character,targets,1.6,4,30);

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
	wander_s->addTransition(Transition(stFollowTarget, new ConNextTo(character,target)));
	

	StateMachine *stateMachine = new StateMachine(wander_s);
	//stateMachine->addState(stFollowTarget);

	return stateMachine;
}

*/
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