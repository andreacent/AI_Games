#include "Behavior.h"

GLfloat getNewOrientation(GLfloat currentOrientation, vec3 velocity){
	//Make sure we have a velocity
	if (glm::length(velocity) > 0){
		//Calculate orientation using an arc tangent of
		//the velocity components.
		return atan2(velocity.x, velocity.z);
	}	
	else{ //Otherwise use the current orientation
		return currentOrientation;
	}
};

GLfloat randomBinomial(){ return rand() - rand(); }

vec3 getVectorOrientation(GLfloat orientation){
	vec3 vecOrientation = {-sin(orientation),0.0,cos(orientation)};//{-sin(orientation),cos(orientation)};
	return vecOrientation;
};

GLfloat mapToRange(GLfloat orientation){
	if (orientation > M_PI) orientation -= 2*M_PI;
	else if (orientation < -M_PI) orientation += 2*M_PI;
	return orientation;
}

vec3 rotateVectorZ(vec3 v, GLfloat ang){
	return vec3(v.x * cos(ang) + v.z * sin(ang), v.y, v.z * cos(ang) - v.x * sin(ang) );
}