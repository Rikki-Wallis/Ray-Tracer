#ifndef OBJSPHERE_H
#define OBJSHPERE_H

#include "objectbase.hpp"
#include "gtfm.hpp"

class ObjSphere : public ObjectBase 
{
public:
	// Constructor
	ObjSphere();

	// Destructor
	virtual ~ObjSphere() override;

	// Test intersections
	virtual bool TestIntersections(const Ray& castRay, qbVector<double>& intPoint, qbVector<double>& localNormal, qbVector<double>& localColour) override;

private:
};


#endif
