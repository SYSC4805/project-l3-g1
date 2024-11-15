// Motor control pins 
const int M1_DIR = 2; 
const int M1_SPEED = 4; 
const int M2_DIR = 3; 
const int M2_SPEED = 5; 

// Velleman VMA 330 analog sensor pins
const int rightSensorPin = 24;  // Right sensor analog input
const int leftSensorPin = 22;   // Left sensor analog input
const int distanceThreshold = 512;  // Adjust threshold based on your sensor's range (0-1023)

// Line sensor pins
const int leftLineSensor = 4; 
const int middleLineSensor = 1; 
const int rightLineSensor = 3; 

unsigned long lastUpdate = 0; 
const unsigned long watchdogTimeout = 1000;  // Timeout in milliseconds (1 second) 
const int alertLED = LED_BUILTIN;  // LED pin for alert (use LED_BUILTIN if available) 

void setup() { 
  // Motor control pins setup 
  pinMode(M1_DIR, OUTPUT); 
  pinMode(M1_SPEED, OUTPUT); 
  pinMode(M2_DIR, OUTPUT); 
  pinMode(M2_SPEED, OUTPUT); 

  // Velleman VMA 330 sensor setup 
  pinMode(rightSensorPin, INPUT); 
  pinMode(leftSensorPin, INPUT); 

  // Line sensor pins setup 
  pinMode(leftLineSensor, INPUT); 
  pinMode(middleLineSensor, INPUT); 
  pinMode(rightLineSensor, INPUT); 

  // Alert LED setup 
  pinMode(alertLED, OUTPUT); 

  Serial.begin(9600); 
} 

void loop() { 
  // Get the sensor values from the VMA 330 analog sensors
  int rightSensorValue = analogRead(rightSensorPin); 
  int leftSensorValue = analogRead(leftSensorPin); 

  // Convert analog readings to distance in cm (or whatever scale you're using)
  int rightDistance = convertToDistance(rightSensorValue);
  int leftDistance = convertToDistance(leftSensorValue);

  // Read line sensors
  bool leftLine = digitalRead(leftLineSensor) == LOW;  // Assuming LOW means black line
  bool middleLine = digitalRead(middleLineSensor) == LOW; 
  bool rightLine = digitalRead(rightLineSensor) == LOW; 

  // Function handler for stopping the motors based on sensor conditions 
  handleFunction(rightDistance, leftDistance, leftLine, middleLine, rightLine); 

  delay(100);  // Adjust delay based on testing needs 
} 

// Function to convert the analog sensor reading to distance in centimeters
int convertToDistance(int sensorValue) {
  // Example conversion (you may need to calibrate this)
  // Assuming the sensor value corresponds linearly to distance from 0 to 300 cm
  return map(sensorValue, 0, 1023, 0, 300);
}

// Function handler that decides what to do based on sensor input
void handleFunction(int rightDistance, int leftDistance, bool leftLine, bool middleLine, bool rightLine) { 
  // If any line sensor sees a black line, stop and reverse
  if (leftLine || middleLine || rightLine) { 
    Serial.println("STOP"); 
    stopMotors(); 
    delay(100); 

    Serial.println("REVERSE"); 
    reverseMotors(); 
    delay(200); 

    // Turn based on the line sensor that detected the black line 
    if (leftLine) { 
      Serial.println("TURN_RIGHT"); 
      turnRight(); 
    } else if (rightLine) { 
      Serial.println("TURN_LEFT"); 
      turnLeft(); 
    } else { 
      Serial.println("TURN_RIGHT");  // Default behavior for middle line 
      turnRight(); 
    } 

    lastUpdate = millis();  // Reset watchdog timer 
  } 

  // If an obstacle is detected by the distance sensors, stop and avoid
  else if (rightDistance <= distanceThreshold || leftDistance <= distanceThreshold) { 
    Serial.println("STOP"); 
    stopMotors(); 
    delay(100); 

    if (rightDistance <= distanceThreshold) { 
      Serial.println("TURN_LEFT"); 
      turnLeft(); 
    } else if (leftDistance <= distanceThreshold) { 
      Serial.println("TURN_RIGHT"); 
      turnRight(); 
    } 

    delay(300); 
    lastUpdate = millis();  // Reset watchdog timer 
  } 

  // If no line or obstacle detected, move forward
  else { 
    Serial.println("FORWARD"); 
    moveForward(); 
    lastUpdate = millis();  // Reset watchdog timer 
  } 

  // Watchdog timer check
  if (millis() - lastUpdate > watchdogTimeout) { 
    Serial.println("WATCHDOG_TIMEOUT_STOP"); 
    stopMotors(); 
    flashLED(); 
  } 
} 

// Motor control functions 
void stopMotors() { 
  analogWrite(M1_SPEED, 0); 
  analogWrite(M2_SPEED, 0); 
} 

void reverseMotors() { 
  digitalWrite(M1_DIR, LOW);  // Reverse direction 
  digitalWrite(M2_DIR, LOW); 
  analogWrite(M1_SPEED, 150);  // Adjust speed as necessary 
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

// Flash LED to indicate timeout or error
void flashLED() { 
  for (int i = 0; i < 5; i++) {  // Flash LED 5 times 
    digitalWrite(alertLED, HIGH); 
    delay(100); 
    digitalWrite(alertLED, LOW); 
    delay(100); 
  } 
}
