#pragma once

#include <iostream>
#include <vector>
#include <shared_mutex>
#include <thread>

struct image {
    std::string path;
    int initialPos;
};

extern std::vector<image> imageQueue;
extern std::shared_mutex imageQueueLock;

image getImage(int index);
std::vector<image> getQueue();
