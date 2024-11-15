// Motor control pins
const int M1_DIR = 2;
const int M1_SPEED = 4;
const int M2_DIR = 3;
const int M2_SPEED = 5;

void setup() {
  // Set up motor pins
  pinMode(M1_DIR, OUTPUT);
  pinMode(M1_SPEED, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M2_SPEED, OUTPUT);

  // Initialize Serial for communication with Due
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');

    if (command == "STOP") {
      stopMotors();
    } else if (command == "REVERSE") {
      reverseMotors();
    } else if (command == "TURN_LEFT") {
      turnLeft();
    } else if (command == "TURN_RIGHT") {
      turnRight();
    } else if (command == "FORWARD") {
      moveForward();
    }
  }
}

void stopMotors() {
  analogWrite(M1_SPEED, 0);
  analogWrite(M2_SPEED, 0);
}

void reverseMotors() {
  digitalWrite(M1_DIR, LOW);  // Reverse direction
  digitalWrite(M2_DIR, LOW);
  analogWrite(M1_SPEED, 150); // Adjust speed as necessary
  analogWrite(M2_SPEED, 150);
  delay(200);                 // Brief reverse delay
  stopMotors();
}

void turnLeft() {
  digitalWrite(M1_DIR, LOW);  // Reverse right wheels
  digitalWrite(M2_DIR, HIGH); // Forward left wheels
  analogWrite(M1_SPEED, 150);
  analogWrite(M2_SPEED, 150);
  delay(300);                 // Adjust turning duration as necessary
  stopMotors();
}

void turnRight() {
  digitalWrite(M1_DIR, HIGH); // Forward right wheels
  digitalWrite(M2_DIR, LOW);  // Reverse left wheels
  analogWrite(M1_SPEED, 150);
  analogWrite(M2_SPEED, 150);
  delay(300);                 // Adjust turning duration as necessary
  stopMotors();
}

void moveForward() {
  digitalWrite(M1_DIR, HIGH); // Forward both wheels
  digitalWrite(M2_DIR, HIGH);
  analogWrite(M1_SPEED, 150);
  analogWrite(M2_SPEED, 150);
}
