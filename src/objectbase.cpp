#include "headers/objectbase.hpp"
#include <math.h>

#define EPSILON 1e-21f;

// Constructor
ObjectBase::ObjectBase() {

}

// Destructor
ObjectBase::~ObjectBase() {

}

bool ObjectBase::TestIntersections(const Ray& castRay, qbVector<double>& intPoint, qbVector<double>& localNormal, qbVector<double>& localColour) {
	return false;
}

void ObjectBase::SetTransformMatrix(const GTform& transformMatrix) {
	m_transformMatrix = transformMatrix;
}

bool ObjectBase::CloseEnough(const double f1, const double f2) {
	return fabs(f1 - f2) < EPSILON;
}