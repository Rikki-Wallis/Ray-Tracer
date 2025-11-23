#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "image.hpp"
#include "camera.hpp"
#include "objsphere.hpp"
#include "pointlight.hpp"

class Scene
{
public:
	// Default constructor
	Scene();

	// Render the scene
	bool Render(Image& outputImage);

private:
	// Attributes
	Camera m_camera;
	std::vector<std::shared_ptr<ObjectBase>> m_objectList;
	std::vector<std::shared_ptr<LightBase>> m_lightList;

};

#endif 
