#include "shared_state.h"

ImageQueue imageQueue;
shared_mutex imageQueueLock;
int currentIndex = 0;

image ImageQueue::getImage(int index) {
    return imageQueue[index];
}

vector<image> ImageQueue::getQueue() {
    return imageQueue;
}

void ImageQueue::push(image& payload) {
    if (imageQueue.empty()) {
        imageQueue.push_back(payload);
        return;
    }

    for (auto img = imageQueue.begin(); img != imageQueue.end(); ++img) {
        if (img->hue > payload.hue) {
            imageQueue.insert(img, payload);
            return;
        }
    }

    imageQueue.push_back(payload);
}

optional<image> ImageQueue::pop() {
    if (imageQueue.empty()) {
        return nullopt;
    }

    for (auto current = imageQueue.rbegin(); current != imageQueue.rend(); ++current) {
        if (current->processed == false) {
            image img = *current;
            imageQueue.erase(prev(current.base()));
            return img;
        }
    }

    return std::nullopt;
}

void ImageQueue::printQueue() const {
    for (const auto& img : imageQueue) {
        cout << img.path << " with hue: " << img.hue << endl;
    }
}