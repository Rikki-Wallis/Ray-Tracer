#include "headers/CApp.h"
#include "../qbLinAlg/qbVector.h"

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
    pWindow = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_SetWindowBordered(pWindow, SDL_TRUE);



    // Create renderer
    if (pWindow != NULL) {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

        // Initialise the image instance
        m_image.Initialise(1280, 720, pRenderer);

        // Set background to white
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        SDL_RenderClear(pRenderer);

        // Render the scene
        m_scene.Render(m_image);

        // Display the image
        m_image.Display();

        // Show the result
        SDL_RenderPresent(pRenderer);
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
    //// Set background colour to white
    //SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    //SDL_RenderClear(pRenderer);
    //   
    //// Render scene
    //m_scene.Render(m_image);
    //
    //// Display image
    //m_image.Display();

    ////Show result
    //SDL_RenderPresent(pRenderer);
}


void CApp::OnExit() {
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
    SDL_Quit();
}

// Private Functions
void CApp::PrintVector(const qbVector<double>& inputVector) {
    int nRows = inputVector.GetNumDims();
    for (int row = 0; row < nRows; ++row) {
        std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
    }
}