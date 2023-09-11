#include "DrawingFunctions.hpp"

#include <cmath>

void DrawPixel(int x, int y, SDL_Surface *MySurface, int WindowWidth, SDL_Color Color){
	uint8_t* PixelPtr = (uint8_t*)MySurface->pixels + (y * WindowWidth + x) * 4;
	*(PixelPtr + 2) = Color.r;
	*(PixelPtr + 1) = Color.g;
	*(PixelPtr) = Color.b;
}

void DrawLine(int x0, int y0, int x1, int y1, SDL_Surface *MySurface, int WindowWidth, SDL_Color Color){
  double x = x1 - x0;
	double y = y1 - y0;
	double length = sqrt(x * x + y * y);
	double addx = x / length;
	double addy = y / length;
	x = x0;
	y = y0;
	for(int i = 0; i < length; i++){
		DrawPixel((int)x, (int)y, MySurface, WindowWidth, Color);
		x += addx;
		y += addy;
	}
}
