#ifndef CAPP_H
#define CAPP_H

#include <SDL2/SDL.h>
#include "image.hpp"

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
    // Image instance
    Image m_image;

    // SDL2 stuff
    bool isRunning;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
};



#endif
