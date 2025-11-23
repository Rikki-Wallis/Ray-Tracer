#include "headers/pointlight.hpp"

// Constructor
PointLight::PointLight() {
	m_colour = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };
	m_intensity = 1.0;
}

// Destructor
PointLight::~PointLight() {

}

bool PointLight::ComputeIllumination(const qbVector<double>& intPoint, const qbVector<double>& localNormal, const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase>& currentObject, qbVector<double>& colour, double& intensity) {
	
	// Construct a vector pointing for intPoint to the light
	qbVector<double> lightDir = (m_location - intPoint).Normalized();

	// Compute a starting point
	qbVector<double> startPoint = intPoint;

	// Compute the angle between the local normal and the light ray
	double angle = acos(qbVector<double>::dot(localNormal, lightDir));

	// If normal is pointing away from light, then we have no illumination
	if (angle > 1.5708) {
		colour = m_colour;
		intensity = 0.0;
		return false;
	}

	colour = m_colour;
	intensity = m_intensity * (1.0 - (angle / 1.5708));
	return true;
}
