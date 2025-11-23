#ifndef CAPP_H
#define CAPP_H

#include <SDL2/SDL.h>
#include "image.hpp"
#include "scene.hpp"
#include "camera.hpp"

class CApp {
public:
    CApp();

    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event* event);
    void OnLoop();
    void OnRender();
    void OnExit();

private:
    void PrintVector(const qbVector<double>& inputVector);

private:
    // Image instance
    Image m_image;
    // Scene Instance
    Scene m_scene;

    // SDL2 stuff
    bool isRunning;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
};



#endif
