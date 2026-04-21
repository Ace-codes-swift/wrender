#pragma once

#include <SDL3/SDL.h>
#include <fstream>
#include <string>

//this is so that any program that uses WRender can access the rendered scene texture and do whatever with it
extern SDL_Texture* renderedscene;

bool WRender_Init(SDL_Renderer* renderer, int width = 960, int height = 540);
SDL_AppResult WRender_Iterate(SDL_Renderer* renderer,
                              std::ifstream*  file         = nullptr,
                              std::string*    type         = nullptr,
                              std::string*    sceneName    = nullptr,
                              std::string*    specificPath = nullptr);
void WRender_Quit();
