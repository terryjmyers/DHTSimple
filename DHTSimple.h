/* DHT library

MIT license
written by Adafruit Industries
Updated by TerryJMyers

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
};

class InterruptLock {
public:
	InterruptLock() {
		noInterrupts();
	}
	~InterruptLock() {
		interrupts();
	}

};

#endif
