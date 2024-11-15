// Ultrasonic Sensor Pins and Threshold
const int trigPinRight = 6;
const int echoPinRight = 8;
const int trigPinLeft = 7;
const int echoPinLeft = 9;
const int distanceThreshold = 8;

// Watchdog Timer Variables
unsigned long lastUpdate = 0;
const unsigned long watchdogTimeout = 2000;  // Timeout in milliseconds (2 seconds)
const int alertLED = LED_BUILTIN;  // LED pin for alert (use LED_BUILTIN if available)

void setup() {
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  Serial1.begin(9600);
  
  // Setup alert LED
  pinMode(alertLED, OUTPUT);
}

void loop() {
  int distanceRight = measureDistance(trigPinRight, echoPinRight);
  int distanceLeft = measureDistance(trigPinLeft, echoPinLeft);

  if (distanceRight <= distanceThreshold || distanceLeft <= distanceThreshold) {
    Serial1.println("STOP");
    delay(100);

    if (distanceRight <= distanceThreshold) {
      Serial1.println("TURN_LEFT");
    } else if (distanceLeft <= distanceThreshold) {
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
    Serial1.println("WATCHDOG_TIMEOUT_STOP");  // Stop the toy due to timeout

    // Flash LED to indicate timeout (error state)
    for (int i = 0; i < 5; i++) {  // Flash LED 5 times
      digitalWrite(alertLED, HIGH);
      delay(200);
      digitalWrite(alertLED, LOW);
      delay(200);
    }
  }

  delay(100);
}

int measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}
