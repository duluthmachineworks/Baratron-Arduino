# Baratron-Arduino
## A simple Arduino library to read pressure data from MKS Baratron capacitance manometers

## Purpose and Applicability
This library was intended to interface specifically with the MKS Baratron micro capacitance manometers, which are high quality pressure transducers intended for accurate measurement of a wide range of pressures. These sensors can often be obtained on the surplus market for a reasonable cost, and provide exceptional quality for the price.

Specifically, this library was created to interface with a MKS model 870B-24365 pressure transducer, with the following specifications:

- 10.8-32 VDC power input, isolated from output signal
- 0-5 VDC output signal (0 VDC at 0 psia, 5 VDC at max rated psia)
- Four-wire connection
- 250psia rated pressure

This library will likely work with any other pressure transducer that has a linear voltage/pressure response in the 0-5 VDC range, although no other sensors have currently been tested.

## Using the library
To use the library, include Baratron.h in your sketch. This library creates a Baratron class, which can be assigned:
- The analog input pin
- The max(full scale) pressure rating of the gauge
- The current barometric pressure, or constant (in inHg, for derivation of a gauge pressure instead of absolute)
- The number of sensor readings to take per measurement (for averaging)

```
Baratron(uint8_t pin, int PSI, float baro = 29.9212, int readnum = 20);
```
A default value is set for barometric pressure and number of sensor readings, but can be set by the user. Currently, the max (full scale) pressure rating and the barometric pressure can be updated after initializing the Baratron object.

This is then initialized in the main sketch like so:
```
Baratron gauge1(A0, 250); // initializes a Baratron object gauge1, with an analog pin of A0 and max pressure rating of 250psia
```