// Define line sensor pins
const int leftSensor = 4;    // Out1
const int middleSensor = 1;  // Out3
const int rightSensor = 3;   // Out2

void setup() {
  // Set up sensor pins
  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);

  // Initialize serial communication to communicate with Nano
  Serial1.begin(9600);  // Using Serial1 to communicate with Nano
}

void loop() {
  // Read sensor values
  bool left = digitalRead(leftSensor);
  bool middle = digitalRead(middleSensor);
  bool right = digitalRead(rightSensor);

  // Check if any sensor detects the black line
  if (left == LOW || middle == LOW || right == LOW) {  // Assuming LOW means black line
    Serial1.println("STOP");  // Send a STOP signal to the Nano
    delay(100);               // Small delay to let it process
    Serial1.println("REVERSE");  // Send a REVERSE signal
    delay(200);               // Allow time for reversing

    if (left == LOW) {
      Serial1.println("TURN_RIGHT");  // Turn away from the left sensor line detection
    } else if (right == LOW) {
      Serial1.println("TURN_LEFT");   // Turn away from the right sensor line detection
    } else {
      Serial1.println("TURN_RIGHT");  // Default to turning right if middle sensor detects the line
    }
    delay(300);  // Adjust turning duration as needed
  } else {
    Serial1.println("FORWARD");  // Move forward if no line is detected
  }

  delay(100);  // Adjust delay based on testing needs
}
