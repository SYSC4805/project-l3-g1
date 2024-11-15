// Ultrasonic Sensor Pins
const int trigPinRight = 6;   // Trig pin for Right sensor
const int echoPinRight = 8;   // Echo pin for Right sensor
const int trigPinLeft = 7;    // Trig pin for Left sensor
const int echoPinLeft = 9;    // Echo pin for Left sensor

// Distance threshold for obstacle detection (in cm)
const int distanceThreshold = 8;

void setup() {
  // Set up sensor pins
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);

  // Initialize Serial1 for communication with Arduino Nano
  Serial1.begin(9600);
}

void loop() {
  // Measure distance for both sensors
  int distanceRight = measureDistance(trigPinRight, echoPinRight);  // Distance from right sensor
  int distanceLeft = measureDistance(trigPinLeft, echoPinLeft);      // Distance from left sensor

  if (distanceRight <= distanceThreshold || distanceLeft <= distanceThreshold) {
    // Obstacle detected within 8 cm
    Serial1.println("STOP");  // Stop the robot
    delay(100);               // Small delay to allow the Nano to process the stop

    if (distanceRight <= distanceThreshold) {
      // Obstacle detected on the right side, turn left
      Serial1.println("TURN_LEFT");
    } else if (distanceLeft <= distanceThreshold) {
      // Obstacle detected on the left side, turn right
      Serial1.println("TURN_RIGHT");
    }

    delay(300);  // Delay for the turn, adjust as needed
  } else {
    // No obstacle within 8 cm, move forward
    Serial1.println("FORWARD");
  }

  delay(100);  // Delay between readings
}

// Function to measure distance using ultrasonic sensor
int measureDistance(int trigPin, int echoPin) {
  // Send a 10µs pulse to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin and calculate distance
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;  // Convert to cm

  return distance;
}
