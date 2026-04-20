#pragma once

#include <SDL3/SDL.h>
#include <fstream>
#include <string>

extern SDL_Texture* renderedscene;

bool WRender_Init(SDL_Renderer* renderer, int width = 960, int height = 540);
SDL_AppResult WRender_Iterate(SDL_Renderer* renderer, std::ifstream& file, std::string& type);
void WRender_Quit();
