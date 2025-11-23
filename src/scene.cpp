#include "headers/scene.hpp"

// Constructor
Scene::Scene() {
	// Configure camera
	m_camera.SetPosition(qbVector<double>{std::vector{ 0.0,-10.0,0.0 }});
	m_camera.SetLookAt(qbVector<double>{std::vector{ 0.0,0.0,0.0 }});
	m_camera.SetUp(qbVector<double>{std::vector{ 0.0,0.0,1.0 }});
	m_camera.SetHorizontalSize(0.25);
	m_camera.setAspect(16.0/9.0);
	m_camera.UpdateCameraGeometry();
}

// Perform Rendering
bool Scene::Render(Image& outputImage) {
	// Get dimensions of output image
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();

	// Loop over each pixel in the image
	Ray cameraRay;
	qbVector<double> intPoint(3);
	qbVector<double> localNormal(3);
	qbVector<double> localColour(3);
	double xFactor = 1 / (static_cast<double>(xSize) / 2.0);
	double yFactor = 1 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;

	for (int x = 0; x < xSize; ++x) {
		for (int y = 0; y < ySize; ++y) {
			
			// Normalise x and y coords
			double normX = (static_cast<double>(x) * xFactor) - 1.0;
			double normY = (static_cast<double>(y) * yFactor) - 1.0;

			// Generate ray for this pixel
			m_camera.GenerateRay(normX, normY, cameraRay);

			// Test if intersects
			bool validInt = m_testSphere.TestIntersections(cameraRay, intPoint, localNormal, localColour);

			// If we have an intersection change pixel to red
			if (validInt) {
				// Compute the distance between the camera and the point of intersection
				double dist = (intPoint - cameraRay.m_point1).norm();
				if (dist > maxDist) {
					maxDist = dist;
				}

				if (dist < minDist) {
					minDist = dist;
				}

				outputImage.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
			}
			else {
				outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
			}
		}
	}

	return true;
}