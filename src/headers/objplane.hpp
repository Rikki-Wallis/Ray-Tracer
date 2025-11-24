#ifndef OBJPLANE_H
#define OBJPLANE_H

#include "objectbase.hpp"
#include "gtfm.hpp"

class ObjPlane : public ObjectBase {
public:
	// Constructor
	ObjPlane();

	// Destructor
	virtual ~ObjPlane() override;

	// Test for intersections
	virtual bool TestIntersections(const Ray& castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColour) override;
};


#endif
