#include "shared_state.h"

ImageQueue imageQueue;

void ImageQueue::enqueue(image& payload) {
    unique_lock<shared_mutex> lock(mutex);

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

optional<image> ImageQueue::dequeue() {
    unique_lock<shared_mutex> lock(mutex);

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

    return nullopt;
}

vector<image> ImageQueue::getQueue() {
    shared_lock<shared_mutex> lock(mutex);

    return imageQueue;
}

image ImageQueue::getImage(int index) {
    shared_lock<shared_mutex> lock(mutex);

    return imageQueue[index];
}

void ImageQueue::printQueue() {
    shared_lock<shared_mutex> lock(mutex);

    for (const auto& img : imageQueue) {
        cout << img.path << " with hue: " << img.hue << endl;
    }
}