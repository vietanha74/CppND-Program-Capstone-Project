#include "Mandelbrot.h"

double MandelbrotSet::mapToRange(double value, double inputMin, double inputMax, double outputMin, double outputMax) {
    return outputMin + ((value - inputMin) / (inputMax - inputMin)) * (outputMax - outputMin);
}

cv::Vec3b MandelbrotSet::getColor(int iterations) {
    double t = static_cast<double>(iterations) / static_cast<double>(1000);
    int r = static_cast<int>(9 * (1 - t) * t * t * t * 255);
    int g = static_cast<int>(15 * (1 - t) * (1 - t) * t * t * 255);
    int b = static_cast<int>(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    return cv::Vec3b(r, g, b);
}

MandelbrotSet::MandelbrotSet(int width, int height, int maxIterations, double xMin, double xMax, double yMin, double yMax)
    : width_(width), height_(height), maxIterations_(maxIterations), xMin_(xMin), xMax_(xMax), yMin_(yMin), yMax_(yMax) {
    mandelbrotData_.resize(height_, std::vector<cv::Vec3b>(width_));
}

void MandelbrotSet::setData(int width, int height, int maxIterations, double xMin, double xMax, double yMin, double yMax)
{
    width_ = width;
    height_ = height;
    maxIterations_ = maxIterations;
    xMin_ = xMin;
    xMax_ = xMax;
    yMin_ = yMin;
    yMax_ = yMax;
    mandelbrotData_.resize(height_, std::vector<cv::Vec3b>(width_));
}

int MandelbrotSet::getIterationsSimple(long double a, long double b) {

    // Apply the Mandelbrot algorithm to the point
    long double ca = a;
    long double cb = b;
    int iterations = 0;
    while (iterations < 1000) {
        long double aa = a * a - b * b;
        long double bb = 2 * a * b;
        a = aa + ca;
        b = bb + cb;
        if (a * a + b * b > 2.0) {
            break;
        }
        ++iterations;
    }
    return iterations;
}

int MandelbrotSet::getIterations(long double real, long double imaginary) {

    ComplexNumber c(real, imaginary);
    ComplexNumber z;

    int iterations = 0;
    while (iterations < maxIterations_) {
        z = z.square() + c;
        if (z.getReal() * z.getReal() + z.getImaginary() * z.getImaginary() > 4.0) {
            break;
        }
        iterations++;
    }
    return iterations;
}

void MandelbrotSet::calculateMandelbrotSet1() {
    std::vector<std::thread> threads;
    std::mutex mutex;

    int numThreads = std::thread::hardware_concurrency();
    int rowsPerThread = height_ / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? height_ : startRow + rowsPerThread;
        threads.emplace_back([this, startRow, endRow, &mutex]() {
            for (int y = startRow; y < endRow; ++y) {
                for (int x = 0; x < width_; ++x) {
                    double real = mapToRange(x, 0, width_ - 1, xMin_, xMax_);
                    double imaginary = mapToRange(y, 0, height_ - 1, yMin_, yMax_);

                    int iterations = getIterationsSimple(real, imaginary);
                    mandelbrotData_[y][x] = getColor(iterations);
                }
            }
            std::lock_guard<std::mutex> lock(mutex);
            completedRows_ += endRow - startRow;
            if (completedRows_ % (height_ / 10) == 0) {
                std::cout << "Progress: " << (completedRows_ * 100) / height_ << "%" << std::endl;
            }
            });
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }
}

void MandelbrotSet::calculateMandelbrotSet() {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            long double real = mapToRange(x, 0, width_ - 1, xMin_, xMax_);
            long double imaginary = mapToRange(y, 0, height_ - 1, yMin_, yMax_);

            ComplexNumber c(real, imaginary);
            ComplexNumber z;

            int iterations = 0;
            while (iterations < maxIterations_) {
                z = z.square() + c;
                if (z.getReal() * z.getReal() + z.getImaginary() * z.getImaginary() > 4.0) {
                    break;
                }
                iterations++;
            }

            mandelbrotData_[y][x] = getColor(iterations);
        }
    }
}

void MandelbrotSet::calculateMandelbrotSetThread() {
    std::vector<std::thread> threads;
    std::mutex mutex;

    int numThreads = std::thread::hardware_concurrency();
    numThreads = 24;
    int rowsPerThread = height_ / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? height_ : startRow + rowsPerThread;
        threads.emplace_back([this, startRow, endRow, &mutex]() {
            for (int y = startRow; y < endRow; ++y) {
                for (int x = 0; x < width_; ++x) {
                    double real = mapToRange(x, 0, width_ - 1, xMin_, xMax_);
                    double imaginary = mapToRange(y, 0, height_ - 1, yMin_, yMax_);

                    ComplexNumber c(real, imaginary);
                    ComplexNumber z;

                    int iterations = 0;
                    while (iterations < maxIterations_) {
                        z = z.square() + c;
                        if (z.getReal() * z.getReal() + z.getImaginary() * z.getImaginary() > 4.0) {
                            break;
                        }
                        iterations++;
                    }
                    mandelbrotData_[y][x] = getColor(iterations);
                }
            }
            std::lock_guard<std::mutex> lock(mutex);
            completedRows_ += endRow - startRow;
            if (completedRows_ % (height_ / 10) == 0) {
                std::cout << "Progress: " << (completedRows_ * 100) / height_ << "%" << std::endl;
            }
            });
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }
}


const std::vector<std::vector<cv::Vec3b>>& MandelbrotSet::getMandelbrotData() const {
    return mandelbrotData_;
}