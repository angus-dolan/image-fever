#include "shared_state.h"

std::vector<image> imageQueue;
std::shared_mutex imageQueueLock;

image getImage(int index) {
    std::shared_lock<std::shared_mutex> lock(imageQueueLock);

    return imageQueue[index];

    lock.unlock();
}

std::vector<image> getQueue() {
    std::shared_lock<std::shared_mutex> lock(imageQueueLock);

    return imageQueue;

    lock.unlock();
}
