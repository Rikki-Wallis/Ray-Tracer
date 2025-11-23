#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>

class Image {
public:
	// Constructor
	Image();

	// Destructor
	~Image();

	// Initialise
	void Initialise(const int xSize, const int ySize, SDL_Renderer* pRenderer);

	// Set Color of Pixel
	void SetPixel(const int x, const int y, const double red, const double green, const double blue);

	// Return the image for display
	void Display();

	// Return dimensions of the image
	int GetXSize();
	int GetYSize();

private:
	Uint32 ConvertColor(const double red, const double green, const double blue);
	
	void InitTexture();

private:
	// Store image data
	std::vector<std::vector<double>> m_rChannel;
	std::vector<std::vector<double>> m_gChannel;
	std::vector<std::vector<double>> m_bChannel;

	// Store dimensions of image
	int m_xSize, m_ySize;

	// SDL2 studd
	SDL_Renderer *m_pRenderer;
	SDL_Texture *m_pTexture;
};



#endif