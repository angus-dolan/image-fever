#include "preload_images.h"
#include "process_images.h"
#include "shared_state.h"
#include "gui.h"
#include <iostream>
#include <future>
#include <chrono>

int main()
{
    future<bool> preloader = async(launch::async, preloadImages);
    bool preloaded = preloader.get();

    if (preloaded) {
        thread slideshowThread(slideshow);
        processImages(2);

        slideshowThread.join();
    }

    return EXIT_SUCCESS;
}
