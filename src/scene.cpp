#include "headers/scene.hpp"

// Constructor
Scene::Scene() {
	// Configure camera
	m_camera.SetPosition(qbVector<double>{std::vector{ 0.0,-10.0, -1.0 }});
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

	m_objectList.at(0)->m_baseColour = qbVector<double>{ std::vector<double>{0.25, 0.5, 0.8} };
	m_objectList.at(1)->m_baseColour = qbVector<double>{ std::vector<double>{1.0, 0.5, 0.0} };
	m_objectList.at(2)->m_baseColour = qbVector<double>{ std::vector<double>{1.0, 0.8, 0.0} };

	// Construct test planes
	m_objectList.push_back(std::make_shared<ObjPlane>(ObjPlane()));
	m_objectList.at(3)->m_baseColour = qbVector<double>{ std::vector<double>{0.5, 0.5, 0.5} };
	// Transform for the plane
	GTform planeMatrix;
	planeMatrix.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}}, qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});
	m_objectList.at(3)->SetTransformMatrix(planeMatrix);

	// Construct lights
	m_lightList.push_back(std::make_shared<PointLight>(PointLight()));
	m_lightList.at(0) -> m_location = qbVector<double>{ std::vector<double> {5.0, -10.0, -5.0} };
	m_lightList.at(0)-> m_colour = qbVector<double>{ std::vector<double> {0.0, 0.0, 1.0} };

	m_lightList.push_back(std::make_shared<PointLight>(PointLight()));
	m_lightList.at(1)->m_location = qbVector<double>{ std::vector<double> {-5.0, -10.0, -5.0} };
	m_lightList.at(1)->m_colour = qbVector<double>{ std::vector<double> {1.0, 0.0, 0.0} };

	m_lightList.push_back(std::make_shared<PointLight>(PointLight()));
	m_lightList.at(2)->m_location = qbVector<double>{ std::vector<double> {0.0, -10.0, -5.0} };
	m_lightList.at(2)->m_colour = qbVector<double>{ std::vector<double> {0.0, 1.0, 0.0} };
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
			std::shared_ptr<ObjectBase> closestObject;
			qbVector<double> closestIntPoint{ 3 };
			qbVector<double> closestLocalNormal{ 3 };
			qbVector<double> closestLocalColour{ 3 };
			double minDist = 1e6;
			bool intersectionFound = false;

			for (auto currentObject : m_objectList) {
				bool validInt = currentObject->TestIntersections(cameraRay, intPoint, localNormal, localColour);
				
				// If we have an intersection
				if (validInt) {
					// Set the flag to indicate that we found an intersection
					intersectionFound = true;

					// Compute the distance between the camera and the poi
					double dist = (intPoint - cameraRay.m_point1).norm();

					// If this object is closer to camera than any other we have seen, store reference to it
					if (dist < minDist) {
						minDist = dist;
						closestObject = currentObject;
						closestIntPoint = intPoint;
						closestLocalNormal = localNormal;
						closestLocalColour = localColour;
					}
				}
			}

			// Compute the illumination for the closest object
			if (intersectionFound) {
				double intensity;
				qbVector<double> colour{ 3 };
				double red = 0.0;
				double green = 0.0;
				double blue = 0.0;
				bool validIllum = false;
				bool illumFound = false;
				for (auto currentLight : m_lightList) {
					validIllum = currentLight->ComputeIllumination(closestIntPoint, closestLocalNormal, m_objectList, closestObject, colour, intensity);

					if (validIllum) {
						illumFound = true;
						red += colour.GetElement(0) * intensity;
						green += colour.GetElement(1) * intensity;
						blue += colour.GetElement(2) * intensity;
					}
				}

				if (illumFound) {
					red *= closestLocalColour.GetElement(0);
					green *= closestLocalColour.GetElement(1);
					blue *= closestLocalColour.GetElement(2);
					outputImage.SetPixel(x, y, red, green, blue);
				}
			}
		}
	}

	return true;
}