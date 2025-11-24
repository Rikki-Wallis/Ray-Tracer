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

	// Construct objects
	m_objectList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
	m_objectList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
	m_objectList.push_back(std::make_shared<ObjSphere>(ObjSphere()));

	// Modify the spheres
	GTform testMatrix1, testMatrix2, testMatrix3;
	testMatrix1.SetTransform(qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}}, qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, qbVector<double>{std::vector<double>{0.5, 0.5, 0.75}});
	testMatrix2.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});
	testMatrix3.SetTransform(qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}}, qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});
	m_objectList.at(0)->SetTransformMatrix(testMatrix1);
	m_objectList.at(1)->SetTransformMatrix(testMatrix2);
	m_objectList.at(2)->SetTransformMatrix(testMatrix3);

	m_objectList.at(0)->m_baseColour = qbVector<double>{ std::vector<double>{64.0, 128.0, 200.0} };
	m_objectList.at(1)->m_baseColour = qbVector<double>{ std::vector<double>{255.0, 128.0, 0.0} };
	m_objectList.at(2)->m_baseColour = qbVector<double>{ std::vector<double>{255.0, 200.0, 0.0} };


	// Construct lights
	m_lightList.push_back(std::make_shared<PointLight>(PointLight()));
	m_lightList.at(0) -> m_location = qbVector<double>{ std::vector<double> {5.0, -10.0, -5.0} };
	m_lightList.at(0)-> m_colour = qbVector<double>{ std::vector<double> {255.0, 255.0, 255.0} };
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

			// Test for intersections with all objects in the scene
			for (auto currentObject : m_objectList) {
				bool validInt = currentObject->TestIntersections(cameraRay, intPoint, localNormal, localColour);
				
				// If we have an intersection change pixel to red
				if (validInt) {

					// Compute intensity of light
					double intensity;
					qbVector<double> colour{ 3 };
					bool validIllumination = false;

					for (auto currentLight : m_lightList) {
						validIllumination = currentLight->ComputeIllumination(intPoint, localNormal, m_objectList, currentObject, colour, intensity);
					}

					if (validIllumination) {
						//outputImage.SetPixel(x, y, 255.0 * intensity, 0.0, 0.0);
						outputImage.SetPixel(x, y, localColour.GetElement(0) * intensity, localColour.GetElement(1) * intensity, localColour.GetElement(2) * intensity);
					}
				}
			}
		}
	}

	return true;
}