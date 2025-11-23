#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "image.hpp"
#include "camera.hpp"
#include "objsphere.hpp"

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
	ObjSphere m_testSphere;

};



#endif 
