#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include <thread>
#include "ComplexNumber.h"

using namespace std;

class MandelbrotSet {
public:
    MandelbrotSet() = default;
    MandelbrotSet(int width, int height, int maxIterations, double xMin, double xMax, double yMin, double yMax);

    void setData(int width, int height, int maxIterations, double xMin, double xMax, double yMin, double yMax);
    int getIterationsSimple(long double a, long double b);
    int getIterations(long double real, long double imaginary);
    void calculateMandelbrotSet1();
    void calculateMandelbrotSet();
    void calculateMandelbrotSetThread();
    const std::vector<std::vector<cv::Vec3b>>& getMandelbrotData() const;

private:
    int width_;
    int height_;
    int maxIterations_;
    double xMin_;
    double xMax_;
    double yMin_;
    double yMax_;
    std::vector<std::vector<cv::Vec3b>> mandelbrotData_;
    int completedRows_ = 0;

    double mapToRange(double value, double inputMin, double inputMax, double outputMin, double outputMax);
    cv::Vec3b getColor(int iterations);
};

#endif /* MANDELBROT_H_ */