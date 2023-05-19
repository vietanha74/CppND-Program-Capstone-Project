#include "ImageGenerator.h"

ImageGenerator::ImageGenerator(int width, int height) : width_(width), height_(height) {}

void ImageGenerator::generateImage(const std::vector<std::vector<cv::Vec3b>>& mandelbrotData) {
    image_ = cv::Mat(height_, width_, CV_8UC3);
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            image_.at<cv::Vec3b>(y, x) = mandelbrotData[y][x];
        }
    }
}

void ImageGenerator::displayImage() {
    cv::imshow("Mandelbrot Set", image_);

    //cv::waitKey(0);
}