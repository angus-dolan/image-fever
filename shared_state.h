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
    shared_mutex mutex;

public:
    void enqueue(image& payload);
    optional<image> dequeue();
    vector<image> getQueue();
    image getImage(int index);
    void printQueue();
};

extern ImageQueue imageQueue;