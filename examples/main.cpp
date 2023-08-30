#include <Arduino.h>
#include <Baratron.h> // Get the library at https://github.com/duluthmachineworks/Baratron-Arduino

Baratron gauge1(A0, 250); // initializes a Baratron object gauge1, with an analog pin of A0 and max pressure rating of 250psia

void setup() {
  // Start serial so we can see our results
  Serial.begin(9600);
  delay(1000);  // Let things start...
  Serial.println("Serial started");

  //Check and see if the gauge is responding
  if (gauge1.isConnected()) {
    Serial.println("Connected to Gauge 1");
  } else {
    Serial.println("Check gauge connection");
  }
}

// Define a few holding variables
float read1;
float read2;
float voltRead;

void loop() {
  //Read the gauge and write to holding variables
  read1 = gauge1.readAbsolute();      //read absolute pressure (psia)
  read2 = gauge1.readGauge();         //read gauge pressure (psig)
  voltRead = gauge1.getRawVoltage();  //Get raw voltage from sensor

  // Print everything nicely
  Serial.print(read1);
  Serial.print(" psia, ");
  Serial.print(read2);
  Serial.print(" psig, ");
  Serial.print(voltRead);  
  Serial.println(" v");
  
  // Wait two seconds for the next reading.
  delay(2000);    //Not necessary, can read quickly if desired

  // Uncomment these to see examples of their function
  //gauge1.setMaxPSI(500);     // For a 500psia gauge
  //gauge1.updateBaro(500.00); // A ridiculous value just to see the change.
}
