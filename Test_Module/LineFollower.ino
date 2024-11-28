// Pin definitions for Cytron motor driver
#define M1_DIR 14  // Motor 1 Direction (Right Motor)
#define M1_PWM 15  // Motor 1 Speed Control (Right Motor)
#define M2_DIR 16  // Motor 2 Direction (Left Motor)
#define M2_PWM 17  // Motor 2 Speed Control (Left Motor)

// Pin definitions for line follower sensor
#define LEFT_SENSOR 10
#define MIDDLE_SENSOR 12
#define RIGHT_SENSOR 11

void setup() {
  // Motor driver pin setup
  pinMode(M1_DIR, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);

  // Line follower sensor pin setup
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(MIDDLE_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
}

void loop() {
  // Read line follower sensor values
  int leftSensor = digitalRead(LEFT_SENSOR);
  int middleSensor = digitalRead(MIDDLE_SENSOR);
  int rightSensor = digitalRead(RIGHT_SENSOR);

    // Move forward
  digitalWrite(M1_DIR, HIGH); // Forward direction for Motor 1
  digitalWrite(M2_DIR, LOW); // Forward direction for Motor 2
  analogWrite(M1_PWM, 150);  // Set speed for Motor 1
  analogWrite(M2_PWM, 150);  // Set speed for Motor 2


  // Check if any sensor detects a black line
  if (leftSensor == HIGH || middleSensor == HIGH || rightSensor == HIGH) {

    // Reverse for 2 seconds
    digitalWrite(M1_DIR, LOW); // Reverse direction for Motor 1 (Right Motor)
    digitalWrite(M2_DIR, HIGH); // Reverse direction for Motor 2 (Left Motor)
    analogWrite(M1_PWM, 150); // Set reverse speed for Motor 1
    analogWrite(M2_PWM, 150); // Set reverse speed for Motor 2
    delay(500);

    // Stop motors
    analogWrite(M1_PWM, 0);
    analogWrite(M2_PWM, 0);
    delay(1000); 

    // Turn left for 2 seconds
    digitalWrite(M1_DIR, HIGH); // Forward direction for Motor 1 (Right Motor)
    digitalWrite(M2_DIR, HIGH); // Forward direction for Motor 2 (Left Motor)
    analogWrite(M1_PWM, 200); // Increase speed for Motor 1 (Right Motor)
    analogWrite(M2_PWM, 0); // Decrease speed for Motor 2 (Left Motor)
    delay(1400);
  }
}

  
  


