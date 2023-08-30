// Baratron.h

/*This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

/***************************************************************************
* Create a class for Baratron objects, using
* user selected values.
*
* In general, this works by reading the analog input pin assigned to the gauge
* and then converting the analog input to voltage (0-5v). This is then compared
* to the voltage range of the gauge (provided by the user as the maximum PSIa
* rating). With Baratron gauges, as well as most capacitance manometers,
* 0v = 0psia, 5v=max psia. Yes, this means that gauges must be zeroed to a hard
* vacuum.
*
* Tested with a MKS 870B-24365 gauge on an Adafruit itsybitsy32u4_5V.
*
 ****************************************************************************/

#include "Arduino.h"
#ifndef Baratron_h
#define Baratron_h

class Baratron {
private:
  uint8_t gaugePin; // Analog pin where the gauge is connected to
  int maxPSI; // Maximum PSI reading from gauge. Should produce 5v at this level
  float barometricPressure; // Current barometric pressure in inHg
  int gaugeValue;           // Raw analog value from pin
  float gaugeVoltage;       // Voltage reading from pin
  float gaugePSIa;          // Absolute pressure read from gauge
  float gaugePSIg;          // Gauge pressure, i.e absolute-atmospheric pressure
  int numReadings = 20; // The number of readings to average every read function
  int readings[];

public:
  // Create the Baratron object
  Baratron(uint8_t pin, int PSI, float baro = 29.9212, int readnum = 20);
  void setMaxPSI(int PSI);   // Changes the max psi.
  void updateBaro(int baro); // Updates the barometric pressure
  float readAbsolute();      // Reads absolute pressure in PSI
  float readGauge();         // Reads gauge pressure in PSI
  float getRawVoltage();     // Reads raw gauge voltage for testing purposes
  bool isConnected();  // Returns true if the Baratron is connected and reading a voltage
};

#endif