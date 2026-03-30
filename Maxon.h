#ifndef MAXON_H
#define MAXON_H

#include <Arduino.h>

class Maxon {
public:
    Maxon(uint8_t DIR, uint8_t PWMA, uint8_t PWMB)
        : dir(DIR), pwma(PWMA), pwmb(PWMB) {}

    void begin() {
        stop();
        pinMode(dir, OUTPUT);
        pinMode(pwma, OUTPUT);
        pinMode(pwmb, OUTPUT);
    }

    void forward(int speedPercentage) {
        speedPercentage = constrain(speedPercentage, 0, 100);
        int pwmValue = map(speedPercentage, 0, 100, 0, 255);

        digitalWrite(dir, LOW);
        analogWrite(pwma, pwmValue);
        analogWrite(pwmb, pwmValue);
    }

    void backward(int speedPercentage) {
        speedPercentage = constrain(speedPercentage, 0, 100);
        int pwmValue = map(speedPercentage, 0, 100, 0, 255);

        digitalWrite(dir, HIGH);
        analogWrite(pwma, pwmValue);
        analogWrite(pwmb, pwmValue);
    }

    void stop() {
        analogWrite(pwma, 0);
        analogWrite(pwmb, 0);
    }

private:
    uint8_t dir;
    uint8_t pwma;
    uint8_t pwmb;
};

#endif
