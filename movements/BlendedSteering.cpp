#ifndef BLENDED_CPP
#define BLENDED_CPP

#include "Behaviors.cpp"
#include "BlendedSteering.h"

#include <map>

void followTarget(  std::map<string,Behavior*> behaviors,
                    BlendedSteering &blended ){

    if(behaviors.count("obstacle") > 0 ){
        blended.addBehavior(new BehaviorAndWeight(behaviors["obstacle"],0.8));
    }
    if(behaviors.count("separation") > 0 ){
        blended.addBehavior(new BehaviorAndWeight(behaviors["separation"],0.3));
    }
    if(behaviors.count("arrive") > 0 ){
        blended.addBehavior(new BehaviorAndWeight(behaviors["arrive"],0.1));
    }
    if(behaviors.count("lwyg") > 0 ){
        blended.addBehavior(new BehaviorAndWeight(behaviors["lwyg"],3));
    }
}

void flocking(  std::map<string,Behavior*> behaviors,
                BlendedSteering &blended ){

    if(behaviors.count("separation") > 0 ){
        blended.addBehavior(new BehaviorAndWeight(behaviors["separation"],1));
    }
    if(behaviors.count("lwyg") > 0 ){
        blended.addBehavior(new BehaviorAndWeight(behaviors["lwyg"],1));
    }
    if(behaviors.count("velocityMatch") > 0 ){
        blended.addBehavior(new BehaviorAndWeight(behaviors["velocityMatch"],1));
    }
}

void followPathWithObstacle(  
                    std::map<string,Behavior*> behaviors,
                    BlendedSteering &blended ){

    if(behaviors.count("obstacle") > 0 ){
        blended.addBehavior(new BehaviorAndWeight(behaviors["obstacle"],0.3));
    }
    if(behaviors.count("followPath") > 0 ){
        blended.addBehavior(new BehaviorAndWeight(behaviors["followPath"],0.7));
    }
}

#endif