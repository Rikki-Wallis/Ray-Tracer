#include "CApp.h"

// Constructor (default)
CApp::CApp() {
    // Initial Variables
    isRunning = true;
    pWindow = NULL;
    pRenderer = NULL;
}

// Handle init of SDL
bool CApp :: OnInit() {

    // Initialise SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    // Create the window
    pWindow = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    // Create renderer
    if (pWindow != NULL) {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

        // Initialise the image instance
        m_image.Initialise(1280, 720, pRenderer);

        // Create colour variations
        for (int x = 0; x < 1280; ++x) {
            for (int y = 0; y < 720; ++y) {
                
                double red = (static_cast<double>(x) / 1280.0) * 255;
                double green = (static_cast<double>(y) / 720.0) * 255;
                m_image.SetPixel(x, y, red, green, 0.0);

            }
        }
    }
    else {
        return false;
    }

    return true;
}

int CApp :: OnExecute() {
    SDL_Event event;

    if (OnInit() == false) {
        return -1;
    }

    while (isRunning) {
        while (SDL_PollEvent(&event) != 0) {
            OnEvent(&event);
        }

        OnLoop();
        OnRender();
    }
}


void CApp::OnEvent(SDL_Event* event) {
    if (event->type == SDL_QUIT) {
        isRunning = false;
    }
}


void CApp::OnLoop() {

}


void CApp::OnRender() {
    // Set background colour to white
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);

    // Display image
    m_image.Display();

    //Show result
    SDL_RenderPresent(pRenderer);
}


void CApp::OnExit() {
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
    SDL_Quit();
}