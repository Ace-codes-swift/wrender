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

#include <SDL3/SDL.h>
#include "WRender.hpp"

SDL_Texture* rendertarget = nullptr;

bool WRender_Init(SDL_Renderer* renderer, int width, int height)
{
    rendertarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (!rendertarget) {
        SDL_Log("Couldn't create WRender render target: %s", SDL_GetError());
        return false;
    }
    SDL_SetRenderTarget(renderer, rendertarget);
    return true;
}

SDL_AppResult WRender_Iterate(SDL_Renderer* renderer)
{
    SDL_SetRenderTarget(renderer, rendertarget);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_FRect rect = { 10.0f, 10.0f, 100.0f, 100.0f };
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderTarget(renderer, nullptr);
    return SDL_APP_CONTINUE;
}

void WRender_Quit()
{
    rendertarget = nullptr;
}
