/*
 * Photoresistor / Light Intensity Sensor Module test (LM393 LDR module)
 * Works with 3-pin (VCC, GND, DO) and 4-pin (VCC, GND, DO, AO) modules.
 *
 * Connections (Arduino Uno R3):
 *   VCC -> 5V
 *   GND -> GND
 *   DO  -> Pin 2   (Digital threshold output - adjust with blue potentiometer)
 *   AO  -> A0      (Analog brightness output - leave unconnected if 3-pin module)
 */

const int doPin = 2;
const int aoPin = A0;

void setup() {
  Serial.begin(115200);
  pinMode(doPin, INPUT);
  pinMode(aoPin, INPUT);
  Serial.println("Photoresistor / Light Sensor Test");
}

void loop() {
  // DO is usually LOW when bright (threshold reached) and HIGH when dark
  int digitalVal = digitalRead(doPin);

  // AO reads 0 (very bright) to 1023 (dark)
  int analogVal = analogRead(aoPin);

  Serial.print("DO: ");
  Serial.print(digitalVal);
  if (digitalVal == LOW) {
    Serial.print(" (Bright)");
  } else {
    Serial.print(" (Dark)  ");
  }

  Serial.print("  |  AO: ");
  Serial.println(analogVal);

  delay(250);
}
