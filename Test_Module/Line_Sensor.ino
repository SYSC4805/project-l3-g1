// Define line sensor pins
const int leftSensor = 4;    // Out1
const int middleSensor = 1;  // Out3
const int rightSensor = 3;   // Out2

// Watchdog Timer Variables
unsigned long lastUpdate = 0;
const unsigned long watchdogTimeout = 500;  // Timeout in milliseconds (0.5 seconds)
const int alertLED = LED_BUILTIN;  // LED pin for alert (use LED_BUILTIN if available)

void setup() {
  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);
  Serial1.begin(9600);  // Initialize communication with Nano
  pinMode(alertLED, OUTPUT);  // Setup alert LED
}

void loop() {
  // Read sensor values
  bool left = digitalRead(leftSensor);
  bool middle = digitalRead(middleSensor);
  bool right = digitalRead(rightSensor);

  // Check if any sensor detects the black line
  if (left == LOW || middle == LOW || right == LOW) {  // Assuming LOW means black line
    Serial1.println("STOP");
    delay(100);

    Serial1.println("REVERSE");
    delay(200);

    if (left == LOW) {
      Serial1.println("TURN_RIGHT");
    } else if (right == LOW) {
      Serial1.println("TURN_LEFT");
    } else {
      Serial1.println("TURN_RIGHT");
    }
    delay(300);
    lastUpdate = millis();  // Reset the watchdog timer
  } else {
    Serial1.println("FORWARD");
    lastUpdate = millis();  // Reset the watchdog timer
  }

  // Check if the watchdog timer has timed out
  if (millis() - lastUpdate > watchdogTimeout) {
    Serial1.println("WATCHDOG_TIMEOUT_STOP");  // Stop the robot due to timeout

    // Flash LED to indicate timeout (error state)
    for (int i = 0; i < 5; i++) {  // Flash LED 5 times
      digitalWrite(alertLED, HIGH);
      delay(100);
      digitalWrite(alertLED, LOW);
      delay(100);
    }
  }

  delay(100);  // Adjust delay based on testing needs
}
