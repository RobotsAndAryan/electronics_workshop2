// Basic test for VL53L0X ToF distance sensor (based on Adafruit vl53l0x_oled / vl53l0x example)
// Library: Adafruit_VL53L0X
//
// Connections (Arduino Uno R3):
//   VIN -> 5V (or 3.3V)
//   GND -> GND
//   SDA -> A4
//   SCL -> A5

#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (!Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X - check wiring"));
    while (1);
  }
  // power
  Serial.println(F("VL53L0X API Simple Ranging example\n"));
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  // Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): ");
    Serial.print(measure.RangeMilliMeter);
    Serial.print("  (");
    Serial.print(measure.RangeMilliMeter / 10.0, 1);
    Serial.println(" cm)");
  } else {
    Serial.println(" out of range ");
  }

  delay(200);
}
