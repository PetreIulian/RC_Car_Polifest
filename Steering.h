#ifndef STEERING_H
#define STEERING_H

#include <Arduino.h>
#include <ESP32Servo.h>

class Steering {
public:
    Steering(uint8_t pin) : _pin(pin) {}

    void begin() {
        _servo.attach(_pin);
        _servo.write(90);
    }

    void turn(int joystickValue, int minAngle, int maxAngle) {
        if (abs(joystickValue) < 25) {
            _servo.write(90);
            return;
        }

        int angle = map(joystickValue, -512, 512, minAngle, maxAngle);
        _servo.write(angle);
    }

    void reset() {
        _servo.write(90);
    }

private:
    uint8_t _pin;
    Servo _servo;
};

#endif
