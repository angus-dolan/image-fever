#include "process_image.h"

void processImage() {
	image next = getImage(0);
    Mat image = imread(next.path.c_str());

    // HSV
    Mat hsvModel;
    cvtColor(image, hsvModel, COLOR_BGR2HSV);

    // Hue
    vector<int> hueModel;
    for (int y = 0; y < hsvModel.rows; y++) {
        for (int x = 0; x < hsvModel.cols; x++) {
            Vec3b pixel = hsvModel.at<Vec3b>(y, x);
            hueModel.push_back(pixel[2]); // 0: Hue, 1: Saturation, 2: Value
            
        }
    }

    // Calculate median hue
    int median = calculateMedianHue(hueModel);
   

    // Mutate shared state with unique_lock
    // ...
}

int calculateMedianHue(vector<int>& hueModel) {
    int median = 0;

    // Sorting
    // ...

    median / 360; // normalize
    return mapMedianHue(median);
}

int mapMedianHue(int& median) {
    return median + (1/6.0f);
}
