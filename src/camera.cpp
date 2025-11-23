#include "headers/camera.hpp"
#include "headers/ray.hpp"
#include <math.h>

Camera::Camera()
{
	m_cameraPosition = qbVector<double>{ std::vector<double>({0.0, -10.0, 0.0})};
	m_cameraLookAt = qbVector<double>{ std::vector<double>({0.0, 0.0, 0.0})};
	m_cameraUp = qbVector<double>{ std::vector<double>({0.0, 0.0, 1.0})};
	m_cameraLength = 1.0;
	m_cameraHorizontalSize = 1.0;
	m_cameraAspectRatio = 1.0;
}

// Set Camera Parameters
void Camera::SetPosition(const qbVector<double>& newPosition) {
	m_cameraPosition = newPosition;
}

void Camera::SetLookAt(const qbVector<double>& newLookAt) {
	m_cameraLookAt = newLookAt;
}

void Camera::SetUp(const qbVector<double>& upVector) {
	m_cameraUp = upVector;
}

void Camera::SetLength(double newLength) {
	m_cameraLength = newLength;
}

void Camera::SetHorizontalSize(double newSize) {
	m_cameraHorizontalSize = newSize;
}
void Camera::setAspect(double newAspect) {
	m_cameraAspectRatio = newAspect;
}

// Get Camera Parameters
qbVector<double> Camera::GetPosition(){
	return m_cameraPosition;
}

qbVector<double> Camera::GetLookAt()  {
	return m_cameraLookAt;
}

qbVector<double> Camera::GetUp()	  {
	return m_cameraUp;
}

double Camera::GetLength()				  {
	return m_cameraLength;
}

double Camera::GetHorizontalSize()		  {
	return m_cameraHorizontalSize;
}

double Camera::GetAspect()				  {
	return m_cameraAspectRatio;
}

qbVector<double> Camera::GetU() {
	return m_projectionScreenU;
}

qbVector<double> Camera::GetV() {
	return m_projectionScreenV;
}

qbVector<double> Camera::GetScreenCenter() {
	return m_projectionScreenCenter;
}

// Compute Geometry
void Camera::UpdateCameraGeometry() {
	// Compute vector from camera position to look at position
	m_allignmentVector = m_cameraLookAt - m_cameraPosition;
	m_allignmentVector.Normalize();

	// Compute U and V vectors
	m_projectionScreenU = qbVector<double>::cross(m_allignmentVector, m_cameraUp);
	m_projectionScreenU.Normalize();
	m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_allignmentVector);
	m_projectionScreenV.Normalize();

	// Compute the position of the center point of the screen
	m_projectionScreenCenter = m_cameraPosition + (m_cameraLength * m_allignmentVector);

	// Modify the u and V vectors to match the size and aspect ratios
	m_projectionScreenU = m_projectionScreenU * m_cameraHorizontalSize;
	m_projectionScreenV = m_projectionScreenV * (m_cameraHorizontalSize / m_cameraAspectRatio);
}

Ray Camera::GenerateRay(float proScreenX, float proScreenY) {
	// Compute the location of the screen point in world coordinates
	qbVector<double> screenWorldPart1 = m_projectionScreenCenter + (m_projectionScreenU * proScreenX);
	qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);

	// Compute the ray with camera position and screenWorldCoordinate
	return Ray(m_cameraPosition, screenWorldCoordinate);
}