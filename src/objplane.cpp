#include "headers/objplane.hpp"
#include <cmath>

// Constructor
ObjPlane::ObjPlane() {

}

// Destructor
ObjPlane::~ObjPlane() {

}

// Test Intersections
bool ObjPlane::TestIntersections(const Ray& castRay, qbVector<double>& intPoint, qbVector<double>& localNormal, qbVector<double>& localColour) {
	// Copy the ray and apply the backwards transform
	Ray backRay = m_transformMatrix.Apply(castRay, RT::BCKTFORM);

	// Copy m_lab and normalise
	qbVector<double> k = backRay.m_lab;
	k.Normalize();

	// Check if there is an intersection
	// Cast ray is not parallel to plane
	if (!CloseEnough(k.GetElement(2), 0.0)) 
	{
		// There is an intersection so do stuff
		double t = backRay.m_point1.GetElement(2) / -k.GetElement(2);

		// If t is -, then intPoint must be behind camera and can be ignored
		if (t > 0.0) {
			// Comput values for u and v
			double u = backRay.m_point1.GetElement(0) + (k.GetElement(0) * t);
			double v = backRay.m_point1.GetElement(1) + (k.GetElement(1) * t);

			// If magnitude of both u and v is <= 1then we must be in the plane
			if ((abs(u) < 1.0) && (abs(v) < 1.0)) {

				// Compute point of intersection
				qbVector<double> poi = backRay.m_point1 + t * k;

				// Transform the intersection point back into world coords
				intPoint = m_transformMatrix.Apply(poi, RT::FWDTFORM);

				// Compute local normal
				qbVector<double> localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
				qbVector<double> normalVector{ std::vector<double> {0.0, 0.0, -1.0} };
				qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, RT::FWDTFORM);
				localNormal = m_transformMatrix.Apply(normalVector, RT::FWDTFORM) - globalOrigin;
				localNormal.Normalize();

				// Return the base colour
				localColour = m_baseColour;

				return true;
			}
		}
	}
	return false;
}

