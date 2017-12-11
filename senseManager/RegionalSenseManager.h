/* 
    Andrea Centeno
    sep-dic 2017
*/
#ifndef SENSE_H
#define SENSE_H

#include <GL/freeglut.h>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <list>
#include <queue>
#include <vector>

class Signal;
class Sensor;

class Modality{
	public:
	float maximumRange;
	float attenuation;
	float inverseTransmissionSpeed;

	virtual bool extraChecks(Signal signal, Sensor sensor) = 0;

};

class SightModality: public Modality{
	public:
	bool extraChecks(Signal signal, Sensor sensor);
};

class Signal{
	public:
	float strength;
	glm::vec3 position;
	Modality *modality;
};

class Sensor{
	public:
	glm::vec3 position;
	float orientation;
	float threshold;

	/*
	where detectsModality returns true if the sensor can detect 
	the given modality; the modality is a modality instance.
	*/
	bool detectsModality(Modality *modality){
		return true;
	}

	/*
	The notify method is just the same as we saw in regular 
	event management: it notifies the sensor of the signal.
	*/
	void notify(Signal signal){}
};

bool SightModality::extraChecks(Signal signal, Sensor sensor){
	/*
	where checkSightCone and checkLineOfSight carry out  
	the individual tests; both return true if they pass
	*/
	//if (!checkSightCone(signal.position, sensor.position, sensor.orientation)) continue;
	//if (!checkLineOfSight(signal.position, sensor.position)) continue;
	return true;
}

class RegionalSenseManager{
	protected:

	// Holds a record in the notification queue, ready to notify
	// the sensor at the correct time.
	struct Notification{
		float time;
		Sensor sensor;
		Signal signal;
	};

	class CompareNotifications {
    public:
        bool operator()(Notification &n1, Notification &n2) {
            if (n1.time > n2.time ) return true;
            return false;
        }
    };

	// Holds the list of sensors
	std::list<Sensor> sensors;

	// Holds a queue of notifications waiting to be honored	
	std::priority_queue<Notification, std::vector<Notification>, CompareNotifications> notificationQueue;
	
	public:

	// Introduces a signal into the game. This also calculates
	// the notifications that this signal will be needed
	void addSignal(Signal _signal){
		//Aggregation phase
		//validSensors = []

		Sensor sensor;

		for (std::list<Sensor>::iterator it = this->sensors.begin(); it != this->sensors.end(); ++it){
			// Testing phase

			sensor = (*it);

			// Check the modality first 	
			if (!sensor.detectsModality(_signal.modality)) continue;

			// Find the distance of the signal and check range
			float _distance = glm::distance(_signal.position, sensor.position);
			if (_signal.modality->maximumRange < _distance) continue;

			// Find the intensity of the signal and check threshold
			float intensity = _signal.strength * pow(_signal.modality->attenuation, _distance);
			if (intensity < sensor.threshold) continue;

			// Perform additional modality specific checks
			if (!_signal.modality->extraChecks(_signal, sensor)) continue;

			// We’re going to notify the sensor, work out when
			float _time = glutGet(GLUT_ELAPSED_TIME) + _distance * _signal.modality->inverseTransmissionSpeed;

			// Create a notification record and add it to the queue
			Notification notification;
			notification.time = _time;
			notification.sensor = sensor;
			notification.signal = _signal;
			notificationQueue.push(notification);
		}

		// Send signals, in case the current signal is ready to notify
		// immediately.
		sendSignals();

	}

	//Flushes notifications from the queue, up to the current time
	void sendSignals(){
		//Notification Phase

		float currentTime = glutGet(GLUT_ELAPSED_TIME);

		while (!notificationQueue.empty()){
			Notification notification = notificationQueue.top();        	

			//Check if the notification is due
			if( notification.time < currentTime){
				notification.sensor.notify(notification.signal);
				notificationQueue.pop();
			}
			//If we are beyond the current time, then stop
			//(the queue is sorted)
			else break;

		}
	}
};

#endif