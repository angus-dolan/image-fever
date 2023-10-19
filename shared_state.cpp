#include "shared_state.h"

std::vector<image> imageQueue;
std::shared_mutex imageQueueLock;
int currentIndex = 0;

std::vector<image> getQueue() {
    std::shared_lock<std::shared_mutex> lock(imageQueueLock);

    return imageQueue;

    lock.unlock();
}

image getCurrentImage() {
    std::shared_lock<std::shared_mutex> lock(imageQueueLock);

    return imageQueue[currentIndex];

    lock.unlock();
}

image getImage(int index) {
    std::shared_lock<std::shared_mutex> lock(imageQueueLock);

    return imageQueue[index];

    lock.unlock();
}
