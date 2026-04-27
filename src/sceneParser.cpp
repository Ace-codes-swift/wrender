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

#include "sceneParser.hpp"
#include <optional>
#include <string>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using json = nlohmann::json;


void sceneParser::parseScene(std::optional<std::string> filePath,
    std::optional<std::string> type,
    std::optional<std::string> sceneName,
    std::optional<std::string> specificPath)
{
    if (filePath.has_value()) {
        fs::path scenePath = fs::path(*filePath);
        else if (scenePath.extension() == ".omnix") {
            std::cout << "omnix file loaded" << scenePath << std::endl;
            
        }
        else {
            std::cout << "unknown file type" << scenePath << std::endl;
        }
    }
}
