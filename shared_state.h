#pragma once

#include <iostream>
#include <vector>
#include <shared_mutex>
#include <thread>

struct image {
    std::string path;
    bool processed;
    int initialPos;
    float hue;
};

extern std::shared_mutex imageQueueLock;
extern std::vector<image> imageQueue;
extern int currentIndex;

std::vector<image> getQueue();
image getImage(int index);
