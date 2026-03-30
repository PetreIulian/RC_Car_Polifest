# ESP32 Bluetooth RC Car

A modular, object-oriented firmware for an ESP32-based RC car. This project uses the **Bluepad32** library to interface with modern Bluetooth gamepads (PS4/PS5/Xbox) to control high-power Maxon motors and a steering servo.

## Features

* [cite_start]**Smooth Acceleration:** Implements a software-based acceleration curve (0.2 step) and a faster deceleration curve (0.3 step) for realistic handling
* [cite_start]**Dynamic Speed Profiles:** Three toggleable speed modes (Level 1-3) with maximum speed limits (15%, 30%, 45%).
* [cite_start]**Variable Steering Geometry:** Switch between "Standard" (45°-135°) and "Wide" (0°-180°) steering angles on the fly.
* [cite_start]**Visual Feedback:** The controller's LED changes color based on the selected speed mode (Green, Blue, or Red).
* **Object-Oriented Design:** Clean separation of concerns between motor driving, steering, and controller input.

---

## Hardware Configuration

### Pin Mapping
[cite_start]The project is configured with the following ESP32 pins:

| Component | Pin | Function |
| :--- | :--- | :--- |
| **DIR** | 25 | Motor Direction Control |
| **PWMA** | 8 | Motor PWM Channel A |
| **PWMB** | 5 | Motor PWM Channel B |
| **SERVO_PIN** | 26 | Steering Servo Signal |

### Hardware Classes
* **`Maxon`**: Manages the DIR and PWM pins to drive the motors forward or backward using mapped speed percentages.
* **`Steering`**: Utilizes `ESP32Servo` to map joystick X-axis values (-512 to 512) to specific servo angles.

---

## 🎮 Controller Mapping

[cite_start]Once connected, the gamepad controls the car as follows:

| Input | Action |
| :--- | :--- |
| **Right Trigger** | [cite_start]Drive Forward (Brake input in code) |
| **Left Trigger** | [cite_start]Drive Backward (Throttle input in code) |
| **Left Joystick (X)**| [cite_start]Steering [cite: 26] |
| **Triangle Button** | [cite_start]Cycle Speed Modes (1 → 2 → 3) |
| **Cross (X) Button** | [cite_start]Toggle Steering Mode (Standard vs. Wide) |
| **R1 Button** | [cite_start]Reset Steering to Center (90°) |

### Speed Modes & Indicators
* **Mode 1:** 15% Max Speed | **Green LED**
* **Mode 2:** 30% Max Speed | **Blue LED**
* **Mode 3:** 45% Max Speed | **Red LED**

---

## Logic Flow

1.  [cite_start]**Input Processing:** The `BP32.update()` function polls the controller.
2.  [cite_start]**Target Calculation:** The triggers determine the `targetSpeed` based on the current `maxSpeedLimit`.
3.  [cite_start]**Smoothing:** The `currentSpeed` incrementally approaches the `targetSpeed` every loop to prevent mechanical stress.
4.  [cite_start]**Steering:** The joystick value is mapped to the current `steer_left` and `steer_right` constraints.

## Dependencies

* [Bluepad32](https://github.com/ricardoquesada/bluepad32)
* [ESP32Servo](https://github.com/madhephaestus/ESP32Servo)
