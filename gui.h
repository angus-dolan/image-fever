#pragma once

#include "preload_images.h"
#include "shared_state.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

sf::Vector2f scaleFromDimensions(const sf::Vector2u& textureSize, int screenWidth, int screenHeight);

int slideshow();
