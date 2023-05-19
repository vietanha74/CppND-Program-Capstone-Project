#ifndef IMAGEGENERATOR_H_
#define IMAGEGENERATOR_H_

#include "Mandelbrot.h"

class ImageGenerator {
public:
    ImageGenerator() = default;
    ImageGenerator(int width, int height);
    void generateImage(const std::vector<std::vector<cv::Vec3b>>& mandelbrotData);
    void displayImage();
private:
    int width_;
    int height_;
    cv::Mat image_;
};

#endif /* IMAGEGENERATOR */