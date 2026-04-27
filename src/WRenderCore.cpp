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
#include "cpumem_monitor.h"
#include <string>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "sceneParser.hpp"
#include <SDL3/SDL_gpu.h>
#include <fstream>
#include <vector>
#include <SDL3/SDL_shadercross.h>

SDL_Texture* renderedscene = nullptr;

using json = nlohmann::json;

static json sceneConfig;



static SDL_Window*   offscreen_window   = nullptr;
static SDL_Renderer* offscreen_renderer = nullptr;

static std::optional<std::string> s_filePath     = std::nullopt;
static std::optional<std::string> s_type         = std::nullopt;
static std::optional<std::string> s_sceneName    = std::nullopt;
static std::optional<std::string> s_specificPath = std::nullopt;

static constexpr const char* kSceneTypes = R"({
 "sceneTypes": {
    "Omnix": {
        "ScenePath": "${file}/Game/${SceneName}.xml",
        "SceneFormat": "xml",
        "AssetsPath": "${file}/Assets/",
        "requiresSpecificPath": false
    },
    "Unity": {
        "ScenePath": "${file}",
        "SceneFormat": "yaml",
        "AssetsPath": "${SpecificPath}",
        "requiresSpecificPath": true
    }
 }
})";    

bool WRender_Init(
    SDL_Renderer*              renderer,
    int                        width,
    int                        height,
    std::optional<std::string> filePath,
    std::optional<std::string> type,
    std::optional<std::string> sceneName,
    std::optional<std::string> specificPath)
{
    s_filePath     = std::move(filePath);
    s_type         = std::move(type);
    s_sceneName    = std::move(sceneName);
    s_specificPath = std::move(specificPath);
    
    sceneParser::parseScene(s_filePath, s_type, s_sceneName, s_specificPath);

    
    if (!SDL_CreateWindowAndRenderer("WRender output", width, height, SDL_WINDOW_HIDDEN, &offscreen_window, &offscreen_renderer)) {
        SDL_Log("Couldn't create WRender offscreen window/renderer: %s", SDL_GetError());
        return false;
    }
    renderedscene = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!renderedscene) {
        SDL_Log("Couldn't create WRender output texture: %s", SDL_GetError());
        return false;
    }

    sceneConfig = json::parse(kSceneTypes);
    SDL_ShaderCross_Init();

    SDL_IOStream* io = SDL_IOFromFile("shaders/triangle.frag.hlsl", "r");
    Sint64 size = SDL_GetIOSize(io);
    char* hlslSource = new char[size + 1];
    SDL_ReadIO(io, hlslSource, size);
    hlslSource[size] = '\0';
    SDL_CloseIO(io);

SDL_ShaderCross_HLSL_Info hlslInfo = {};
    hlslInfo.source = hlslSource;
    hlslInfo.entrypoint = "main";
    hlslInfo.shader_stage = SDL_SHADERCROSS_SHADERSTAGE_FRAGMENT;

    fragShader = SDL_ShaderCross_CompileGraphicsShaderFromHLSL(device, &hlslInfo, nullptr);

    return true;
}

SDL_AppResult WRender_Iterate()
{
    if (s_type.has_value()) {
        const auto& types = sceneConfig["sceneTypes"];
        if (!types.contains(*s_type)) {
            SDL_Log("WRender: Unknown scene type '%s'", s_type->c_str());
            return SDL_APP_CONTINUE;
        }
    }

//TODO: parse the scene data from file, type, sceneName, and specificPath

//right now we are just rendering a red rectangle

    SDL_SetRenderDrawColor(offscreen_renderer, 0, 0, 0, 255);
    SDL_RenderClear(offscreen_renderer);

    SDL_SetRenderDrawColor(offscreen_renderer, 255, 0, 0, 255);
    SDL_FRect rect = { 10.0f, 10.0f, 100.0f, 100.0f };
    SDL_RenderFillRect(offscreen_renderer, &rect);

    SDL_RenderPresent(offscreen_renderer);

    SDL_Surface* frame = SDL_RenderReadPixels(offscreen_renderer, nullptr);
    if (frame) {
        SDL_Surface* converted = SDL_ConvertSurface(frame, SDL_PIXELFORMAT_RGBA8888);
        SDL_DestroySurface(frame);
        if (converted) {
            SDL_UpdateTexture(renderedscene, nullptr, converted->pixels, converted->pitch);
            SDL_DestroySurface(converted);
        }
    }

    return SDL_APP_CONTINUE;
}

void WRender_Quit()
{
    SDL_DestroyTexture(renderedscene);
    renderedscene = nullptr;
    SDL_DestroyRenderer(offscreen_renderer);
    SDL_DestroyWindow(offscreen_window);
    offscreen_renderer = nullptr;
    offscreen_window   = nullptr;
    SDL_ShaderCross_Quit();
}
