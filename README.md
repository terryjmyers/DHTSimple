# DHTSimple
**Simplified DHT22 library with a single function.  Lightweight and faster.**

Based off of the AdaFruit library.  The AdaFruit library has extraneous functions like converting to F or calculating the heat index.  It also has two different functions for Temperature and Humidity, but yet each functions pulls all of the data needed for both.  So if you wanted both, you had to physically probe the sensor twice with two separate function calls.

**Changes from the AdaFruit Library:**
1. Smaller: Deleted references to different DHT types and extraneous conversion and computational functions
2. Faster: Main function is expecting floats passed in byref, and now only requires one sensor read for both Temperature and Humidity
3. Added Error checking at the end for valid in range non-NAN data.

**Limitations:**
1. Libary has only been tested on ESP8266
2. Will only work with DHT22, not DHT11 (just spend the extra 10 cents already...)


Two Functions
  void begin(uint8_t pin);
  bool Read(float& Temperature, float& Humidity, bool force = false);

Usage (note that I didn't actually test this code):
```
#include <DHTSimple.h>

DHTSimple dht;
float Temperature;
float Humidity;

Setup {
  Serial.Begin(115200);
}

loop {
  if (dht.Read(Temperature, Humidity) == true) {
  Serial.print("Temperature = "); Serial.println(Temperature);
  Serial.print("Humidity = "); Serial.println(Humidity);
  delay(2000);
}
```
