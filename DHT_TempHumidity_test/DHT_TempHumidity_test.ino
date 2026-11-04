/*
 * Digital Temperature & Humidity Sensor Module test (DHT22 / AM2302 / DHT11)
 * (DollaTek Digital Temperature And Humidity Sensor Module Replace SHT11 SHT15)
 * Based on the Adafruit DHTtester example.
 *
 * Libraries needed: DHT sensor library by Adafruit, Adafruit Unified Sensor
 *
 * Connections (Arduino Uno R3):
 *   VCC / +   -> 5V (or 3.3V)
 *   GND / -   -> GND
 *   OUT / DAT -> Pin 2   (Single-bus digital signal output)
 */

#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor

// Uncomment the type of sensor in use:
#define DHTTYPE DHT22   // DHT 22 (AM2302 / AM2321) - White housing (standard DollaTek SHT11/SHT15 replacement)
//#define DHTTYPE DHT11   // DHT 11 - Blue housing

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx Temperature & Humidity Sensor Test"));

  dht.begin();
}

void loop() {
  // Wait at least 2 seconds between measurements (DHT22 sampling period is ~2s)
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor! Check wiring or DHTTYPE."));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h, 1);
  Serial.print(F("%  |  Temperature: "));
  Serial.print(t, 1);
  Serial.print(F(" °C ("));
  Serial.print(f, 1);
  Serial.print(F(" °F)  |  Heat Index: "));
  Serial.print(hic, 1);
  Serial.println(F(" °C"));
}
