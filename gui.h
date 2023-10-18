#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

sf::Vector2f scaleFromDimensions(const sf::Vector2u& textureSize, int screenWidth, int screenHeight);

int slideshow();
