#include "headers/pointlight.hpp"

// Constructor
PointLight::PointLight() {
	m_colour = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };
	m_intensity = 1.0;
}

// Destructor
PointLight::~PointLight() {

}

bool PointLight::ComputeIllumination(const qbVector<double>& intPoint, const qbVector<double>& localNormal,
    const std::vector<std::shared_ptr<ObjectBase>>& objectList,
    const std::shared_ptr<ObjectBase>& currentObject,
    qbVector<double>& colour, double& intensity)
{
    // Construct a vector pointing from intPoint to the light
    qbVector<double> lightDir = (m_location - intPoint).Normalized();

    // Compute a starting point
    qbVector<double> startPoint = intPoint;

    // Construct a ray from the poi to the light
    Ray lightRay(startPoint, startPoint + lightDir);

    // Check intersections with all objects in the scene except current one
    qbVector<double> poi{ 3 };
    qbVector<double> poiNormal{ 3 };
    qbVector<double> poiColour{ 3 };
    bool validInt = false;

    for (auto sceneObject : objectList) {
        if (sceneObject != currentObject) {
            validInt = sceneObject->TestIntersections(lightRay, poi, poiNormal, poiColour);

            // If we have an intersection, object is in shadow - break immediately
            if (validInt) {
                break;
            }
        }
    }

    /* Only continue to compute illumination if the light ray did not intersect
       with any objects in the scene. I.e. no objects are casting a shadow
       from this light source */
    if (!validInt) {
        // Compute the angle between the local normal and the light ray
        double angle = acos(qbVector<double>::dot(localNormal, lightDir));

        // If the normal is pointing away from the light, then no illumination
        if (angle > 1.5708) {
            // No illumination
            colour = m_colour;
            intensity = 0.0;
            return false;
        }
        else {
            // We do have illumination
            colour = m_colour;
            intensity = m_intensity * (1.0 - (angle / 1.5708));
            return true;
        }
    }
    else {
        // Shadow
        colour = m_colour;
        intensity = 0.0;
        return false;
    }
}
