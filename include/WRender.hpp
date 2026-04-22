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
#pragma once

#include <SDL3/SDL.h>
#include <fstream>
#include <string>
#include <optional>

//this is so that any program that uses WRender can access the rendered scene texture and do whatever with it
extern SDL_Texture* renderedscene;

bool WRender_Init(SDL_Renderer* renderer, int width = 960, int height = 540);
SDL_AppResult WRender_Iterate(
    std::ifstream*               file         = nullptr,
    std::optional<std::string>   type         = std::nullopt,
    std::optional<std::string>   sceneName    = std::nullopt,
    std::optional<std::string>   specificPath = std::nullopt);
void WRender_Quit();
