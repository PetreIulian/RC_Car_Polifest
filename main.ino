#include "Maxon.h"
#include "Steering.h"
#include "Controller.h"

#define DIR 2
#define PWMA 3
#define PWMB 4
#define SERVO_PIN 5

Maxon motor(DIR, PWMA, PWMB);
Steering steeringservo(SERVO_PIN);
Controller controller;

void setup() {
    Serial.begin(115200);
    controller.begin();
    motor.begin();
    steeringservo.begin();
}

void loop() {
    if(PS4.isConnected()) {
        
        int leftJoystickX = controller.getLeftJoystickX();
        int rightJoystickY = controller.getRightJoystickY();

        // Motor control
        if(rightJoystickY > 15) { 
            int speedPercentage = map(rightJoystickY, 15, 127, 0, 100);
            motor.forward(speedPercentage);
        } 

        else if (rightJoystickY < -15) {
            int speedPercentage = map(rightJoystickY, -15, -127, 0, 100);
            motor.backward(speedPercentage);
        } 
        else {
            motor.stop();
        }

        //Steering control
        steeringservo.turnLeft(leftJoystickX);
        steeringservo.turnRight(leftJoystickX);
        //Reset steering servo with R2
        steeringservo.reset(controller.getRightTrigger());
    }

    delay(10);
}