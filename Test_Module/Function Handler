 

// Motor control pins 

const int M1_DIR = 2; 

const int M1_SPEED = 4; 

const int M2_DIR = 3; 

const int M2_SPEED = 5; 

  

// Ultrasonic sensor pins 

const int trigPinRight = 6; 

const int echoPinRight = 8; 

const int trigPinLeft = 7; 

const int echoPinLeft = 9; 

const int distanceThreshold = 8;  // Threshold distance for obstacle detection (in cm) 

  

// Line sensor pins 

const int leftSensor = 4; 

const int middleSensor = 1; 

const int rightSensor = 3; 

  

unsigned long lastUpdate = 0; 

const unsigned long watchdogTimeout = 1000;  // Timeout in milliseconds (1 second) 

const int alertLED = LED_BUILTIN;  // LED pin for alert (use LED_BUILTIN if available) 

  

void setup() { 

  // Motor control pins setup 

  pinMode(M1_DIR, OUTPUT); 

  pinMode(M1_SPEED, OUTPUT); 

  pinMode(M2_DIR, OUTPUT); 

  pinMode(M2_SPEED, OUTPUT); 

  

  // Ultrasonic sensor setup 

  pinMode(trigPinRight, OUTPUT); 

  pinMode(echoPinRight, INPUT); 

  pinMode(trigPinLeft, OUTPUT); 

  pinMode(echoPinLeft, INPUT); 

  

  // Line sensor pins setup 

  pinMode(leftSensor, INPUT); 

  pinMode(middleSensor, INPUT); 

  pinMode(rightSensor, INPUT); 

  

  // Alert LED setup 

  pinMode(alertLED, OUTPUT); 

  

  Serial.begin(9600); 

} 

  

void loop() { 

  // Get the sensor values 

  int distanceRight = measureDistance(trigPinRight, echoPinRight); 

  int distanceLeft = measureDistance(trigPinLeft, echoPinLeft); 

  

  bool leftLine = digitalRead(leftSensor) == LOW;  // Assuming LOW means black line 

  bool middleLine = digitalRead(middleSensor) == LOW; 

  bool rightLine = digitalRead(rightSensor) == LOW; 

  

  // Function handler for stopping the motors based on sensor conditions 

  handleFunction(distanceRight, distanceLeft, leftLine, middleLine, rightLine); 

  

  delay(100);  // Adjust delay based on testing needs 

} 

  

// Function to measure the distance using the ultrasonic sensors 

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

  

// Function handler that decides what to do based on sensor input 

void handleFunction(int distanceRight, int distanceLeft, bool leftLine, bool middleLine, bool rightLine) { 

  // If either line sensor sees a black line, stop and reverse 

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

  // If an obstacle is detected by the ultrasonic sensors, stop and avoid 

  else if (distanceRight <= distanceThreshold || distanceLeft <= distanceThreshold) { 

    Serial.println("STOP"); 

    stopMotors(); 

    delay(100); 

  

    if (distanceRight <= distanceThreshold) { 

      Serial.println("TURN_LEFT"); 

      turnLeft(); 

    } else if (distanceLeft <= distanceThreshold) { 

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
