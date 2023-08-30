// Baratron.cpp
#include "Arduino.h"
#include "Baratron.h"

// Create a Baratron object, with user input.
Baratron::Baratron(uint8_t pin, int PSI, float baro, int readnum) {
  gaugePin = pin;
  maxPSI = PSI;
  barometricPressure = baro;
  numReadings = readnum;
}

// Updates the max PSI of the Baratron object
void Baratron::setMaxPSI(int PSI) { maxPSI = PSI; }

// Updates the current barometric pressure. Can get this from a sensor for
// accurate readings
void Baratron::updateBaro(int baro) { barometricPressure = baro; }

// Reads the absolute pressure (PSIa)
float Baratron::readAbsolute() {
  // Some internal variables used for sensor reading averaging
  int total = 0;
  // Initializes all readings as zero, set our index to zero

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  // read the sensor and populate the readings array
  for (int thisReading = 0; thisReading <= numReadings; thisReading++) {
    // Do the read operation
    readings[thisReading] = analogRead(gaugePin);
    // Keep a running total
    total = total + readings[thisReading];
    // Delay a moment to debounce and make sure reading stable
    delay(5);
  }

  // Average the gauge readings
  gaugeValue = total / numReadings;

  // Convert the analog read in to voltage. Depending on platform/ADC, this may
  // need changing.
  gaugeVoltage = (float)gaugeValue * (5.0 / 1023.0);

  // Calculate and return the absolute pressure
  return gaugeVoltage * ((float)maxPSI / 5.0);
}

// Returns the gauge pressure by calling readAbsolute(), and then subtracting
// the current barometric pressure. For high accuracy applications, keep the
// barometric pressure updated.
float Baratron::readGauge() {
  return readAbsolute() - (barometricPressure * 0.49115);
}

// Dump the raw voltage from the gauge, with no smoothing or debounce
float Baratron::getRawVoltage() {
  return analogRead(gaugePin) * (5.0 / 1023.0);
}

//Check to see if the Baratron is active and connected
bool Baratron::isConnected() {
  int reading = analogRead(gaugePin);
  if (reading > 5) { //looks for value above noise level
    return true;
  } else {
    return false;
  }
}