#include "headers/lightbase.hpp"


// Constructor
LightBase::LightBase() {

}

// Destructor
LightBase::~LightBase() {

}

bool LightBase::ComputeIllumination(const qbVector<double>& intPoint, const qbVector<double>& localNormal, const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase>& currentObject, qbVector<double>& colour, double& intensity) {
	return false;
}
