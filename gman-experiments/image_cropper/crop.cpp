#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Read the input image
    Mat image = imread("input_image.jpg");
    
    // Check if the image was successfully loaded
    if(image.empty()) {
        cout << "Error: Couldn't open or find the image." << endl;
        return -1;
    }

    // Define the cropping region
    int x = (image.cols - 724) / 2; // Center crop for width
    int y = (image.rows - 715) / 2; // Center crop for height
    int width = 724;
    int height = 715;

    // Crop the image
    Rect cropRegion(x, y, width, height);
    Mat croppedImage = image(cropRegion);

    // Save the cropped image
    imwrite("cropped_image.jpg", croppedImage);

    cout << "Cropped image saved successfully." << endl;

    return 0;
}
