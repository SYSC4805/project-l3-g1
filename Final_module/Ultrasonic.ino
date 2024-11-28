#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <LIS3MDL.h>

Adafruit_VL53L0X tofSensor = Adafruit_VL53L0X();
LIS3MDL imu;

// Ultrasonic sensor pins
#define LEFT_TRIG 6
#define LEFT_ECHO 7
#define RIGHT_TRIG 8
#define RIGHT_ECHO 9

// Motor Pins
#define M1_DIR 14 // Right Motor Direction
#define M1_PWM 15 // Right Motor Speed
#define M2_DIR 16 // Left Motor Direction
#define M2_PWM 17 // Left Motor Speed

void setup() {
  Wire.begin();

  // Initialize ToF sensor
  if (!tofSensor.begin()) {
    flashMotors(); // Flash motors to indicate initialization failure
    while (1);     // Halt if initialization fails
  }

  // Initialize IMU
  if (!imu.init()) {
    flashMotors(); // Flash motors to indicate initialization failure
    while (1);     // Halt if initialization fails
  }
  imu.enableDefault();

  // Ultrasonic sensor pins
  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);

  // Motor pins
  pinMode(M1_DIR, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
}

void loop() {
  float leftDistance = getDistance(LEFT_TRIG, LEFT_ECHO);
  float rightDistance = getDistance(RIGHT_TRIG, RIGHT_ECHO);

  // Ultrasonic obstacle detection
  if (leftDistance < 15 || rightDistance < 15) {
    stopMotors();
    turnLeft();

    // Check for obstacles with ToF
    while (true) {
      int tofDistance = readToF();
      if (tofDistance < 15) { // If ToF detects an obstacle
        stopMotors();
        turnRight();
      } else {
        moveForward(); // Move forward to bypass the obstacle
      }

      // Break loop when no obstacles are detected by ToF
      if (tofDistance > 20) {
        stopMotors();
        delay(500);
        turnRight(); // Turn right to align with the original path
        break;
      }
    }
  } else {
    moveForward(); // Continue forward if no obstacles
  }

  delay(100); // Small delay for stability
}

// Function to measure distance using ultrasonic sensor
float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.0343) / 2; // Convert to cm
  return distance;
}

// Function to read distance from ToF sensor
int readToF() {
  VL53L0X_RangingMeasurementData_t measure;
  tofSensor.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) { // 4 means out of range
    return measure.RangeMilliMeter / 10; // Convert to cm
  } else {
    return 255; // Return max range if no object is detected
  }
}

// Function to stop motors
void stopMotors() {
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, 0);
}

// Function to move forward
void moveForward() {
  digitalWrite(M1_DIR, HIGH); // Right motor forward
  digitalWrite(M2_DIR, LOW);  // Left motor forward
  analogWrite(M1_PWM, 150);   // Set speed for Motor 1
  analogWrite(M2_PWM, 150);   // Set speed for Motor 2
}

// Function to turn left
void turnLeft() {
  digitalWrite(M1_DIR, HIGH); // Right motor forward
  digitalWrite(M2_DIR, HIGH); // Left motor backward
  analogWrite(M1_PWM, 150);   // Set speed for Motor 1
  analogWrite(M2_PWM, 150);   // Set speed for Motor 2
  delay(1000);                // Adjust duration for 90-degree turn
  stopMotors();
}

// Function to turn right
void turnRight() {
  digitalWrite(M1_DIR, LOW);  // Right motor backward
  digitalWrite(M2_DIR, LOW);  // Left motor forward
  analogWrite(M1_PWM, 150);   // Set speed for Motor 1
  analogWrite(M2_PWM, 150);   // Set speed for Motor 2
  delay(1000);                // Adjust duration for 90-degree turn
  stopMotors();
}

// Function to flash motors for feedback (e.g., on initialization failure)
void flashMotors() {
  for (int i = 0; i < 3; i++) {
    analogWrite(M1_PWM, 150);
    analogWrite(M2_PWM, 150);
    delay(200);
    analogWrite(M1_PWM, 0);
    analogWrite(M2_PWM, 0);
    delay(200);
  }
}
