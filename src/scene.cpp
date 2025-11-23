#include "headers/scene.hpp"

// Constructor
Scene::Scene() {

}

// Perform Rendering
bool Scene::Render(Image& outputImage) {
	// Get dimensions of output image
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();

	// Create some colour variations
	for (int x = 0; x < xSize; ++x) {
		for (int y = 0; y < ySize; ++y) {
			double red = (static_cast<double>(x) / 1280.0) * 255;
			double green = (static_cast<double>(y) / 720.0) * 255;
			outputImage.SetPixel(x, y, red, green, 0.0);
		}
	}

	return true;
}