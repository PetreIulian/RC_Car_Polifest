#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <PS4Controller.h>

#pragma once

char macAddress[18] = "00:00:00:00:00:00"; // Replace with your PS4 controller's MAC address

class Controller {
public: Controller() {}

    void begin() {
        if(PS4.begin(macAddress)) {
            Serial.println("Connected to PS4 controller");
        } else {
            Serial.println("Failed to connect to PS4 controller");
            return;
        }
    }

    int getLeftJoystickX() {
        if(PS4.isConnected()) {
            return PS4.LStickX();
        } else {
            return 0;
        }
    }

    int getRightJoystickY() {
        if(PS4.isConnected()) {
            return PS4.RStickY();
        } else {
            return 0;
        }

    }

    int getRightTrigger() {
        if(PS4.isConnected()) {
            return PS4.R2();
        }
    }
private:

};

#endif // CONTROLLER_H