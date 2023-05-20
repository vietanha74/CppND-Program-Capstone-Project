#include "UserInterface.h"

UserInterface::UserInterface(int width, int height, double xMin, double xMax, double yMin, double yMax)
    : width_(width), height_(height), xMin_(xMin), xMax_(xMax), yMin_(yMin), yMax_(yMax) {

    cv::namedWindow("Mandelbrot Set");
    cv::setMouseCallback("Mandelbrot Set", &UserInterface::onMouse, this);
}

UserInterface::UserInterface(MandelbrotSet& mandelbrotSet, ImageGenerator& imageGenerator)
{
    cv::namedWindow("Mandelbrot Set");
    cv::setMouseCallback("Mandelbrot Set", &UserInterface::onMouse, this);

    mandelbrotSet_ = mandelbrotSet;
    imageGenerator_ = imageGenerator;
}

void UserInterface::setData(int width, int height, double xMin, double xMax, double yMin, double yMax)
{
    width_ = width;
    height_ = height;
    xMin_ = xMin;
    xMax_ = xMax;
    yMin_ = yMin;
    yMax_ = yMax;
}

void UserInterface::start() {

    mandelbrotSet_.calculateMandelbrotSetThread();
    imageGenerator_.generateImage(mandelbrotSet_.getMandelbrotData());
    imageGenerator_.displayImage();
    //cv::waitKey(0);
    handleKeyPress();
    cv::destroyAllWindows();
}

void UserInterface::handleMouseClick(int x, int y, double Factor) {

    double real = mapToRange(x, 0, width_ - 1, xMin_, xMax_);
    double imaginary = mapToRange(y, 0, height_ - 1, yMin_, yMax_);

    double zoomFactor = Factor;  // Adjust the zoom factor as needed

    double newWidth = (xMax_ - xMin_) * zoomFactor;
    double newHeight = (yMax_ - yMin_) * zoomFactor;
    double newCenterX = real;
    double newCenterY = imaginary;

    xMin_ = newCenterX - newWidth / 2.0;
    xMax_ = newCenterX + newWidth / 2.0;
    yMin_ = newCenterY - newHeight / 2.0;
    yMax_ = newCenterY + newHeight / 2.0;

    mandelbrotSet_.setData(800, 600, 1000, xMin_, xMax_, yMin_, yMax_);
    mandelbrotSet_.calculateMandelbrotSet1();
    imageGenerator_.generateImage(mandelbrotSet_.getMandelbrotData());
    imageGenerator_.displayImage();
}

double UserInterface::mapToRange(int value, int inputMin, int inputMax, double outputMin, double outputMax) {
    return outputMin + ((value - inputMin) / static_cast<double>(inputMax - inputMin)) * (outputMax - outputMin);
}

void UserInterface::onMouse(int event, int x, int y, int flags, void* userdata){
    UserInterface* ui = static_cast<UserInterface*>(userdata);
    if (event == cv::EVENT_LBUTTONDOWN) {
        ui->handleMouseClick(x, y, 0.5);
    }
    else if (event == cv::EVENT_RBUTTONDOWN) {
        ui->handleMouseClick(x, y, 2.0);
    }
}

void UserInterface::handleKeyPress(){
    while (true)
    {
        int key = cv::waitKey(0);

        if (key == 'q' || key == 'Q')
            break;

        if (key == 32) 
        {
            mandelbrotSet_.calculateMandelbrotSetThread();
            imageGenerator_.generateImage(mandelbrotSet_.getMandelbrotData());
            imageGenerator_.displayImage();
        }
    }
}