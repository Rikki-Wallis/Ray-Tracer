#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightbase.hpp"

class PointLight : public LightBase 
{
public:
	// Constructor
	PointLight();

	// Destructor
	virtual ~PointLight() override;

	// Compute illumination
	virtual bool ComputeIllumination(const qbVector<double>& intPoint, const qbVector<double>& localNormal, const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase>& currentObject, qbVector<double>& colour, double& intensity);

};







#endif
