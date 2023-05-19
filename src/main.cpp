#include <iostream>
#include <opencv2/opencv.hpp>

#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include "ImageGenerator.h"
#include "UserInterface.h"


int main()
{
    const int width = 800;
    const int height = 600;
    const int maxIterations = 1000;
    const double xMin = -2.0;
    const double xMax = 1.0;
    const double yMin = -1.5;
    const double yMax = 1.5;

    MandelbrotSet mandelbrotSet(width, height, maxIterations, xMin, xMax, yMin, yMax);
    ImageGenerator imageGenerator(width, height);

    UserInterface userInterface(std::ref(mandelbrotSet), std::ref(imageGenerator));
    userInterface.setData(width, height, xMin, xMax, yMin, yMax);
    userInterface.start();

    return 0;
}