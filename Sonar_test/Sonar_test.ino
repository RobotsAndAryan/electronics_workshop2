/*
 * HC-SR04 Ultrasonic Sensor distance test
 * No extra library needed
 *
 * Pins (Arduino Uno R3):
 *   VCC  -> 5V
 *   TRIG -> Pin 9
 *   ECHO -> Pin 10
 *   GND  -> GND
 */

const int trigPin = 9;
const int echoPin = 10;

long duration;
float distanceCm;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("HC-SR04 Ultrasonic Test");
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds to send pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, returns sound wave travel time in microseconds (30ms timeout)
  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    Serial.println("Out of range");
  } else {
    // Speed of sound = 0.0343 cm/us, divide by 2 for round trip
    distanceCm = duration * 0.0343 / 2.0;

    Serial.print("Distance: ");
    Serial.print(distanceCm, 1);
    Serial.print(" cm (");
    Serial.print(distanceCm * 10.0, 0);
    Serial.println(" mm)");
  }

  delay(200);
}
