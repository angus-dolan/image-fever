#include "preload_images.h"
#include "process_images.h"
#include "shared_state.h"
#include "gui.h"
#include <iostream>
#include <future>
#include <chrono>

int main()
{
    auto start = std::chrono::high_resolution_clock::now(); // for results

    future<bool> preloader = async(launch::async, preloadImages);
    bool preloaded = preloader.get();

    if (preloaded) {
        thread slideshowThread(slideshow);
        processImages(1);

        slideshowThread.join();
    }

    return EXIT_SUCCESS;
}
