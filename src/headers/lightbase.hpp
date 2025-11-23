#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>
#include "../../qbLinAlg/qbVector.h"
#include "ray.hpp"
#include "objectbase.hpp"

class LightBase {
public:
	// constructor
	LightBase();
	
	// Deconstructor
	virtual ~LightBase();

	// Compute illumination contribution
	virtual bool ComputeIllumination(const qbVector<double>& intPoint, const qbVector<double>& localNormal, const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase> &currentObject, qbVector<double>& colour, double& intensity);

public:
	// Attributes
	qbVector<double> m_colour{ 3 };
	qbVector<double> m_location{ 3 };
	double m_intensity;
};


#endif
