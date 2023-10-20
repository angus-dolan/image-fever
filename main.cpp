#include "preload_images.h"
#include "process_image.h"
#include "shared_state.h"
#include "gui.h"
#include <iostream>
#include <future>

int main()
{
    std::future<bool> preloader = std::async(std::launch::async, preloadImages);
    bool preloaded = preloader.get();

    if (preloaded) {
        thread slideshowThread(slideshow);
        thread processImagesThread(processImages);

        slideshowThread.join();
        processImagesThread.join();
    }
   
    return EXIT_SUCCESS;
}
