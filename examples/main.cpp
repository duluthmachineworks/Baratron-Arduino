#include <Arduino.h>
#include <Baratron.h>

Baratron gauge1(A0, 250); // initializes a Baratron object gauge1, with an analog pin of A0 and max pressure rating of 250psia

void setup() {
  // Start serial so we can see our results
  Serial.begin(9600);
}

// Define a couple of holding variables
float read1 = 0.0;
float read2 = 0.0;

void loop() {

  read1 = gauge1.readAbsolute();  //Read the sensor
  read2 = gauge1.readGauge();

  // Print everything nicely
  Serial.print(read1);
  Serial.print(", ");
  Serial.print(read2);
  Serial.println();

  Serial.println(gauge1.getRawVoltage());  //Get raw voltage from sensor
  
  // Wait two seconds for the next reading.
  delay(2000);

  // Uncomment these to see examples of their function
  //gauge1.setMaxPSI(500);     // For a 500psia gauge
  //gauge1.updateBaro(500.00); // A ridiculous value just to see the change.
}
