#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "image.hpp"

class Scene
{
public:
	// Default constructor
	Scene();

	// Render the scene
	bool Render(Image& outputImage);


};



#endif 
