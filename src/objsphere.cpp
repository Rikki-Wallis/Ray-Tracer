#include "headers/objsphere.hpp"
#include <cmath>

// Constructor
ObjSphere::ObjSphere() {

}

// Deconstructor
ObjSphere::~ObjSphere() {

}

bool ObjSphere::TestIntersections(const Ray& castRay, qbVector<double>& intPoint, qbVector<double>& localNormal, qbVector<double>& localColour) {
	// Compute values a,b,c to sub into quadratic equation
	qbVector<double> vhat = castRay.m_lab;
	vhat.Normalize();
	
	/* a is equal to the squared magnitude of the direction
	of the cast ray. As this will be a unit vector, we can
	conclude that the value of a will always be 1
	*/

	// Calculate b
	double b = 2.0 * qbVector<double>::dot(castRay.m_point1, vhat);

	// Calculate c
	double c = qbVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

	// Test if we have an intersection
	double intTest = (b * b) - 4.0 * c;

	if (intTest > 0.0) {
		
		double numSQRT = sqrtf(intTest);
		double t1 = (-b + numSQRT) / 2.0;
		double t2 = (-b - numSQRT) / 2.0;

		/* If either t1 or t2 are negative, then atleast part of the
		object is behind the camera and so we will ignor it*/
		if ((t1 < 0.0) || (t2 < 0.0)) {
			return false;
		}

		// Determine which point of intersection was closest to the camera
		if (t1 < t2) {
			intPoint = castRay.m_point1 + (vhat * t1);
		}
		else {
			intPoint = castRay.m_point1 + (vhat * t2);
		}

		// Compute the local normal
		localNormal = intPoint;
		localNormal.Normalize();

		return true;
	}

	return false;
}