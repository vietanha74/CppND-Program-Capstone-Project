#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "ImageGenerator.h"

class UserInterface {
public:
    UserInterface(int width, int height, double xMin, double xMax, double yMin, double yMax);
    UserInterface(MandelbrotSet& mandelbrotSet, ImageGenerator& imageGenerator);
    static void onMouse(int event, int x, int y, int flags, void* userdata);
    void setData(int width, int height, double xMin, double xMax, double yMin, double yMax);
    void start();
    void handleMouseClick(int x, int y, double Factor);
    void handleKeyPress();
private:
    int width_;
    int height_;
    double xMin_;
    double xMax_;
    double yMin_;
    double yMax_;
    MandelbrotSet mandelbrotSet_;
    ImageGenerator imageGenerator_;
    double mapToRange(int value, int inputMin, int inputMax, double outputMin, double outputMax);
};

#endif /* USERINTERFACE_H_ */