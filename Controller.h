#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Bluepad32.h>

#define BUTTON_TRIANGLE 0x0008
#define BUTTON_R1 0x0020
#define BUTTON_L1 0x0010
#define BUTTON_X 0x0001

class Controller {
public:
    Controller() : controller(nullptr) {}

    void setController(ControllerPtr ctl) {
        controller = ctl;
    }

    void clearController() {
        controller = nullptr;
    }

    bool isConnected() {
        return (controller != nullptr && controller->isConnected());
    }

    int getLeftJoystickX() {
        if (!isConnected()) return 0;
        return controller->axisX();
    }

    int getRightTrigger() {
        if (!isConnected()) return 0;
        return controller->throttle(); 
    }

    int getLeftTrigger() {
        if (!isConnected()) return 0;
        return controller->brake();
    }

    bool getButtonR1() {
        if (!isConnected()) return false;
        return (controller->buttons() & BUTTON_R1) != 0;
    }

    bool getButtonTriangle() {
        if (!isConnected()) return false;
        return (controller->buttons() & BUTTON_TRIANGLE) != 0;
    }

    bool getButtonX() {
        if (!isConnected()) return false;
        return (controller->buttons() & BUTTON_X) != 0;
    }

    void setLED(uint8_t r, uint8_t g, uint8_t b) {
        if (isConnected()) {
            controller->setColorLED(r, g, b);
        }
    }

private:
    ControllerPtr controller;
};

#endif
