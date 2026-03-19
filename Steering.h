#ifndef STEERING_H
#define STEERING_H

#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <PS4Controller.h>

Servo steeringServo;

class Steering {
public: 
    Steering(uint8_t pin) : _pin(pin) {}

    void begin() {
        steeringServo.attach(_pin);
        steeringServo.write(90);
    }

    void turnLeft(int joystickValue) {
        if(PS4.isConnected() && joystickValue < -15) {
            int angle = map(joystickValue, -15, -127, 0, 90);
            steeringServo.write(90 - angle);
        }    
    }

    void turnRight(int joystickValue) {
        if(PS4.isConnected() && joystickValue > 15) {
            int angle = map(joystickValue, 15, 127, 0, 90);
            steeringServo.write(90 + angle);
        }
    }

    void reset(int controllerValue) {
        if(PS4.isConnected() && controllerValue > 100) {
            steeringServo.write(90);
        }
    }

private:
    uint8_t _pin;

};

#endif // STEERING_H