/* DHT library

MIT license
Originall written by Adafruit Industries
Updated by TerryJMyers
	GitHub.com/TerryJMyers/DHTSimple

Simplified DHT22 library with a single function. Lightweight and faster.

Based off of the AdaFruit library. The AdaFruit library has extraneous functions like converting to F or calculating the heat index. It also has two different functions for Temperature and Humidity, but yet each functions pulls all of the data needed for both. So if you wanted both, you had to physically probe the sensor twice with two separate function calls.

Changes from the AdaFruit Library:

Smaller: Deleted references to different DHT types and extraneous conversion and computational functions
Faster: Main function is expecting floats passed in byref, and now only requires one sensor read for both Temperature and Humidity
Added Error checking at the end for valid in range non-NAN data.
Limitations:

Libary has only been tested on ESP8266
Will only work with DHT22, not DHT11 (just spend the extra 10 cents already...)
Two Functions void begin(uint8_t pin); bool Read(float& Temperature, float& Humidity, bool force = false);

Usage (note that I didn't actually test this code):

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



*/
#ifndef DHTSIMPLE_H
#define DHTSIMPLE_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


#define MIN_INTERVAL 2000

// Uncomment to enable printing out nice debug messages.
//#define DHT_DEBUG

// Define where debug output will be printed.
#define DEBUG_PRINTER Serial

// Setup debug printing macros.
	#ifdef DHT_DEBUG
	  #define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
	  #define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
	#else
	  #define DEBUG_PRINT(...) {}
	  #define DEBUG_PRINTLN(...) {}
	#endif

class DHTSimple {

public:
	DHTSimple() {};
	void begin(uint8_t pin);
	bool Read(float& Temperature, float& Humidity, bool force = false);


private:
	uint8_t data[5];
	uint8_t _pin;
	uint32_t _lastreadtime, _maxcycles;
	uint32_t expectPulse(bool level);

	#ifdef __AVR
	// Use direct GPIO access on an 8-bit AVR so keep track of the port and bitmask
	// for the digital pin connected to the DHT.  Other platforms will use digitalRead.
	uint8_t _bit, _port;
	#endif
};

/*!
 *  @brief  Class that defines Interrupt Lock Avaiability
 */
class InterruptLock {
public:
	InterruptLock() {
		#if !defined(ARDUINO_ARCH_NRF52)  
		noInterrupts();
		#endif
	}
	~InterruptLock() {
		#if !defined(ARDUINO_ARCH_NRF52)  
		interrupts();
		#endif
	}
};

#endif
