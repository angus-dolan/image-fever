#include "preload_images.h"

bool preloadImages() {
    string imgFolder = string(CMAKE_DIR) + "/images/unsorted";

    try {
        int i = 0;
        for (auto& p : fs::directory_iterator(imgFolder)) {
            image newImage{
                p.path().u8string(), false, i++, numeric_limits<double>::infinity()
            };

            imageQueue.enqueue(newImage);
        }
    }
    catch (const fs::filesystem_error& e) {
        cerr << e.what() << endl;
        return false;
    }

    return true;
}
