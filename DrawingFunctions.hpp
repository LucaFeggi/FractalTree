#pragma once

#include <SDL.h>

const SDL_Color White = {0xff, 0xff, 0xff};
const SDL_Color Black = {0x00, 0x00, 0x00};

void DrawPixel(int x, int y, SDL_Surface *MySurface, int WindowWidth, SDL_Color Color);
void DrawLine(int x0, int y0, int x1, int y1, SDL_Surface *MySurface, int WindowWidth, SDL_Color Color);
