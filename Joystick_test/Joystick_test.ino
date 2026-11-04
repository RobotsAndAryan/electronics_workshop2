/*
 * 2-Axis Analog Joystick (KY-023) test
 *
 * Connections (Arduino Uno R3):
 *   GND -> GND
 *   +5V -> 5V
 *   VRx -> A0
 *   VRy -> A1
 *   SW  -> Pin 2 (push button)
 */

const int vrxPin = A0;
const int vryPin = A1;
const int swPin  = 2;

void setup() {
  Serial.begin(115200);

  // SW pin shorts to GND when pressed, so enable internal pull-up resistor
  pinMode(swPin, INPUT_PULLUP);
  Serial.println("Joystick test started");
}

void loop() {
  int xVal = analogRead(vrxPin); // 0-1023, center ~512
  int yVal = analogRead(vryPin); // 0-1023, center ~512
  int btnState = digitalRead(swPin); // LOW when pressed, HIGH when released

  Serial.print("X: ");
  Serial.print(xVal);
  Serial.print("  |  Y: ");
  Serial.print(yVal);
  Serial.print("  |  Button: ");
  if (btnState == LOW) {
    Serial.println("Pressed");
  } else {
    Serial.println("Not pressed");
  }

  delay(200);
}
