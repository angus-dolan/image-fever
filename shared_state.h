#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <shared_mutex>
#include <optional>
#include <iterator>
#include <thread>

using namespace std;

struct image {
    string path;
    bool processed;
    int initialPos;
    double hue;
};

class ImageQueue {
private:
    vector<image> imageQueue;

public:
    image getImage(int index);
    vector<image> getQueue();
    void enqueue(image& payload);
    optional<image> dequeue();
    void printQueue() const;
};

extern shared_mutex imageQueueLock;
extern ImageQueue imageQueue;
extern int currentIndex;
