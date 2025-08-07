# SJT Robo club
![1754569944186426968848425701269](https://github.com/user-attachments/assets/6ce48513-a853-4e92-837b-647ac4cc98c5)

# General Description

🧠 Autonomous Vehicle Solution – WRO 2025 Future Engineers Category


This repository contains the code and technical documentation of an autonomous vehicle designed for the **WRO 2025 – Future Engineers** category. The vehicle is built using an **Arduino Uno**, a **Motor Shield**, **three ultrasonic sensors**, and a **servo motor** for directional control.

The robot is programmed to navigate autonomously through a predefined course. It can detect and avoid obstacles using ultrasonic sensors, perform directional corrections via a servo motor, and make intelligent decisions based on distance thresholds. The entire system is designed to run efficiently with simple components and logic, demonstrating robust obstacle management and movement coordination.

---

⚙️ Hardware Components

* **Arduino Uno** – Main microcontroller.
* **Motor Shield (HW-130 or compatible)** – Controls the DC motor and interfaces with the sensors.
* **DC Motor** – Drives the wheels for forward and reverse motion.
* **3 Ultrasonic Sensors (HC-SR04)** – Positioned at:

  * Front (for detecting obstacles ahead),
  * Left side,
  * Right side.
* **Servo Motor** – Rotates the vehicle to specific angles (130° or 60°) to avoid obstacles.
* **External Power Supply** – Powers the motors and servo (via Motor Shield).

---

📏 Sensor Placement and Logic

* **Front Ultrasonic Sensor:**

  * Constantly measures the distance to objects in front.
  * If an object is detected at less than **50 cm**, the vehicle stops, reverses briefly, and then **rotates** using the servo to find a clear path.
* **Left and Right Ultrasonic Sensors:**

  * Used to detect proximity to obstacles on the sides.
  * If either sensor detects an object **closer than 25 cm**, the vehicle triggers a **quick turn** in the opposite direction using the servo.

🔁 Behavior Flow

1. The vehicle begins moving forward.
2. Continuously monitors distances from the three ultrasonic sensors.
3. If **front sensor < 50 cm**:

   * Stops,
   * Moves backward for a short duration,
   * Turns to **130°** or **60°** depending on the obstacle's location.
4. If **side sensor < 25 cm**:

   * Makes a faster and smaller-angle turn to avoid side collision.
5. Once a clear path is found, the servo reorients the wheels to the forward position, and the vehicle continues moving.

🧩 Code Structure

The code is written in Arduino C++ and consists of:

* `setup()`: Initializes pins, sensor communication, and servo motor.
* `loop()`: Constantly monitors distances and makes decisions based on the threshold values.
* `measureDistance(triggerPin, echoPin)`: Calculates the distance using ultrasonic timing.
* `turnServo(angle)`: Turns the servo to rotate the robot.
* `moveForward()`, `moveBackward()`, `stopMotors()`: Control the DC motor via the Motor Shield.

---

🔌 Pin Mapping (Motor Shield with Arduino Uno)

* **Ultrasonic Front**:

  * Trigger: A0
  * Echo: A1
* **Ultrasonic Left**:

  * Trigger: A2
  * Echo: A3
* **Ultrasonic Right**:

  * Trigger: A4
  * Echo: A5
* **Motor Control Pins** (via Motor Shield):

  * Direction: D12
  * PWM: D3
  * Brake: D9
* **Servo Motor**: D5

🛠️ Compilation and Upload Instructions

1. Open the Arduino IDE.
2. Connect the Arduino Uno via USB.
3. Select the correct **board** ("Arduino Uno") and **port** from the Tools menu.
4. Load the `main.ino` sketch.
5. Click **Verify** (check mark icon) to compile the code.
6. Click **Upload** to flash the code onto the Arduino Uno.
7. Disconnect the USB and power the Arduino externally via battery pack or VIN.

🔁 Commits Timeline

This repository includes at least 3 commits as required:

* **First Commit**: Initial setup, basic movement and sensor testing.
* **Second Commit**: Full obstacle avoidance logic implemented.
* **Third Commit**: Optimization and final version for competition.

Additional commits may be added for tuning performance or improving readability.

📦 Folder Structure

```plaintext
├── main.ino                  # Arduino sketch file
├── README.md                 # Project documentation
├── /models/                  # 3D printable parts (if any)
├── /images/                  # Vehicle and team photos
├── /videos/                  # Demonstration video links
└── /docs/                    # Supporting files or diagrams
```

🎥 Video Demonstration

A public YouTube video link is included in this repository, demonstrating:

* Full autonomous behavior,
* Obstacle avoidance,
* Sensor accuracy,
* Reaction timing.

Minimum 30 seconds, per WRO rules.

