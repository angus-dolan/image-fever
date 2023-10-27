#include "process_images.h"

double warmth(double& median) {
    return round((median + (1 / 6.0f)) * 100.0) / 100.0;
}

double calculateMedian(vector<uchar>& unsorted) {
    int n = unsorted.size();
    double median;

    // Sort : https://en.cppreference.com/w/cpp/algorithm/sort
    vector<uchar> sorted = unsorted;
    sort(sorted.begin(), sorted.end());
    
    // Calculate median
    if (n % 2 == 0)
        median = (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
    else
        median = sorted[n / 2];

    median = median / 360; // normalize
    return warmth(median); 
}

void process(image& img) {
    Mat image = imread(img.path.c_str());

    // Extract HSV : https://docs.opencv.org/4.x/d8/d01/group__imgproc__color__conversions.html#ga397ae87e1288a81d2363b61574eb8cab
    Mat hsvModel;
    cvtColor(image, hsvModel, COLOR_BGR2HSV);

    // Get hue values from channels : https://docs.opencv.org/4.x/d2/de8/group__core__array.html#ga0547c7fed86152d7e9d0096029c8518a
    vector<Mat> channels(3);
    split(hsvModel, channels);
    Mat hueChannel = channels[0];

    // Flatten hue's for sorting : https://docs.opencv.org/4.x/d3/d63/classcv_1_1Mat.html#a4eb96e3251417fa88b78e2abd6cfd7d8
    vector<uchar> unsorted;
    hueChannel.reshape(0, 1).copyTo(unsorted);
    
    double hue = calculateMedian(unsorted);
    
    // Mutate shared state with unique_lock
    img.hue = hue;
    img.processed = true;
    imageQueue.enqueue(img);
}

void processImages() {
    optional<image> current = imageQueue.dequeue();

    while (current.has_value()) {
        process(current.value());

        // Next image to process
        current = imageQueue.dequeue();
    }
}
