// Ultrasonic sensor pins
#define LEFT_TRIG 6
#define LEFT_ECHO 7
#define RIGHT_TRIG 8
#define RIGHT_ECHO 9
#define MIDDLE_TRIG 2
#define MIDDLE_ECHO 3


// Line sensor pins
#define LEFT_SENSOR 10
#define MIDDLE_SENSOR 12
#define RIGHT_SENSOR 11

// Motor Pins
#define M1_DIR 14 // Right Motor Direction
#define M1_PWM 15 // Right Motor Speed
#define M2_DIR 16 // Left Motor Direction
#define M2_PWM 17 // Left Motor Speed


void setup() {
  // Ultrasonic sensor pins
  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);

  // Line sensor pins
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(MIDDLE_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  // Motor pins
  pinMode(M1_DIR, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
}

void loop() {
  // Read ultrasonic sensor distances
  float leftDistance = getDistance(LEFT_TRIG, LEFT_ECHO);
  float rightDistance = getDistance(RIGHT_TRIG, RIGHT_ECHO);
  float middleDistance = getDistance(MIDDLE_TRIG, MIDDLE_ECHO);

  // Read line sensor values
  int leftLine = digitalRead(LEFT_SENSOR);
  int middleLine = digitalRead(MIDDLE_SENSOR);
  int rightLine = digitalRead(RIGHT_SENSOR);

  // Line detection logic
  if (leftLine == HIGH || middleLine == HIGH || rightLine == HIGH) {
    handleDetection();
  }
  // Obstacle detection logic
  else if (leftDistance < 17 || rightDistance < 17 || middleDistance < 20) {
    handleDetection();
  } else {
    // Default behavior: Move forward
    moveForward();
  }

  delay(20); // Small delay for stability
}

// Function to handle detections (line or obstacle)
void handleDetection() {
  stopMotors();
  delay(200); // Stop for 200ms

  reverseMotors();
  delay(700); // Reverse for 700ms

  turnLeft(); // Always turn left
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

// Function to stop motors
void stopMotors() {
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, 0);
}

// Function to reverse motors
void reverseMotors() {
  digitalWrite(M1_DIR, LOW); // Right motor backward
  digitalWrite(M2_DIR, HIGH); // Left motor backward
  analogWrite(M1_PWM, 130);   // Set speed for Motor 1
  analogWrite(M2_PWM, 130);   // Set speed for Motor 2
}

// Function to move forward
void moveForward() {
  digitalWrite(M1_DIR, HIGH); // Right motor forward
  digitalWrite(M2_DIR, LOW);  // Left motor forward
  analogWrite(M1_PWM, 130);   // Set speed for Motor 1
  analogWrite(M2_PWM, 130);   // Set speed for Motor 2
}

// Function to turn left in place
void turnLeft() {
  digitalWrite(M1_DIR, HIGH); // Right motor backward
  digitalWrite(M2_DIR, HIGH); // Left motor forward
  analogWrite(M1_PWM, 130);  // Set speed for Motor 1
  analogWrite(M2_PWM, 130);  // Set speed for Motor 2
  long x = random(600, 1001);
  delay(x);               // Turn left
  stopMotors();
}



