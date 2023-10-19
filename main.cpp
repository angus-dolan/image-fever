#include "preload_images.h"
#include "gui.h"
#include <iostream>
#include <future>

int main()
{
    std::future<bool> preloader = std::async(std::launch::async, preloadImages);
    bool preloaded = preloader.get();

    if (preloaded) {
        slideshow();
    }
   
    return EXIT_SUCCESS;
}