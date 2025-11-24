#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "../../qbLinAlg/qbVector.h"
#include "ray.hpp"
#include "gtfm.hpp"

class ObjectBase 
{
public:
	// Constructor
	ObjectBase();

	// Destructor
	virtual ~ObjectBase();

	// Test for intersections
	virtual bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double>& localColour);

	// Set the transform matrix
	void SetTransformMatrix(const GTform& transformMatrix);

	// Two floating points are close to being equal
	bool CloseEnough(const double f1, const double f2);

// Attributes
public:
	qbVector<double> m_baseColour{ 3 };
	GTform m_transformMatrix;
};

#endif