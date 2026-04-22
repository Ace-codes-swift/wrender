/*Copyright © 2026  Ace Jones/ATech

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program. If not, see https://www.gnu.org/licenses/. */

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "WRender.hpp"
//fun chuck norris programing joke #2: chuck norris can make a code library without a test application
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("WRender", "1.0", "com.ATech.WRender");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    //NOTE: 99% of the time this program will be used as a background process so this program is only for testing so the specifics of the window are not important
    
    if (!SDL_CreateWindowAndRenderer("WRender Test App", 960, 540, SDL_WINDOW_BORDERLESS, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    } 

    if (!WRender_Init(renderer)) {
        return SDL_APP_FAILURE;
    }



    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_AppResult result = WRender_Iterate();
    //so we can tell the test app bg from the wrender texture apart so it is red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    //this is intended to be 1/2 the rendered size why: i have no clue but it again doesnt matter as this entire script wont be included in the final lib 
   //TODO: make dynamic resizing of the renderedtexture
    SDL_FRect dst = { 0, 0, 480.0f, 270.0f };
  
    SDL_RenderTexture(renderer, renderedscene, nullptr, &dst);

    SDL_RenderPresent(renderer);

    return result;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    WRender_Quit();
}
