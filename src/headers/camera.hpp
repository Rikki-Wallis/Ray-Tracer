#ifndef CAMERA_H
#define CAMERA_H

#include "../qbLinAlg/qbVector.h"
#include "ray.hpp"

class Camera {
public:
	// Constructor
	Camera();

	// Set camera parameters
	void SetPosition(const qbVector<double>& newPosition);
	void SetLookAt(const qbVector<double>& newLookAt);
	void SetUp(const qbVector<double>& upVector);
	void SetLength(double newLength);
	void SetHorizontalSize(double newSize);
	void setAspect(double newAspect);

	// Return camera parameters
	qbVector<double> GetPosition();
	qbVector<double> GetLookAt();
	qbVector<double> GetUp();
	qbVector<double> GetU();
	qbVector<double> GetV();
	qbVector<double> GetScreenCenter();
	double GetLength();
	double GetHorizontalSize();
	double GetAspect();

	// Generate ray
	bool GenerateRay(float proScreenX, float proScreenY, Ray &cameraRay);

	// Update camera geometry
	void UpdateCameraGeometry();

private:
	qbVector<double> m_cameraPosition{ 3 };
	qbVector<double> m_cameraLookAt{ 3 };
	qbVector<double> m_cameraUp{ 3 };
	double m_cameraLength;
	double m_cameraHorizontalSize;
	double m_cameraAspectRatio;

	qbVector<double> m_allignmentVector{ 3 };
	qbVector<double> m_projectionScreenU{ 3 };
	qbVector<double> m_projectionScreenV{ 3 };
	qbVector<double> m_projectionScreenCenter{ 3 };
};


#endif
