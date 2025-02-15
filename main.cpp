#include <Servo.h>
Servo servo; // Create a servo object
// Pin definitions
const int trigPin = 9;  // Ultrasonic Trig Pin
const int echoPin = 8;  // Ultrasonic Echo Pin
const int capSensorPin = 7; // Capacitive Sensor Pin
const int servoPin = 10; // Servo Motor Pin

long duration;
int distance;
int capSensorValue;

void setup() {
  // Start serial monitor
  Serial.begin(9600);

  // Set up pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(capSensorPin, INPUT);

  // Attach servo to the servo pin
  servo.attach(servoPin);

  // Set initial servo position
  servo.write(90);  // Neutral position
}

void loop() {
  // Get distance from ultrasonic sensor
  distance = getDistance();
  Serial.print("Distance calculated: ");
  Serial.println(distance);

  // If distance is less than 20cm (indicating waste is detected)
  if (distance < 20) {
    Serial.print("Waste detected at distance: ");
    Serial.println(distance);

    // Read capacitive sensor value
    capSensorValue = digitalRead(capSensorPin);
    Serial.print("Capacitive sensor value: ");
    Serial.println(capSensorValue);

    // If capacitive sensor detects touch (e.g., recyclable waste)
    if (capSensorValue == HIGH) {
      Serial.println("Recyclable waste detected!");
      // Move servo to the right (indicating recyclable waste bin)
      servo.write(180);  
      delay(2000);  // Wait for 2 seconds
    }
    // If no touch detected (e.g., general waste)
    else {
      Serial.println("General waste detected!");
      // Move servo to the left (indicating general waste bin)
      servo.write(0);    
      delay(2000);  // Wait for 2 seconds
    }

    // Reset servo to neutral position
    servo.write(90);
  }

  // Small delay to avoid rapid sensor triggering
  delay(500);
}

// Function to get distance from ultrasonic sensor
int getDistance() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (since it goes back and forth)
  Serial.print("Distance in getDistance(): ");
  Serial.println(distance);
  return distance;
}
