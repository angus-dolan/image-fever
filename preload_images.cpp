#include "preload_images.h"

bool preloadImages() {
    std::unique_lock<std::shared_mutex> lock(imageQueueLock);
    const char* imgFolder = "images/unsorted";

    int i = 0;
    for (auto& p : fs::directory_iterator(imgFolder)) {
        image newImage{
            p.path().u8string(), false, i++, std::numeric_limits<double>::infinity()
        };

        imageQueue.push(newImage);
    }

    return true;
    lock.unlock();
}
