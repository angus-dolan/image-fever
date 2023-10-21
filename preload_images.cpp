#include "preload_images.h"

bool preloadImages() {
    unique_lock<shared_mutex> lock(imageQueueLock);
    const char* imgFolder = "images/unsorted";

    int i = 0;
    for (auto& p : fs::directory_iterator(imgFolder)) {
        image newImage{
            p.path().u8string(), false, i++, numeric_limits<double>::infinity()
        };

        imageQueue.enqueue(newImage);
    }

    return true;
    lock.unlock();
}
