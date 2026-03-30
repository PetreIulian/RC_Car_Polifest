#include <Bluepad32.h>
#include "Maxon.h"
#include "Steering.h"
#include "Controller.h"

#define DIR 25
#define PWMA 8
#define PWMB 5
#define SERVO_PIN 26

Maxon motor(DIR, PWMA, PWMB);
Steering steeringservo(SERVO_PIN);
ControllerBP gamepad;

int steerMode = 0;
int speedMode = 2;
int maxSpeedLimit = 30;

int steer_left = 45;
int steer_right = 135;

float currentSpeed = 0;
float accelerationStep = 0.2;

bool trianglePressed = false;
bool xPressed = false;

void onConnectedController(ControllerPtr ctl) {
    Serial.println("Controller conectat cu succes!");
    gamepad.setController(ctl);
}

void onDisconnectedController(ControllerPtr ctl) {
    Serial.println("Controller deconectat!");
    gamepad.clearController();
}

void setup() {
    Serial.begin(115200);

    BP32.setup(&onConnectedController, &onDisconnectedController);
    BP32.enableNewBluetoothConnections(true);

    motor.begin();
    steeringservo.begin();
}

void loop() {
    BP32.update();

    if (gamepad.isConnected()) {
        
        bool triangleDown = gamepad.getButtonTriangle(); 
        if (triangleDown && !trianglePressed) {
            speedMode = (speedMode % 3) + 1;

            if (speedMode == 1) {
                maxSpeedLimit = 15;
                gamepad.setLED(0, 255, 0); // Verde
            } else if (speedMode == 2) {
                maxSpeedLimit = 30;
                gamepad.setLED(0, 0, 255); // Albastru
            } else {
                maxSpeedLimit = 45;
                gamepad.setLED(255, 0, 0); // Roșu
            }
            trianglePressed = true;
            Serial.print("Speed Mode Nou: "); Serial.println(speedMode);
        }
        if (!triangleDown) trianglePressed = false;

        bool xDown = gamepad.getButtonX();
        if (xDown && !xPressed) {
            steerMode = (steerMode + 1) % 2;

            if(steerMode == 0) {
                steer_left = 45;
                steer_right = 135;
                Serial.println("Esti gay");
            } else {
                steer_left = 0;
                steer_right = 180;
                Serial.println("Esti lezbi");
            }
            xPressed = true;
        }
        if (!xDown) xPressed = false;

        int throttle = gamepad.getRightTrigger();
        int brake    = gamepad.getLeftTrigger();
        int targetSpeed = 0;
        bool forwardDir = true;

        if (throttle > 20) {
            targetSpeed = map(throttle, 20, 1023, 0, maxSpeedLimit);
            forwardDir = false;
        } else if (brake > 20) {
            targetSpeed = map(brake, 20, 1023, 0, maxSpeedLimit);
            forwardDir = true;
        }

        if (currentSpeed < targetSpeed) {
            currentSpeed += accelerationStep;
        } else if (currentSpeed > targetSpeed) {
            currentSpeed -= (accelerationStep * 1.5);
        }

        if (currentSpeed < 1.0 && targetSpeed == 0) currentSpeed = 0;

        if (currentSpeed > 2) {
            if (forwardDir) motor.forward((int)currentSpeed);
            else motor.backward((int)currentSpeed);
        } else {
            motor.stop();
        }

        steeringservo.turn(gamepad.getLeftJoystickX(), steer_left, steer_right);

        if (gamepad.getButtonR1()) steeringservo.reset();
    }
    
    delay(10);
}
