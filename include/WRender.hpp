#pragma once

#include <SDL3/SDL.h>

extern SDL_Texture* rendertarget;

bool WRender_Init(SDL_Renderer* renderer, int width = 960, int height = 540);
SDL_AppResult WRender_Iterate(SDL_Renderer* renderer);
void WRender_Quit();
